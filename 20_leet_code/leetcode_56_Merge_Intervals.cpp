#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    static bool compare(vector<int> &x, vector<int> &y)
    {
        return x[0] < y[0] || (x[0] == y[0] && x[1] < y[1]);
    }

    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end(), compare);
        vector<vector<int>> result;
        int size(intervals.size());
        vector<int> current(intervals[0]);
        for (int i = 1; i < size; ++i)
        {
            if (intervals[i][0] <= current[1])
            {
                current[1] = max(current[1], intervals[i][1]);
            }
            else
            {
                result.push_back(current);
                current = intervals[i];
            }
        }
        result.push_back(current);
        return result;
    }
};