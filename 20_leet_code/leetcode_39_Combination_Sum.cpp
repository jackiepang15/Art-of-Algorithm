#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        vector<vector<int>> results;
        sort(candidates.begin(), candidates.end());
        vector<int> stack;
        while (true)
        {
            int sum(0);
            for (const auto &index : stack)
            {
                sum += candidates[index];
            }
            if (sum < target)
            {
                int index(stack.empty() ? 0 : stack.back());
                if (sum + candidates[index] <= target)
                {
                    stack.push_back(index);
                    continue;
                }
            }
            if (sum == target)
            {
                vector<int> result(stack);
                for (auto &v : result)
                {
                    v = candidates[v];
                }
                results.push_back(result);
            }
            if (stack.size() > 0)
            {
                int index(stack.back());
                while (index == candidates.size() - 1 || sum - candidates[index] + candidates[index + 1] > target)
                {
                    sum -= candidates[stack.back()];
                    stack.pop_back();
                    if (stack.empty())
                    {
                        index = candidates.size() - 1;
                        break;
                    }
                    index = stack.back();
                }
                if (index < candidates.size() - 1 && sum - candidates[index] + candidates[index + 1] <= target)
                {
                    sum -= candidates[stack.back()];
                    stack.pop_back();
                    stack.push_back(index + 1);
                    sum += candidates[stack.back()];
                    continue;
                }
            }
            if (stack.empty())
            {
                break;
            }
        }
        return results;
    }
};
