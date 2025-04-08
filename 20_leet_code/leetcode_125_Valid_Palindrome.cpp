#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    bool isPalindrome(string s)
    {
        for (int i = s.size() - 1; i >= 0; --i)
        {
            s[i] = tolower(s[i]);
        }
        vector<int> alphanumeric(256, false);
        for (char c = 'a'; c <= 'z'; ++c)
        {
            alphanumeric[c] = true;
        }
        for (char c = '0'; c <= '9'; ++c)
        {
            alphanumeric[c] = true;
        }
        int start(0), end(s.size() - 1);
        while (start < end)
        {
            while (start < s.size() && !alphanumeric[s[start]])
            {
                ++start;
            }
            while (end >= 0 && !alphanumeric[s[end]])
            {
                --end;
            }
            if (start < end)
            {
                if (s[start] != s[end])
                {
                    return false;
                }
                ++start;
                --end;
            }
        }
        return true;
    }
};