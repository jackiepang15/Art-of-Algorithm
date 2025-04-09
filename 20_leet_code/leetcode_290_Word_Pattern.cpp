#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    vector<string> splitToWords(const string &text)
    {
        vector<string> words;
        stringstream ss(text);
        string word;
        while (ss >> word)
        {
            words.push_back(word);
        }
        return words;
    }

    bool wordPattern(string pattern, string s)
    {
        vector<string> words(splitToWords(s));
        if (words.size() != pattern.size())
        {
            return false;
        }
        unordered_map<char, string> mPW;
        unordered_map<string, char> mWP;
        for (int i = pattern.size() - 1; i >= 0; --i)
        {
            if (mPW.count(pattern[i]) == 0 && mWP.count(words[i]) == 0)
            {
                mPW[pattern[i]] = words[i];
                mWP[words[i]] = pattern[i];
            }
            if (mPW.count(pattern[i]) > 0 && mPW[pattern[i]] != words[i])
            {
                return false;
            }
            if (mWP.count(words[i]) > 0 && mWP[words[i]] != pattern[i])
            {
                return false;
            }
        }
        return true;
    }
};