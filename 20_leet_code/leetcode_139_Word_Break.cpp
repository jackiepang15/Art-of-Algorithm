#include <vector>
#include <string>
#include <set>

using namespace std;

class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        set<int> wordLength;
        for (auto w : wordDict)
        {
            wordLength.insert(w.size());
        }
        set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<bool> segment(s.size() + 1, false);
        segment[0] = true;
        for (int i = 1; i <= s.size(); ++i)
        {
            for (auto l : wordLength)
            {
                if (l <= i && wordSet.count(s.substr(i - l, l)))
                {
                    if (segment[i] = segment[i] || segment[i - l])
                        break;
                }
            }
        }
        return segment[s.size()];
    }
};