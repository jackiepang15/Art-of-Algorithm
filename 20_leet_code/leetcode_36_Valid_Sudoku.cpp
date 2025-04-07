#include <vector>

using namespace std;

class Solution
{
public:
    bool isValidSudoku(vector<vector<char>> &board)
    {
        bool valid(true);
        for (int i = 0; i < 9; ++i)
        {
            vector<bool> contain(9, false);
            for (int j = 0; j < 9; ++j)
            {
                if (board[i][j] == '.')
                {
                    continue;
                }
                int v(board[i][j] - '1');
                if (contain[v])
                {
                    return false;
                }
                contain[v] = true;
            }
        }
        for (int i = 0; i < 9; ++i)
        {
            vector<bool> contain(9, false);
            for (int j = 0; j < 9; ++j)
            {
                if (board[j][i] == '.')
                {
                    continue;
                }
                int v(board[j][i] - '1');
                if (contain[v])
                {
                    return false;
                }
                contain[v] = true;
            }
        }
        vector<pair<int, int>> center = {
            {1, 1},
            {1, 4},
            {1, 7},
            {4, 1},
            {4, 4},
            {4, 7},
            {7, 1},
            {7, 4},
            {7, 7}};
        vector<pair<int, int>> delta = {
            {-1, -1},
            {-1, 0},
            {-1, 1},
            {0, -1},
            {0, 0},
            {0, 1},
            {1, -1},
            {1, 0},
            {1, 1}};
        for (int i = 0; i < 9; ++i)
        {
            vector<bool> contain(9, false);
            for (int j = 0; j < 9; ++j)
            {
                int r = center[i].first + delta[j].first;
                int c = center[i].second + delta[j].second;
                if (board[r][c] == '.')
                {
                    continue;
                }
                int v(board[r][c] - '1');
                if (contain[v])
                {
                    return false;
                }
                contain[v] = true;
            }
        }
        return true;
    }
};