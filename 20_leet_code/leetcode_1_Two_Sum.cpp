#include <vector>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> exist;
        for (int i = nums.size() - 1; i >= 0; --i)
        {
            int num(nums[i]);
            const auto &iter(exist.find(target - num));
            if (iter != exist.end())
            {
                return vector<int>({iter->second, i});
            }
            exist[num] = i;
        }
        return vector<int>();
    }
};