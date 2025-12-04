#include <iostream>
#include <filesystem>
#include <string>
#include <regex>
#include <vector>
#include <fstream>
#include <sstream>
#include <windows.h>

#include "../00_include/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

const string PATH_SERVER = "D:\\others\\Mir2_Crystal\\Server";

const string PATH_MON_ITEMS = PATH_SERVER + "\\Envir\\Drops";
const string PATH_MON_SPAWN = PATH_SERVER + "\\Exports\\SpawnsExport.txt";

const string PATH_JSON = PATH_SERVER;
const string PATH_JSON_ITEM = PATH_JSON + "\\item.json";
const string PATH_JSON_MON = PATH_JSON + "\\mon.json";

vector<string> split_string_by_regex(const string &str, const string &regex_str)
{
    regex regex_pattern(regex_str);
    sregex_token_iterator it(str.begin(), str.end(), regex_pattern, -1);
    sregex_token_iterator end;
    vector<string> result;

    while (it != end)
    {
        result.push_back(*it++);
    }
    return result;
}

vector<string> split_string(const string &str, char delimiter)
{
    vector<string> tokens;
    istringstream stream(str);
    string token;
    while (getline(stream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

string convert_ansi_to_utf8(const string &ansi_string)
{
    string utf8_string;

    // Get the required buffer size for the wide character string
    int wide_char_length = MultiByteToWideChar(CP_ACP, 0, ansi_string.c_str(), -1, nullptr, 0);
    if (wide_char_length == 0)
    {
        return ""; // Conversion failed
    }

    // Allocate buffer for the wide character string
    vector<wchar_t> wide_char_buffer(wide_char_length);

    // Convert ANSI to wide character (UTF-16)
    int result = MultiByteToWideChar(CP_ACP, 0, ansi_string.c_str(), -1, wide_char_buffer.data(), wide_char_length);
    if (result == 0)
    {
        return ""; // Conversion failed
    }

    // Get the required buffer size for the UTF-8 string
    int utf8_length = WideCharToMultiByte(CP_UTF8, 0, wide_char_buffer.data(), -1, nullptr, 0, nullptr, nullptr);
    if (utf8_length == 0)
    {
        return ""; // Conversion failed
    }

    // Allocate buffer for the UTF-8 string
    vector<char> utf8_buffer(utf8_length);

    // Convert wide character (UTF-16) to UTF-8
    result = WideCharToMultiByte(CP_UTF8, 0, wide_char_buffer.data(), -1, utf8_buffer.data(), utf8_length, nullptr, nullptr);
    if (result == 0)
    {
        return ""; // Conversion failed
    }

    // Construct the UTF-8 string from the buffer
    utf8_string.assign(utf8_buffer.data(), utf8_length - 1); // Exclude the null terminator

    return utf8_string;
}

void convert_item_to_json(const string &path_item, const string &path_json)
{
    map<string, vector<vector<string>>> map_item;

    vector<filesystem::path> path_list(1, filesystem::u8path(path_item));
    int begin(0), end(path_list.size());
    while (begin < end)
    {
        for (int i = begin; i < end; ++i)
        {
            for (const auto &entry : filesystem::directory_iterator(path_list[i]))
            {
                const auto &p(entry.path());
                if (!filesystem::is_directory(p))
                {
                    continue;
                }
                const auto &dir_name(p.stem().string());
                if (dir_name == "Unused")
                {
                    continue;
                }
                path_list.push_back(p);
            }
        }
        begin = end;
        end = path_list.size();
    }

    for (const auto &path : path_list)
    {
        for (const auto &entry : filesystem::directory_iterator(path))
        {
            const auto &p(entry.path());
            if (!filesystem::is_regular_file(p))
            {
                continue;
            }
            const auto &ext(p.extension().string());
            if (ext != ".txt")
            {
                continue;
            }
            const string &mon_name(p.stem().string());
            string line_item;
            ifstream file_item(p);
            if (!file_item.is_open())
            {
                continue;
            }
            while (getline(file_item, line_item))
            {
                const string &line(convert_ansi_to_utf8(line_item));
                vector<string> terms(split_string_by_regex(line, "[\t ]+"));
                if (terms.size() < 2)
                {
                    continue;
                }
                if (terms.size() == 2)
                {
                    terms.push_back("1");
                }
                terms.resize(3);
                const string &item_name(terms[1]);
                terms.push_back(mon_name);
                map_item[item_name].push_back(terms);
            }
            file_item.close();
        }
    }

    json obj_item = json::object();
    for (const auto &[key, value] : map_item)
    {
        json obj_mon = json::array();
        for (const auto &terms : value)
        {
            json obj = json::object();
            obj["mon"] = terms[3];
            obj["number"] = terms[2];
            obj["probability"] = terms[0];
            obj_mon.push_back(obj);
        }
        obj_item[key] = obj_mon;
    }

    ofstream file_json(filesystem::u8path(path_json));
    if (file_json.is_open())
    {
        file_json << setw(2) << obj_item << endl;
        file_json.close();
    }
}

void convert_mon_to_json(const string &path_mon, const string &path_json)
{
    map<string, vector<vector<string>>> map_mon;
    string map_name;
    ifstream file_mon(filesystem::u8path(path_mon));
    if (file_mon.is_open())
    {
        string line_mon;
        while (getline(file_mon, line_mon))
        {
            const string &line(convert_ansi_to_utf8(line_mon));
            if (line.empty())
            {
                continue;
            }
            if (line[0] == ';')
            {
                if (line.find('-') == string::npos && line.find(',') == string::npos)
                {
                    map_name = line.substr(1);
                }
                continue;
            }
            vector<string> terms(split_string_by_regex(line, "[, ]+"));
            if (terms.size() < 8)
            {
                continue;
            }
            if (terms.size() == 8)
            {
                terms.push_back("");
            }
            terms.resize(9);
            const string &mon_name(terms[3]);
            terms.push_back(map_name);
            map_mon[mon_name].push_back(terms);
        }
        file_mon.close();
    }

    json obj_mon = json::object();
    for (const auto &[key, value] : map_mon)
    {
        json obj_position = json::array();
        for (const auto &terms : value)
        {
            json obj = json::object();
            obj["location"] = terms[0] + "(" + terms[1] + "," + terms[2] + ")";
            obj["spread"] = stoi(terms[4]);
            obj["count"] = stoi(terms[5]);
            obj["delay"] = stoi(terms[6]);
            obj["direction"] = stoi(terms[7]);
            obj["route"] = terms[8];
            obj_position.push_back(obj);
        }
        obj_mon[key] = obj_position;
    }

    ofstream file_json(filesystem::u8path(path_json));
    if (file_json.is_open())
    {
        file_json << setw(2) << obj_mon << endl;
        file_json.close();
    }
}

int main()
{
    convert_item_to_json(PATH_MON_ITEMS, PATH_JSON_ITEM);

    convert_mon_to_json(PATH_MON_SPAWN, PATH_JSON_MON);

    return 0;
}

/*
private void ExportMonGenButton_Click(object sender, EventArgs e)
{
    if (_selectedMapInfos.Count == 0) return;

    SaveFileDialog sfd = new SaveFileDialog();
    sfd.InitialDirectory = Path.Combine(Application.StartupPath, "Exports");
    sfd.Filter = "Text File|*.txt";
    sfd.ShowDialog();

    if (sfd.FileName == string.Empty) return;

    for (int i = 0; i < _selectedMapInfos.Count; i++)
    {
        using (StreamWriter sw = File.AppendText(sfd.FileNames[0]))
        {
            for (int j = 0; j < _selectedMapInfos[i].Respawns.Count; j++)
            {
                MonsterInfo mob = Envir.GetMonsterInfo(_selectedMapInfos[i].Respawns[j].MonsterIndex);

                if (mob == null) continue;

                string Output = $"{_selectedMapInfos[i].FileName}" +
                    $",{_selectedMapInfos[i].Respawns[j].Location.X}" +
                    $",{_selectedMapInfos[i].Respawns[j].Location.Y}" +
                    $",{mob.Name}" +
                    $",{_selectedMapInfos[i].Respawns[j].Spread}" +
                    $",{_selectedMapInfos[i].Respawns[j].Count}" +
                    $",{_selectedMapInfos[i].Respawns[j].Delay}" +
                    $",{_selectedMapInfos[i].Respawns[j].Direction}" +
                    $",{_selectedMapInfos[i].Respawns[j].RoutePath}";

                sw.WriteLine(Output);
            }
        }
    }
    MessageBox.Show("MonGen Export complete");
}
*/