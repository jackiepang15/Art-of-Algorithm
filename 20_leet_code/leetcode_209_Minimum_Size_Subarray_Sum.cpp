#include <vector>

using namespace std;

class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int size(nums.size());
        if (size == 0)
        {
            return 0;
        }
        int start(0), end(-1), sum(0), minLen(0);
        while (end < size - 1)
        {
            while (end + 1 < size && sum < target)
            {
                ++end;
                sum += nums[end];
            }
            while (start <= end && sum >= target)
            {
                int len(end - start + 1);
                if (minLen == 0 || len < minLen)
                {
                    minLen = len;
                }
                sum -= nums[start];
                ++start;
            }
        }
        return minLen;
    }
};