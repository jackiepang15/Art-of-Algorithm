#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const string PATH_TXT = "D:\\art\\Art_of_Algorithm\\99_others\\douban-japan.txt";

int main(int argc, char *argv[])
{
    string path(PATH_TXT);
    if (argc > 1)
    {
        path = argv[1];
    }
    else
    {
        cout << "Please input a file path: ";
        cin >> path;
    }

    // 1. Declare an ifstream object and open the file
    ifstream inputFile(path);

    // 2. Check if the file was successfully opened
    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open the file." << endl;
        return 1;
    }

    // 3. Read the file content line by line
    map<string, map<string, string>> data;
    string line, name, description, score;
    int index(0);
    while (getline(inputFile, line))
    {
        if (line == "cover")
        {
            if (!name.empty() && !description.empty() && !score.empty())
            {
                int pos = name.find(" ");
                string key = pos == -1 || pos + 1 == name.size() ? name : name.substr(0, pos);
                string season = pos == -1 || pos + 1 == name.size() ? "" : name.substr(pos + 1);
                string year = description.substr(0, description.find(" "));
                string value = season + "（" + score + "）";
                data[key][year] = value;
                // string result("* " + year + " " + key + value);
                // cout << result << endl;
            }
            name = "";
            description = "";
            score = "";
            index = 0;
            continue;
        }

        if (index == 0)
        {
            name = line;
        }
        else if (index == 1)
        {
            description = line;
        }
        else if (index == 2)
        {
            score = line;
        }
        ++index;
    }
    if (!name.empty() && !description.empty() && !score.empty())
    {
        int pos = name.find(" ");
        string key = pos == -1 || pos + 1 == name.size() ? name : name.substr(0, pos);
        string season = pos == -1 || pos + 1 == name.size() ? "" : name.substr(pos + 1);
        string year = description.substr(0, description.find(" "));
        string value = season + "（" + score + "）";
        data[key][year] = value;
        // string result("* " + year + " " + key + value);
        // cout << result << endl;
    }

    for (const auto& [key, years] : data)
    {
        string values;
        for (const auto& [year, value] : years)
        {
            if (values.empty()) {
                values = value;
            } else {
                values += "、" + value;
            }
        }
        string year = years.begin()->first;
        string result("* " + year + " " + key + values);
        cout << result << endl;
    }

    // 4. Close the file stream
    inputFile.close();

    return 0;
}