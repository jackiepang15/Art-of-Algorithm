#include <vector>

using namespace std;

class Solution
{
public:
    int jump(vector<int> &nums)
    {
        if (nums.empty())
        {
            return -1;
        }
        int size(nums.size());
        int step(0);
        for (int i(0); i < size - 1;)
        {
            int end = min(size - 1, i + nums[i]);
            if (end == size - 1)
            {
                if (end > i)
                {
                    ++step;
                }
                i = end;
            }
            else
            {
                int next(end);
                for (int j = i; j < end; ++j)
                {
                    if (j + nums[j] > next + nums[next])
                    {
                        next = j;
                    }
                }
                if (next > i)
                {
                    ++step;
                }
                else
                {
                    step = -1;
                    break;
                }
                i = next;
            }
        }
        return step;
    }
};