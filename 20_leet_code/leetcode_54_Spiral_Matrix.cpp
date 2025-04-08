#include <vector>

using namespace std;

class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        vector<pair<int, int>> delta = {
            {0, 1},
            {1, 0},
            {0, -1},
            {-1, 0}};
        int rows = matrix.size();
        int cols = matrix.front().size();
        int r = 1, c = 0, d = 3;
        int number = 0;
        vector<int> result;
        vector<vector<bool>> visit(rows, vector<bool>(cols, false));
        for (int i = rows * cols; i > 0; --i)
        {
            r += delta[d].first;
            c += delta[d].second;
            result.push_back(matrix[r][c]);
            visit[r][c] = true;
            while ((r + delta[d].first < 0 || r + delta[d].first >= rows || c + delta[d].second < 0 || c + delta[d].second >= cols || visit[r + delta[d].first][c + delta[d].second]) && i > 1)
            {
                d = (d + 1) % 4;
            }
        }
        return result;
    }
};