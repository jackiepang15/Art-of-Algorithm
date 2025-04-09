#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        vector<vector<string>> result;
        unordered_map<string, int> kMap;
        for (const auto &str : strs)
        {
            string key(str);
            sort(key.begin(), key.end());
            if (kMap.count(key) == 0)
            {
                kMap[key] = result.size();
                result.push_back(vector<string>());
            }
            result[kMap[key]].push_back(str);
        }
        return result;
    }
};