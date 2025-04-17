#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    vector<pair<int, int>> directions;
    int rows, cols;

    bool search(vector<vector<char>> &board, const string &word, vector<int> &path, vector<int> &visit)
    {
        if (path.size() == word.size())
        {
            return true;
        }

        int index(path.back());
        int row(index / cols);
        int col(index % cols);
        for (int i = 0; i < 4; ++i)
        {
            int r(row + directions[i].first);
            int c(col + directions[i].second);
            int idx(r * cols + c);
            if (r >= 0 && r < rows && c >= 0 && c < cols &&
                !visit[idx] && board[r][c] == word[path.size()])
            {
                visit[idx] = true;
                path.push_back(idx);
                int ret = search(board, word, path, visit);
                if (ret)
                {
                    return true;
                }
                path.pop_back();
                visit[idx] = false;
            }
        }
        return false;
    }

    bool exist(vector<vector<char>> &board, string word)
    {
        if (board.empty() || word.empty())
        {
            return false;
        }

        directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        rows = board.size();
        cols = board.front().size();

        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < cols; ++c)
            {
                if (board[r][c] == word.front())
                {
                    vector<int> path(0);
                    vector<int> visit(rows * cols, false);
                    int index(r * cols + c);
                    visit[index] = true;
                    path.push_back(index);
                    int ret = search(board, word, path, visit);
                    if (ret)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};