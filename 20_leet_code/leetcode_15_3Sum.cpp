#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        vector<vector<int>> results;
        sort(nums.begin(), nums.end());
        for (int i = nums.size() - 1; i >= 2; --i)
        {
            if (i < nums.size() - 1 && nums[i] == nums[i + 1])
            {
                continue;
            }
            int target = -nums[i];
            int start(0), end(i - 1);
            while (start < end)
            {
                int sum = nums[start] + nums[end];
                if (sum == target)
                {
                    vector<int> result({nums[i], nums[end], nums[start]});
                    if (results.empty())
                    {
                        results.push_back(result);
                    }
                    else
                    {
                        vector<int> &back(results.back());
                        if (result[1] != back[1] || result[2] != back[2])
                        {
                            results.push_back(result);
                        }
                    }
                    ++start;
                    --end;
                }
                else if (sum < target)
                {
                    ++start;
                }
                else
                {
                    --end;
                }
            }
        }
        return results;
    }
};