#include <string>
#include <unordered_set>

using namespace std;

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int size(s.size());
        if (size == 0)
        {
            return 0;
        }
        unordered_set<char> exist;
        int start(0), end(-1), maxLen(0);
        while (end < size - 1)
        {
            while (end < size - 1 && exist.count(s[end + 1]) == 0)
            {
                ++end;
                exist.insert(s[end]);
                int len(end - start + 1);
                if (len > maxLen)
                {
                    maxLen = len;
                }
            }
            while (end < size - 1 && exist.count(s[end + 1]) > 0)
            {
                exist.erase(s[start]);
                ++start;
            }
        }
        return maxLen;
    }
};
