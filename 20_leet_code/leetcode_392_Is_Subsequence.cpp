#include <string>

using namespace std;

class Solution
{
public:
    bool isSubsequence(string s, string t)
    {
        if (s.empty())
        {
            return true;
        }
        if (t.empty())
        {
            return false;
        }
        int j = t.size() - 1;
        for (int i = s.size() - 1; i >= 0; --i)
        {
            while (j >= 0 && t[j] != s[i])
            {
                --j;
            }
            if (j < 0)
            {
                return false;
            }
            --j;
        }
        return true;
    }
};