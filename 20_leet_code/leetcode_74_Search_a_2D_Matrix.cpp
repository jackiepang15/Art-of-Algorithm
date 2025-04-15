#include <vector>

using namespace std;

class Solution
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        int rows(matrix.size());
        int cols(matrix.front().size());
        int begin(0);
        if (matrix[0][0] > target)
        {
            return false;
        }
        int end(rows * cols - 1);
        if (matrix[rows - 1][cols - 1] < target)
        {
            return false;
        }
        while (begin < end)
        {
            int mid((begin + end) / 2);
            int r(mid / cols), c(mid % cols);
            if (matrix[r][c] < target)
            {
                begin = mid + 1;
            }
            else
            {
                end = mid;
            }
        }
        return matrix[begin / cols][begin % cols] == target;
    }
};