"""Match image paths between two perceptual-hash JSON files.

Usage:
    python match_image_phashes.py first.json second.json -o matches.json

Each output record contains the first file's ``image_path``, the matching
``image_path`` from the second file, its EXIF ``capture_time``, and a ``location``
object with decimal ``latitude`` and ``longitude``. Unavailable values are null.
An empty matched path is written when no hash is within the maximum Hamming distance.
"""

import argparse
import json
import logging
import math
from pathlib import Path
from urllib.parse import urlencode
from urllib.request import Request, urlopen

max_distance_threshold = 10
PHOTON_URL = "http://192.168.1.4:2322/reverse"
PHOTON_SEARCH_URL = "http://192.168.1.4:2322/api/"
ATTRACTION_SEARCH_TERMS = (
    "attraction",
    "museum",
    "viewpoint",
    "art gallery",
    "garden",
    "mausoleum",
    "monument",
    "historic",
    "mosque",
    "palace",
    "park",
    "zoo",
    "memorial",
    "castle",
    "ruins",
    "waterfall",
)
ATTRACTION_TYPES = {
    "tourism": {
        "attraction",
        "museum",
        "viewpoint",
        "gallery",
        "artwork",
        "zoo",
        "theme_park",
        "aquarium",
    },
    "historic": {
        "archaeological_site",
        "castle",
        "city_gate",
        "fort",
        "manor",
        "memorial",
        "monument",
        "ruins",
        "tomb",
        "wayside_cross",
        "wayside_shrine",
    },
    "leisure": {"garden", "nature_reserve", "park"},
    "natural": {"cave", "peak", "waterfall"},
    "amenity": {"arts_centre", "place_of_worship"},
}
GEOCODER_TIMEOUT = 12
USER_AGENT = "ArtOfAlgorithmImageMatcher/1.0"
LOGGER = logging.getLogger(__name__)


def load_records(path):
    with path.open("r", encoding="utf-8") as input_file:
        records = json.load(input_file)
    if not isinstance(records, list):
        raise ValueError(f"Expected a JSON array in {path}.")
    for index, record in enumerate(records):
        if not isinstance(record, dict) or "image_path" not in record or "phash" not in record:
            raise ValueError(f"Record {index} in {path} must contain image_path and phash.")
    return records


def _gps_coordinate(value, reference):
    degrees, minutes, seconds = (float(part) for part in value)
    coordinate = degrees + minutes / 60 + seconds / 3600
    if reference in {"S", "W"}:
        coordinate = -coordinate
    return coordinate


def read_image_metadata(image_path):
    """Read capture time and GPS coordinates from an image's EXIF data."""
    try:
        from PIL import ExifTags, Image

        if image_path.suffix.lower() in {".heic", ".heif"}:
            from pillow_heif import register_heif_opener

            register_heif_opener()

        with Image.open(image_path) as image:
            exif = image.getexif()
            exif_ifd = exif.get_ifd(ExifTags.IFD.Exif)
            capture_time = (
                exif_ifd.get(ExifTags.Base.DateTimeOriginal)
                or exif_ifd.get(ExifTags.Base.DateTimeDigitized)
                or exif.get(ExifTags.Base.DateTime)
            )

            gps_ifd = exif.get_ifd(ExifTags.IFD.GPSInfo)
            gps = {
                ExifTags.GPSTAGS.get(tag, tag): value
                for tag, value in gps_ifd.items()
            }
            latitude = gps.get("GPSLatitude")
            latitude_ref = gps.get("GPSLatitudeRef")
            longitude = gps.get("GPSLongitude")
            longitude_ref = gps.get("GPSLongitudeRef")
            if latitude and latitude_ref and longitude and longitude_ref:
                location = {
                    "latitude": _gps_coordinate(latitude, latitude_ref),
                    "longitude": _gps_coordinate(longitude, longitude_ref),
                }
            else:
                location = None

        return capture_time, location
    except (ImportError, OSError, ValueError, KeyError) as error:
        LOGGER.warning(
            "Could not read EXIF metadata from %s: %s",
            image_path,
            error,
        )
        return None, None


