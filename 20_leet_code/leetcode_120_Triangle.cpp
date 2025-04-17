#include <vector>

using namespace std;

class Solution
{
public:
    int minimumTotal(vector<vector<int>> &triangle)
    {
        int size(triangle.size());
        vector<int> pathPrev(1);
        pathPrev[0] = triangle[0][0];
        for (int i = 1; i < size; ++i)
        {
            vector<int> path(i + 1);
            path[0] = pathPrev[0] + triangle[i][0];
            for (int j = 1; j < i; ++j)
            {
                path[j] = min(pathPrev[j - 1], pathPrev[j]) + triangle[i][j];
            }
            path[i] = pathPrev[i - 1] + triangle[i][i];
            pathPrev = path;
        }
        int minPath(pathPrev[0]);
        for (int i = 1; i < size; ++i)
        {
            minPath = min(minPath, pathPrev[i]);
        }
        return minPath;
    }
};