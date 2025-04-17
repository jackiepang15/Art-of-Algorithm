#include <vector>

using namespace std;

class Solution
{
public:
    int minPathSum(vector<vector<int>> &grid)
    {
        int m(grid.size()), n(grid.front().size());
        vector<vector<int>> minSum(m, vector<int>(n));
        minSum[0][0] = grid[0][0];
        for (int j = 1; j < n; ++j)
        {
            minSum[0][j] = minSum[0][j - 1] + grid[0][j];
        }
        for (int i = 1; i < m; ++i)
        {
            minSum[i][0] = minSum[i - 1][0] + grid[i][0];
            for (int j = 1; j < n; ++j)
            {
                minSum[i][j] = min(minSum[i][j - 1], minSum[i - 1][j]) + grid[i][j];
            }
        }
        return minSum[m - 1][n - 1];
    }
};