#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <locale>
#include <codecvt>

#include "../00_include/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

const string PATH_VIDEO = "H:\\Videos\\test";
const string PATH_VIDEO_INFO = PATH_VIDEO + "\\.videoInfo";

bool isFloatStream(const string &str)
{
    stringstream ss(str);
    float f;
    char remaining;
    // Attempt to extract a float and then check if anything else remains
    return (ss >> f && !(ss >> remaining));
}

void trim_file_bytes(const string &input_filename, const string &output_filename, size_t bytes_to_trim)
{
    // Open the input file in binary mode for reading
    ifstream input_file(input_filename, ios::in | ios::binary);
    if (!input_file.is_open())
    {
        cerr << " > Err - Tri: opening input file: " << input_filename << endl;
        return;
    }

    // Skip the first multiple bytes in the input file
    if (!input_file.seekg(bytes_to_trim, ios::beg))
    {
        cerr << " > Err - Tri: seeking in input file. The file might be too small." << endl;
        input_file.close();
        return;
    }

    // Open the output file in binary mode for writing
    ofstream output_file(output_filename, ios::out | ios::binary);
    if (!output_file.is_open())
    {
        cerr << " > Err - Tri: opening output file: " << output_filename << endl;
        input_file.close();
        return;
    }

    // Read the remaining content from the input file and write to the output file
    // Using a buffer for efficient reading and writing
    vector<char> buffer(4096); // 4KB buffer
    while (input_file.read(buffer.data(), buffer.size()))
    {
        output_file.write(buffer.data(), buffer.size());
    }
    // Write any remaining bytes that didn't fill the last buffer
    output_file.write(buffer.data(), input_file.gcount());

    // Close the files
    output_file.close();
    input_file.close();
}

int norm_path(const string &path)
{
    string path_info(path + "\\.videoInfo");
    ifstream file_info(path_info);
    if (!file_info.is_open())
    {
        cerr << " > Err - Inf: opening file failed." << endl;
        file_info.close();
        return 1;
    }
    if (!json::accept(file_info))
    {
        cerr << " > Err - Inf: not a valid json file." << endl;
        file_info.close();
        return 1;
    }
    file_info.seekg(0);
    json jf = json::parse(file_info);
    if (!jf.is_object())
    {
        cerr << " > Err - Inf: not a json object." << endl;
        file_info.close();
        return 1;
    }
    if (!jf.contains("title"))
    {
        cerr << " > Err - Inf: key 'title' doesn't exist." << endl;
        file_info.close();
        return 1;
    }
    string title(jf["title"]);
    if (!jf.contains("groupTitle"))
    {
        cerr << " > Err - Inf: key 'groupTitle' doesn't exist." << endl;
        file_info.close();
        return 1;
    }
    string group_title(jf["groupTitle"]);
    string filename_txt(path + "\\" + group_title + "-" + title + ".txt");
    if (filesystem::exists(filename_txt))
    {
        cerr << " > Err - Txt: file already exists." << endl;
        file_info.close();
        return 1;
    }
    cout << " > Log - Txt: " << filename_txt << endl;
    ofstream file_txt(filename_txt, ios::out | ios::binary);
    file_txt.close();
    file_info.close();

    vector<string> input_files;
    for (const auto &entry : filesystem::directory_iterator(path))
    {
        const auto &p(entry.path());
        if (!filesystem::is_regular_file(p))
        {
            continue;
        }
        const auto &ext(p.extension().string());
        if (ext != ".m4s")
        {
            continue;
        }
        const string &input_filename(p.string());
        input_files.push_back(input_filename);
    }
    if (input_files.size() != 2)
    {
        cerr << " > Err - M4s: not exact two m4s files." << endl;
        return 1;
    }

    vector<string> output_files;
    int index(0);
    for (const auto &filename : input_files)
    {
        const string &filename_m4s(path + "\\" + to_string(index) + ".m4s");
        if (filesystem::exists(filename_m4s))
        {
            cerr << " > Err - M4s: file already exists." << endl;
            return 1;
        }
        output_files.push_back(filename_m4s);
        cout << " > Log - M4s: " << filename_m4s << endl;
        trim_file_bytes(filename, filename_m4s, 9);
        ++index;
    }

    string filename_mp4(path + "\\" + title + ".mp4");
    if (filesystem::exists(filename_mp4))
    {
        cerr << " > Err - Mp4: file already exists." << endl;
        return 1;
    }
    cout << " > Log - Mp4: " << filename_mp4 << endl;
    string cmd("ffmpeg.exe -i \"" + output_files[0] + "\" -i \"" + output_files[1] + "\" -codec copy \"" + filename_mp4 + "\"");
    // cout << " > Log - CMD: " << cmd << endl;
    int ret(system(cmd.c_str()));
    if (ret != 0)
    {
        return ret;
    }

    // Attempt to remove the file
    for (const auto &filename : output_files)
    {
        if (remove(filename.c_str()) != 0)
        {
            cerr << " > Err - M4s: deleting file failed." << endl;
            return 1;
        }
    }

    string filename_jpg(path + "\\image.jpg");
    string filename_png(path + "\\image.png");
    if (filesystem::exists(filename_jpg))
    {
        cout << " > Log - Jpg: " << filename_jpg << endl;
        string filename(path + "\\" + title + ".jpg");
        if (filesystem::exists(filename))
        {
            cerr << " > Err - Jpg: file already exists." << endl;
            return 1;
        }
        filesystem::copy_file(filename_jpg, filename);
    }
    else if (filesystem::exists(filename_png))
    {
        cout << " > Log - Png: " << filename_png << endl;
        string filename(path + "\\" + title + ".png");
        if (filesystem::exists(filename))
        {
            cerr << " > Err - Png: file already exists." << endl;
            return 1;
        }
        filesystem::rename(filename_png, filename);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, ".UTF-8");

    string path(PATH_VIDEO);
    if (argc > 1)
    {
        path = argv[1];
    }
    else
    {
        cout << " > Log - Arg: please input a file path > ";
        cin >> path;
    }

    vector<filesystem::path> path_list;
    for (const auto &entry : filesystem::directory_iterator(path))
    {
        const auto &p(entry.path());
        if (!filesystem::is_directory(p))
        {
            continue;
        }
        const auto &dir_name(p.stem().string());
        if (!isFloatStream(dir_name))
        {
            continue;
        }
        path_list.push_back(p);
    }

    for (const auto &p : path_list)
    {
        const string &path(p.string());
        cout << " > Log - Dir: " << path << endl;
        int ret(norm_path(path));
        if (ret != 0)
        {
            return ret;
        }
    }

    return 0;
}