#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    string reverseWords(string s)
    {
        vector<string> words;
        int size(s.size());
        int start(-1);
        for (int i = 0; i < size; ++i)
        {
            if (s[i] == ' ')
            {
                if (start != -1)
                {
                    words.push_back(s.substr(start, i - start));
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
            words.push_back(s.substr(start, s.size()));
            start = -1;
        }
        string result(words.back());
        for (int i = words.size() - 2; i >= 0; --i)
        {
            result.push_back(' ');
            result.append(words[i]);
        }
        return result;
    }
};