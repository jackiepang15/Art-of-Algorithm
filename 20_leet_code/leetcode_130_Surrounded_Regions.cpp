#include <vector>

using namespace std;

class Solution
{
public:
    void solve(vector<vector<char>> &board)
    {
        vector<pair<int, int>> directions = {
            make_pair(1, 0),
            make_pair(0, 1),
            make_pair(-1, 0),
            make_pair(0, -1)};
        int rows(board.size()), cols(board.front().size());
        vector<vector<bool>> visited(rows, vector<bool>(cols));
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < cols; ++c)
            {
                if (visited[r][c] || board[r][c] == 'X')
                {
                    continue;
                }
                bool edge(r == 0 || r == rows - 1 || c == 0 || c == cols - 1);
                vector<pair<int, int>> positions(1, make_pair(r, c));
                visited[r][c] = true;
                int start(0);
                while (start < positions.size())
                {
                    int size(positions.size());
                    for (int i = start; i < size; ++i)
                    {
                        pair<int, int> p(positions[i]);
                        for (const auto &d : directions)
                        {
                            int rr(p.first + d.first);
                            int cc(p.second + d.second);
                            if (rr < 0 || rr >= rows || cc < 0 || cc >= cols || visited[rr][cc] || board[rr][cc] == 'X')
                            {
                                continue;
                            }
                            positions.push_back(make_pair(rr, cc));
                            visited[rr][cc] = true;
                            if (rr == 0 || rr == rows - 1 || cc == 0 || cc == cols - 1)
                            {
                                edge = true;
                            }
                        }
                    }
                    start = size;
                }
                if (!edge)
                {
                    for (const auto &p : positions)
                    {
                        board[p.first][p.second] = 'X';
                    }
                }
            }
        }
    }
};