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

    int findMinArrowShots(vector<vector<int>> &points)
    {
        sort(points.begin(), points.end(), compare);
        int size(points.size());
        if (size == 0)
        {
            return -1;
        }
        int count(1);
        vector<int> cur(points[0]);
        for (int i = 1; i < size; ++i)
        {
            if (points[i][0] <= cur[1])
            {
                cur[1] = min(cur[1], points[i][1]);
            }
            else
            {
                cur = points[i];
                ++count;
            }
        }
        return count;
    }
};