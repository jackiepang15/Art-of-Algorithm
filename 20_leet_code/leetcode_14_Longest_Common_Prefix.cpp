#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    string longestCommonPrefix(vector<string> &strs)
    {
        string result;
        int size(strs.size());
        bool fail(false);
        while (!fail)
        {
            fail = strs[0].size() == result.size();
            if (!fail)
            {
                char c(strs[0][result.size()]);
                for (int i = 1; i < size && !fail; ++i)
                {
                    fail = strs[i].size() == result.size() || strs[i][result.size()] != c;
                }
                if (!fail)
                {
                    result.push_back(c);
                }
            }
        }
        return result;
    }
};