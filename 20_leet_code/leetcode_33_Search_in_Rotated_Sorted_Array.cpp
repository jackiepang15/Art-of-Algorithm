#include <vector>

using namespace std;

class Solution
{
public:
    int search(vector<int> &nums, int target)
    {
        int begin(0), end(nums.size() - 1);
        while (begin < end)
        {
            int mid((begin + end) / 2);
            if (nums[begin] < nums[mid])
            {
                if (nums[begin] > target || nums[mid] < target)
                {
                    begin = mid + 1;
                }
                else
                {
                    end = mid;
                }
            }
            else
            {
                if (nums[mid + 1] > target || nums[end] < target)
                {
                    end = mid;
                }
                else
                {
                    begin = mid + 1;
                }
            }
        }
        return nums[begin] == target ? begin : -1;
    }
};