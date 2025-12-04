#include <fstream>
#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

#include "../00_include/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

const string PATH_VIDEO = "H:\\Videos\\test";
const string PATH_VIDEO_INFO = PATH_VIDEO + "\\.videoInfo";

void trim_file_bytes(const string &input_filename, const string &output_filename, size_t bytes_to_trim)
{
    // Open the input file in binary mode for reading
    ifstream input_file(input_filename, ios::in | ios::binary);
    if (!input_file.is_open())
    {
        cerr << "Error - trim_file_bytes: opening input file: " << input_filename << endl;
        return;
    }

    // Skip the first multiple bytes in the input file
    if (!input_file.seekg(bytes_to_trim, ios::beg))
    {
        cerr << "Error - trim_file_bytes: seeking in input file. The file might be too small." << endl;
        input_file.close();
        return;
    }

    // Open the output file in binary mode for writing
    ofstream output_file(output_filename, ios::out | ios::binary);
    if (!output_file.is_open())
    {
        cerr << "Error - trim_file_bytes: opening output file: " << output_filename << endl;
        input_file.close();
        return;
    }

    // Read the remaining content from the input file and write to the output file
    // Using a buffer for efficient reading and writing
    std::vector<char> buffer(4096); // 4KB buffer
    while (input_file.read(buffer.data(), buffer.size()))
    {
        output_file.write(buffer.data(), buffer.size());
    }
    // Write any remaining bytes that didn't fill the last buffer
    output_file.write(buffer.data(), input_file.gcount());

    // Close the files
    input_file.close();
    output_file.close();

    cout << "Log - trim_file_bytes: file successfully trimmed and saved to " << output_filename << endl;
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
        cout << "Please input a file path: ";
        cin >> path;
    }

    string path_info(path + "\\.videoInfo");
    ifstream file_info(path_info);
    if (!file_info.is_open())
    {
        cerr << "Error - path_info: opening file failed." << endl;
        return 1;
    }
    if (!json::accept(file_info))
    {
        cerr << "Error - path_info: not a valid json file." << endl;
        return 1;
    }
    file_info.seekg(0);
    json jf = json::parse(file_info);
    if (!jf.is_object())
    {
        cerr << "Error - path_info: not a json object." << endl;
        return 1;
    }
    if (!jf.contains("title"))
    {
        cerr << "Error - path_info: key 'title' doesn't exist." << endl;
        return 1;
    }
    string title(jf["title"]);
    if (!jf.contains("groupTitle"))
    {
        cerr << "Error - path_info: key 'groupTitle' doesn't exist." << endl;
        return 1;
    }
    string group_title(jf["groupTitle"]);
    string filename_text(path + "\\" + group_title + "-" + title + ".txt");
    cout << "Log - Text: " << filename_text << endl;
    ofstream file_txt(filename_text, ios::out | ios::binary);
    file_txt.close();

    vector<string> file_list;
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
        file_list.push_back(input_filename);
    }
    if (file_list.size() != 2)
    {
        cerr << "Error - file_list: not exact two m4s files." << endl;
        return 1;
    }
    int index(0);
    for (const auto &input_filename : file_list)
    {
        const string &output_filename(path + "\\" + to_string(index) + ".m4s");
        trim_file_bytes(input_filename, output_filename, 9);
        ++index;
    }
    return 0;
}