#include <vector>
#include <map>
#include <string>
#include <limits>

using namespace std;

class Solution
{
public:
    int findPeakElement(vector<int> &nums)
    {
        int size(nums.size());
        if (size == 1)
        {
            return 0;
        }
        int begin(0), end(size - 1);
        while (begin < end)
        {
            int mid((begin + end) / 2);
            if (nums[mid] > nums[mid + 1])
            {
                end = mid;
            }
            else
            {
                begin = mid + 1;
            }
        }
        return begin;
    }
};