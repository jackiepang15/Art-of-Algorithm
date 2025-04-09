#include <string>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        unordered_map<char, int> sMap;
        for (const auto &k : s)
        {
            ++sMap[k];
        }

        unordered_map<char, int> tMap;
        for (const auto &k : t)
        {
            ++tMap[k];
        }

        if (sMap.size() != tMap.size())
        {
            return false;
        }
        for (const auto &kv : sMap)
        {
            if (tMap.count(kv.first) == 0 || kv.second != tMap[kv.first])
            {
                return false;
            }
        }
        return true;
    }
};