#include <vector>
#include <map>
#include <limits>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k)
    {
        multimap<int, int, greater<int>> m;
        int maxSum(numeric_limits<int>::max());
        int min2(*min_element(nums2.begin(), nums2.end()));
        for (const auto &n1 : nums1)
        {
            if (n1 + min2 >= maxSum)
            {
                break;
            }
            for (const auto &n2 : nums2)
            {
                int sum(n1 + n2);
                if (sum >= maxSum)
                {
                    break;
                }
                m.insert(make_pair(sum, n1));
                if (m.size() > k)
                {
                    m.erase(m.begin());
                    maxSum = m.begin()->first;
                }
            }
        }
        vector<vector<int>> results;
        for (auto i = m.rbegin(); i != m.rend(); ++i)
        {
            int sum(i->first), n1(i->second);
            results.push_back({n1, sum - n1});
        }
        return results;
    }
};