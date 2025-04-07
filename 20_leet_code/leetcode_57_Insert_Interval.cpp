#include <vector>

using namespace std;

class Solution
{
public:
    vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
    {
        vector<vector<int>> result;
        vector<int> current(newInterval);
        int size(intervals.size());
        for (int i = 0; i < size; ++i)
        {
            if (!current.empty())
            {
                if (current[1] < intervals[i][0])
                {
                    result.push_back(current);
                    current.clear();
                    result.push_back(intervals[i]);
                }
                else if (current[0] > intervals[i][1])
                {
                    result.push_back(intervals[i]);
                }
                else
                {
                    current[0] = min(current[0], intervals[i][0]);
                    current[1] = max(current[1], intervals[i][1]);
                }
            }
            else
            {
                result.push_back(intervals[i]);
            }
        }
        if (!current.empty())
        {
            result.push_back(current);
            current.clear();
        }
        return result;
    }
};