def _request_json(url, data=None, timeout=10):
    headers = {"User-Agent": USER_AGENT}
    if data is not None:
        headers["Content-Type"] = "application/x-www-form-urlencoded"
    request = Request(url, data=data, headers=headers)
    with urlopen(request, timeout=timeout) as response:
        return json.load(response)


def _first_address_value(address, keys):
    return next((address[key] for key in keys if address.get(key)), None)


def reverse_geocode(latitude, longitude):
    """Resolve address components using Photon."""
    photon_query = urlencode({"lat": latitude, "lon": longitude, "limit": 1})
    try:
        result = _request_json(
            f"{PHOTON_URL}?{photon_query}", timeout=GEOCODER_TIMEOUT
        )
        features = result.get("features", [])
        if not features:
            raise ValueError("Photon returned no address features.")

        properties = features[0].get("properties", {})
        street = properties.get("street")
        if not street and properties.get("type") == "street":
            street = properties.get("name")
        fields = {
            "country": properties.get("country"),
            "state": properties.get("state"),
            "city": properties.get("city"),
            "district": _first_address_value(
                properties, ("district", "suburb", "neighbourhood")
            ),
            "county": properties.get("county"),
            "street": street,
        }
        address_parts = [
            properties.get("name") if properties.get("type") != "street" else None,
            street,
            fields["district"],
            fields["city"],
            fields["county"],
            fields["state"],
            fields["country"],
        ]
        fields["detailed_address"] = ", ".join(
            dict.fromkeys(part for part in address_parts if part)
        ) or None
        return fields
    except Exception as error:
        raise RuntimeError(
            f"Reverse geocoding failed using Photon: {type(error).__name__}: {error}"
        ) from error


def _distance_meters(latitude1, longitude1, latitude2, longitude2):
    earth_radius = 6_371_000
    lat1, lat2 = math.radians(latitude1), math.radians(latitude2)
    delta_lat = lat2 - lat1
    delta_lon = math.radians(longitude2 - longitude1)
    haversine = (
        math.sin(delta_lat / 2) ** 2
        + math.cos(lat1) * math.cos(lat2) * math.sin(delta_lon / 2) ** 2
    )
    return 2 * earth_radius * math.asin(math.sqrt(haversine))


def nearby_attractions(latitude, longitude):
    """Search Photon for named attractions within 1 km and return the closest three."""
    radius_meters = 1000
    latitude_delta = radius_meters / 110_574
    longitude_delta = radius_meters / (
        111_320 * max(math.cos(math.radians(latitude)), 0.01)
    )
    south = max(-90, latitude - latitude_delta)
    north = min(90, latitude + latitude_delta)
    west = longitude - longitude_delta
    east = longitude + longitude_delta
    if west < -180:
        viewboxes = ((-180, south, east, north), (west + 360, south, 180, north))
    elif east > 180:
        viewboxes = ((west, south, 180, north), (-180, south, east - 360, north))
    else:
        viewboxes = ((west, south, east, north),)

    attractions = {}
    try:
        for term in ATTRACTION_SEARCH_TERMS:
            for west_bound, south_bound, east_bound, north_bound in viewboxes:
                query = urlencode(
                    {
                        "q": term,
                        "lat": latitude,
                        "lon": longitude,
                        "bbox": f"{west_bound},{south_bound},{east_bound},{north_bound}",
                        "limit": 50,
                        "lang": "en",
                    }
                )
                try:
                    result = _request_json(
                        f"{PHOTON_SEARCH_URL}?{query}", timeout=GEOCODER_TIMEOUT
                    )
                except Exception as error:
                    LOGGER.warning(
                        "Photon attraction query %r at (%s, %s) failed; skipping it: %s",
                        term,
                        latitude,
                        longitude,
                        error,
                    )
                    continue
                for feature in result.get("features", []):
                    properties = feature.get("properties", {})
                    category = properties.get("osm_key")
                    result_type = properties.get("osm_value")
                    if result_type not in ATTRACTION_TYPES.get(category, set()):
                        continue

                    name = properties.get("name")
                    coordinates = feature.get("geometry", {}).get("coordinates", [])
                    if not name or len(coordinates) < 2:
                        continue
                    try:
                        result_longitude, result_latitude = map(float, coordinates[:2])
                    except (TypeError, ValueError):
                        continue

                    distance = _distance_meters(
                        latitude, longitude, result_latitude, result_longitude
                    )
                    if distance > radius_meters:
                        continue

                    osm_id = properties.get("osm_id")
                    key = (
                        (properties.get("osm_type"), osm_id)
                        if osm_id is not None
                        else (
                            name.casefold(),
                            round(result_latitude, 6),
                            round(result_longitude, 6),
                        )
                    )
                    attraction = {"name": name, "distance_m": round(distance, 1)}
                    if key not in attractions or distance < attractions[key]["_distance"]:
                        attraction["_distance"] = distance
                        attractions[key] = attraction
    except Exception as error:
        raise RuntimeError(
            f"Photon attraction search failed at {PHOTON_SEARCH_URL}: {error}"
        ) from error

    ordered_attractions = sorted(
        attractions.values(), key=lambda attraction: attraction.pop("_distance")
    )
    return ordered_attractions[:3]


