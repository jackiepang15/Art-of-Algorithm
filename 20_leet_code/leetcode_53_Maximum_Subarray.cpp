#include <vector>
#include <limits>

using namespace std;

class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int maxValue(std::numeric_limits<int>::lowest());
        int currentValue(0);
        for (int i = 0; i < nums.size(); i++)
        {
            currentValue += nums[i];
            maxValue = std::max<int>(maxValue, currentValue);
            if (currentValue < 0)
            {
                currentValue = 0;
            }
        }
        return maxValue;
    }
};