#include <vector>

using namespace std;

class Solution
{
public:
    void rotate(vector<int> &nums, int k)
    {
        int size(nums.size());
        k = k % size;
        if (k == 0)
        {
            return;
        }
        int count(0);
        for (int start = 0; start < k && count < size; ++start)
        {
            int curr = start;
            int next = (curr - k + size) % size;
            int val = nums[start];
            while (next != start)
            {
                nums[curr] = nums[next];
                ++count;
                curr = next;
                next = (curr - k + size) % size;
            }
            nums[curr] = val;
            ++count;
        }
    }
};