def enrich_location(location, include_attractions=True):
    """Add address and optionally nearby attractions, retaining EXIF coordinates."""
    try:
        location.update(reverse_geocode(location["latitude"], location["longitude"]))
    except Exception as error:
        LOGGER.warning(
            "Reverse geocoding failed using Photon at (%s, %s): %s",
            location["latitude"],
            location["longitude"],
            error,
        )
        location.update(
            {
                "country": None,
                "state": None,
                "city": None,
                "district": None,
                "county": None,
                "street": None,
                "detailed_address": None,
            }
        )

    if include_attractions:
        try:
            location["nearby_attractions"] = nearby_attractions(
                location["latitude"], location["longitude"]
            )
        except Exception as error:
            LOGGER.warning(
                "Could not search nearby attractions at (%s, %s): %s",
                location["latitude"],
                location["longitude"],
                error,
            )
            location["nearby_attractions"] = []
    else:
        location["nearby_attractions"] = []
    return location


def main():
    parser = argparse.ArgumentParser(
        description="Match image paths by perceptual hash between two JSON files."
    )
    parser.add_argument("first_json", type=Path, help="JSON file whose images are matched.")
    parser.add_argument("second_json", type=Path, help="JSON file to search for matching hashes.")
    parser.add_argument("-o", "--output", required=True, type=Path, help="Destination JSON file.")
    parser.add_argument(
        "--address-only",
        action="store_true",
        help="Skip nearby attraction searches.",
    )
    args = parser.parse_args()

    from imagededup.methods import PHash
    from tqdm import tqdm

    first_records = load_records(args.first_json)
    second_records = load_records(args.second_json)

    matches = []
    location_cache = {}
    for record in tqdm(first_records, desc="Matching images and locations", unit="image"):
        matched_image_path = ""
        min_distance = max_distance_threshold + 1
        for candidate in second_records:
            distance = PHash.hamming_distance(record["phash"], candidate["phash"])
            if distance < min_distance:
                min_distance = distance
                matched_image_path = candidate["image_path"]
        if min_distance > max_distance_threshold:
            matched_image_path = ""
        if matched_image_path:
            capture_time, location = read_image_metadata(Path(matched_image_path))
            if location:
                coordinate_key = (location["latitude"], location["longitude"])
                if coordinate_key not in location_cache:
                    location_cache[coordinate_key] = enrich_location(
                        location.copy(), include_attractions=not args.address_only
                    )
                location = location_cache[coordinate_key].copy()
        else:
            capture_time, location = None, None
        matches.append(
            {
                "image_path": record["image_path"],
                "matched_image_path": matched_image_path,
                "capture_time": capture_time,
                "location": location,
            }
        )

    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("w", encoding="utf-8") as output_file:
        json.dump(matches, output_file, ensure_ascii=False, indent=2)
        output_file.write("\n")

    print(f"Matched {sum(bool(item['matched_image_path']) for item in matches)} of {len(matches)} image(s).")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())