#include <map>
#include <string>

using namespace std;

class Solution
{
public:
    map<char, int> m = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}};

    int romanToInt(string s)
    {
        if (s.empty())
        {
            return 0;
        }
        int v(m[s[0]]);
        int size(s.size());
        for (int i = 1; i < size; ++i)
        {
            v += m[s[i]];
            if (m[s[i]] > m[s[i - 1]])
            {
                v -= m[s[i - 1]] * 2;
            }
        }
        return v;
    }
};