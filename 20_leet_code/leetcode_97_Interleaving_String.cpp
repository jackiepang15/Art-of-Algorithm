#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    bool isInterleave(string s1, string s2, string s3)
    {
        if (s1.size() + s2.size() != s3.size())
        {
            return false;
        }
        vector<vector<bool>> interleaving(s1.size() + 1, vector<bool>(s2.size() + 1));
        for (int i = 0; i <= s1.size(); ++i)
        {
            for (int j = 0; j <= s2.size(); ++j)
            {
                interleaving[i][j] = i == 0 && j == 0;
                if (j > 0)
                {
                    interleaving[i][j] = interleaving[i][j] || (interleaving[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
                }
                if (i > 0)
                {
                    interleaving[i][j] = interleaving[i][j] || (interleaving[i - 1][j] && s1[i - 1] == s3[i + j - 1]);
                }
            }
        }
        return interleaving[s1.size()][s2.size()];
    }
};