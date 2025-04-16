#include <vector>
#include <stdlib.h>

using namespace std;

class Solution
{
public:
    int findKthLargest(vector<int> &nums, int k)
    {
        return findKthLargest(nums, 0, nums.size() - 1, k);
    }

    int findKthLargest(vector<int> &nums, int begin, int end, int k)
    {
        if (begin == end)
        {
            return nums[begin];
        }

        int size(end - begin + 1), pivot(begin + rand() % size);
        swap(nums[pivot], nums[begin]);

        int val(nums[begin]);
        int start(begin);
        for (int i = begin + 1; i <= end; ++i)
        {
            if (nums[i] > val)
            {
                swap(nums[++start], nums[i]);
            }
        }
        swap(nums[start], nums[begin]);

        if (start == k - 1)
        {
            return nums[start];
        }
        else if (start > k - 1)
        {
            return findKthLargest(nums, begin, start - 1, k);
        }
        else
        {
            while (start + 1 < k - 1 && nums[start + 1] == val)
            {
                ++start;
            }
            return findKthLargest(nums, start + 1, end, k);
        }
    }
};