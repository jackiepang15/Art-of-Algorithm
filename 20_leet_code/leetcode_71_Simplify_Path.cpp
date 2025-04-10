#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Solution
{
public:
    string simplifyPath(string path)
    {
        vector<string> tokens;
        char delimiter('/');
        int start(0), end(path.find(delimiter));
        path.push_back(delimiter);
        while (end != string::npos)
        {
            string t = path.substr(start, end - start);
            start = end + 1;
            end = path.find(delimiter, start);
            if (t.empty() || t.compare(".") == 0)
            {
                continue;
            }
            if (t.compare("..") == 0)
            {
                if (tokens.size() > 0)
                {
                    tokens.pop_back();
                }
            }
            else
            {
                tokens.push_back(t);
            }
        }
        stringstream ss;
        for (const auto &t : tokens)
        {
            ss << '/' << t;
        }
        string result(ss.str());
        return result.empty() ? "/" : result;
    }
};