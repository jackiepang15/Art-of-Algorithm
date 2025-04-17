#include <vector>

using namespace std;

class Solution
{
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        int m(obstacleGrid.size()), n(obstacleGrid.front().size());
        vector<vector<int>> paths(m, vector<int>(n));
        if (obstacleGrid[0][0])
        {
            return 0;
        }
        paths[0][0] = 1;
        for (int j = 1; j < n; ++j)
        {
            if (!obstacleGrid[0][j])
            {
                paths[0][j] = paths[0][j - 1];
            }
        }
        for (int i = 1; i < m; ++i)
        {
            if (!obstacleGrid[i][0])
            {
                paths[i][0] = paths[i - 1][0];
            }
            for (int j = 1; j < n; ++j)
            {
                if (!obstacleGrid[i][j])
                {
                    paths[i][j] = paths[i][j - 1] + paths[i - 1][j];
                }
            }
        }
        return paths[m - 1][n - 1];
    }
};