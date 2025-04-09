#include <vector>
#include <unordered_set>

using namespace std;

class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        unordered_set<int> s(nums.begin(), nums.end());
        int maxLength(0);
        for (const auto &x : s)
        {
            if (s.count(x - 1) > 0)
            {
                continue;
            }
            int y(x + 1);
            while (s.count(y) > 0)
            {
                ++y;
            }
            maxLength = max<int>(maxLength, y - x);
        }
        return maxLength;
    }
};