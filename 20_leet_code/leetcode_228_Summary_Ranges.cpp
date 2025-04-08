#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    vector<string> summaryRanges(vector<int> &nums)
    {
        if (nums.empty())
        {
            return vector<string>();
        }
        int size(nums.size());
        int previous(0);
        vector<string> result;
        for (int i = 1; i < size; ++i)
        {
            if (nums[i] - i > nums[previous] - previous)
            {
                if (previous == i - 1)
                {
                    result.push_back(to_string(nums[previous]));
                }
                else
                {
                    result.push_back(to_string(nums[previous]) + "->" + to_string(nums[i - 1]));
                }
                previous = i;
            }
        }
        if (previous == size - 1)
        {
            result.push_back(to_string(nums[previous]));
        }
        else
        {
            result.push_back(to_string(nums[previous]) + "->" + to_string(nums[size - 1]));
        }
        return result;
    }
};