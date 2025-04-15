#include <vector>

using namespace std;

class Solution
{
public:
    int searchInsert(vector<int> &nums, int target)
    {
        int begin(0);
        if (nums[begin] >= target)
        {
            return begin;
        }
        int end(nums.size() - 1);
        if (nums[end] < target)
        {
            return end + 1;
        }
        while (begin < end)
        {
            int mid((begin + end) / 2);
            if (nums[mid] < target)
            {
                begin = mid + 1;
            }
            else
            {
                end = mid;
            }
        }
        return begin;
    }
};