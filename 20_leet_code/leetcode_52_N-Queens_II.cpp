#include <vector>

using namespace std;

class Solution
{
public:
    vector<bool> row;
    vector<bool> column;
    vector<bool> left;
    vector<bool> right;

    int totalNQueens(int n)
    {
        column.resize(n, true);
        left.resize(2 * n - 1, true);
        right.resize(2 * n - 1, true);
        int result(0);
        vector<int> position;
        search(position, n, result);
        return result;
    }

    void search(vector<int> &position, int n, int &result)
    {
        if (position.size() == n)
        {
            ++result;
        }
        else
        {
            int r(position.size());
            for (int c = 0; c < n; ++c)
            {
                if (column[c] && left[r - c + n - 1] && right[r + c])
                {
                    column[c] = false;
                    left[r - c + n - 1] = false;
                    right[r + c] = false;
                    position.push_back(c);
                    search(position, n, result);
                    position.pop_back();
                    column[c] = true;
                    left[r - c + n - 1] = true;
                    right[r + c] = true;
                }
            }
        }
    }
};