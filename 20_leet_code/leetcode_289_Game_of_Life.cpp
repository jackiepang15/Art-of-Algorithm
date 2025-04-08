#include <vector>

using namespace std;

class Solution
{
public:
    void gameOfLife(vector<vector<int>> &board)
    {
        vector<vector<int>> next(board);
        int rows(board.size());
        int cols(board.front().size());
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                int neighbors(board[i][j] ? -1 : 0);
                for (int r = -1; r <= 1; ++r)
                {
                    for (int c = -1; c <= 1; ++c)
                    {
                        int rr = r + i;
                        int cc = c + j;
                        if (rr >= 0 && rr < rows && cc >= 0 && cc < cols && board[rr][cc])
                        {
                            ++neighbors;
                        }
                    }
                }
                if (board[i][j])
                {
                    next[i][j] = neighbors == 3 || neighbors == 2 ? 1 : 0;
                }
                else
                {
                    next[i][j] = neighbors == 3 ? 1 : 0;
                }
            }
        }
        board = next;
    }
};