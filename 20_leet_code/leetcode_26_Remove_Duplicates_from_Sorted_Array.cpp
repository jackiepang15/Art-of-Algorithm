#include <vector>

using namespace std;

class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        if (nums.empty())
        {
            return nums.size();
        }
        int index = 0;
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i - 1] != nums[i])
            {
                nums[index++] = nums[i - 1];
            }
        }
        nums[index++] = nums.back();
        return index;
    }
};