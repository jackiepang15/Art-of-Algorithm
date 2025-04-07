#include <string>

using namespace std;

class Solution
{
public:
    int lengthOfLastWord(string s)
    {
        string word;
        int size(s.size());
        int start(-1);
        for (int i = 0; i < size; ++i)
        {
            if (s[i] == ' ')
            {
                if (start != -1)
                {
                    word = s.substr(start, i - start);
                    start = -1;
                }
            }
            else if (start == -1)
            {
                start = i;
            }
        }
        if (start != -1)
        {
            word = s.substr(start, s.size());
            start = -1;
        }
        return word.size();
    }
};
