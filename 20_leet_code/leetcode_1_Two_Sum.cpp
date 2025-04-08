#include <vector>
#include <algorithm>

using namespace std;

bool compare(pair<int, int> i, pair<int, int> j)
{
    return i.second < j.second;
}

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        vector<pair<int, int>> numbers;
        int index(0);
        for (auto num : nums)
        {
            numbers.push_back(pair<int, int>(index++, num));
        }

        sort(numbers.begin(), numbers.end(), compare);
        int first(0);
        int second(numbers.size() - 1);
        while (true)
        {
            while (numbers[first].second + numbers[second].second < target)
            {
                ++first;
            }
            while (numbers[first].second + numbers[second].second > target)
            {
                --second;
            }
            if (numbers[first].second + numbers[second].second == target)
            {
                return vector<int>({numbers[first].first, numbers[second].first});
            }
        }
    }
};