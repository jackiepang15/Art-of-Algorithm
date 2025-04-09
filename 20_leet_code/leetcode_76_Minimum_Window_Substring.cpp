#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution
{
public:
    string minWindow(string s, string t)
    {
        unordered_map<char, int> number;
        for (int i = t.size() - 1; i >= 0; --i)
        {
            ++number[t[i]];
        }
        string minWin;
        int start(0), end(-1), total(t.size());
        unordered_map<char, int> counter;
        while (end + 1 < s.size())
        {
            while (end + 1 < s.size() && total > 0)
            {
                ++end;
                char c(s[end]);
                if (number.count(c) > 0)
                {
                    ++counter[c];
                    if (counter[c] <= number[c])
                    {
                        --total;
                    }
                }
            }
            while (start <= end && total == 0)
            {
                char c(s[start]);
                if (number.count(c) > 0)
                {
                    if (counter[c] <= number[c])
                    {
                        int size(end - start + 1);
                        if (minWin.size() == 0 || size < minWin.size())
                        {
                            minWin = s.substr(start, size);
                        }
                        ++total;
                    }
                    --counter[c];
                }
                ++start;
            }
        }
        return minWin;
    }
};
