#include <string>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    bool isIsomorphic(string s, string t)
    {
        unordered_map<char, char> mST;
        unordered_map<char, char> mTS;
        for (int i = s.size() - 1; i >= 0; --i)
        {
            if (mST.count(s[i]) == 0 && mTS.count(t[i]) == 0)
            {
                mST[s[i]] = t[i];
                mTS[t[i]] = s[i];
            }
            if (mST.count(s[i]) > 0 && mST[s[i]] != t[i])
            {
                return false;
            }
            if (mTS.count(t[i]) > 0 && mTS[t[i]] != s[i])
            {
                return false;
            }
        }
        return true;
    }
};