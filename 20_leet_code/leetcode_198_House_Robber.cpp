#include <vector>

using namespace std;

class Solution
{
public:
    int rob(vector<int> &nums)
    {
        int x(0), y(0);
        if (nums.size() > 0)
        {
            x = y;
            y = nums[0];
        }
        for (int i = 2; i <= nums.size(); ++i)
        {
            int z(max(y, x + nums[i - 1]));
            x = y;
            y = z;
        }
        return y;
    }
};