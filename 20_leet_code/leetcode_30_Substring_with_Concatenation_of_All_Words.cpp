#include <vector>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <list>

using namespace std;

class Solution
{
public:
    vector<int> findSubstring(string s, vector<string> &words)
    {
        if (words.empty())
        {
            return vector<int>();
        }
        vector<int> result;
        int wordLen(words[0].size()), totalLen(wordLen * words.size());
        unordered_map<string, int> number;
        for (int i = words.size() - 1; i >= 0; --i)
        {
            ++number[words[i]];
        }
        int size(s.size());
        for (int i = 0; i < wordLen; ++i)
        {
            unordered_map<string, int> count;
            for (int start = i, end = start; start < size - totalLen + 1; start += wordLen)
            {
                while (true)
                {
                    string sub(s.substr(end, wordLen));
                    if (number.count(sub) > 0 && count[sub] < number[sub])
                    {
                        ++count[sub];
                        end += wordLen;
                        if (end - start == totalLen)
                        {
                            result.push_back(start);
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                if (end > start)
                {
                    string sub(s.substr(start, wordLen));
                    --count[sub];
                }
                else
                {
                    end += wordLen;
                }
            }
        }
        return result;
    }
};