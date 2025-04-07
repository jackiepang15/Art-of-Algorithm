#include <vector>

using namespace std;

class Solution
{
public:
    void rotate(vector<vector<int>> &matrix)
    {
        vector<vector<int>> m(matrix);
        int n(matrix.size());
        for (int r = 0; r < n; ++r)
        {
            for (int c = 0; c < n; ++c)
            {
                int y = n - 1 - r;
                int x = c;
                m[n - 1 - y][x] = matrix[n - 1 - x][-y + n - 1];
            }
        }
        matrix = m;
    }
};
