#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

const string PATH_TXT = "D:\\art\\Art_of_Algorithm\\99_others\\douban-japan-norm.txt";

bool isFloatStream(const string& str) {
    stringstream ss(str);
    float f;
    char remaining;
    // Attempt to extract a float and then check if anything else remains
    return (ss >> f && !(ss >> remaining));
}

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
    map<string, vector<string>> data;
    string line;
    while (getline(inputFile, line))
    {
        string score = "0.0";
        int posStart = line.find("（");
        while (posStart != -1)
        {
            int posEnd = line.find("）", posStart + 1);
            string s = line.substr(posStart + 3, posEnd - posStart - 3);
            if (isFloatStream(s))
            {
                score = max(score, s);
            }
            posStart = line.find("（", posStart + 1);
        }
        data[score].push_back(line);
    }
    for (auto i = data.rbegin(); i != data.rend(); ++i)
    {
        const string &score = i->first;
        const vector<string> &lines = i->second;
        for (const auto &line : lines)
        {
            cout << line << endl;
        }
    }

    // 4. Close the file stream
    inputFile.close();

    return 0;
}