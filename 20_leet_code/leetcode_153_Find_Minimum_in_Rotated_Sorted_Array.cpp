#include <vector>

using namespace std;

class Solution
{
public:
    int findMin(vector<int> &nums)
    {
        int begin(0), end(nums.size() - 1);
        while (begin + 1 < end && nums[begin] > nums[end])
        {
            int mid((begin + end) / 2);
            if (nums[begin] < nums[mid])
            {
                begin = mid + 1;
            }
            else
            {
                end = mid;
            }
        }
        return min(nums[begin], nums[end]);
    }
};