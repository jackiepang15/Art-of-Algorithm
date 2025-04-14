#include <vector>
#include <map>
#include <string>
#include <limits>

using namespace std;

class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        vector<pair<int, int>> directions = {
            make_pair(1, 0),
            make_pair(0, 1),
            make_pair(-1, 0),
            make_pair(0, -1)};
        int rows(grid.size()), cols(grid.front().size());
        vector<vector<bool>> visited(rows, vector<bool>(cols));
        int num(0);
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < cols; ++c)
            {
                if (visited[r][c] || grid[r][c] == '0')
                {
                    continue;
                }
                ++num;
                vector<pair<int, int>> positions(1, make_pair(r, c));
                visited[r][c] = true;
                while (positions.size() > 0)
                {
                    pair<int, int> p(positions.back());
                    positions.pop_back();
                    for (const auto &d : directions)
                    {
                        int rr(p.first + d.first);
                        int cc(p.second + d.second);
                        if (rr < 0 || rr >= rows || cc < 0 || cc >= cols || visited[rr][cc] || grid[rr][cc] == '0')
                        {
                            continue;
                        }
                        positions.push_back(make_pair(rr, cc));
                        visited[rr][cc] = true;
                    }
                }
            }
        }
        return num;
    }
};