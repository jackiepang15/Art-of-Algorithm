#include <vector>

using namespace std;

class Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
        int time(0), val(0), size(nums.size());
        for (int i = 0; i < size; ++i)
        {
            int num(nums[i]);
            if (time == 0)
            {
                val = num;
                ++time;
            }
            else
            {
                if (num != val)
                {
                    --time;
                }
                else
                {
                    ++time;
                }
            }
        }
        return val;
    }
};