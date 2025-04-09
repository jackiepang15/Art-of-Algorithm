#include <vector>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {
        unordered_map<int, int> position;
        for (int i = nums.size() - 1; i >= 0; --i)
        {
            int num(nums[i]);
            const auto &iter(position.find(num));
            if (iter != position.end())
            {
                if (iter->second - i <= k)
                {
                    return true;
                }
            }
            position[num] = i;
        }
        return false;
    }
};