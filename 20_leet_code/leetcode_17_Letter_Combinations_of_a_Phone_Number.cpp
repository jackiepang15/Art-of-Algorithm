#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    vector<string> letterCombinations(string digits)
    {
        if (digits.empty())
        {
            return vector<string>();
        }
        vector<string> map{"", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> letter(1, "");
        for (const auto &d : digits)
        {
            vector<string> letterNext;
            for (const auto &l : letter)
            {
                for (const auto &c : map[d - '1'])
                {
                    letterNext.push_back(l + c);
                }
            }
            letter = letterNext;
        }
        return letter;
    }
};