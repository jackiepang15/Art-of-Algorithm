#include <vector>

using namespace std;

class Solution
{
public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        int rows(matrix.size());
        int cols(matrix.front().size());
        bool firstRow(matrix[0][0] == 0);
        for (int i = 1; i < cols; ++i)
        {
            firstRow |= matrix[0][i] == 0;
            bool zero(false);
            for (int j = 0; j < rows; ++j)
            {
                zero |= matrix[j][i] == 0;
            }
            if (zero)
            {
                matrix[0][i] = 0;
            }
        }
        bool firstCol(matrix[0][0] == 0);
        for (int i = 1; i < rows; ++i)
        {
            firstCol |= matrix[i][0] == 0;
            bool zero(false);
            for (int j = 0; j < cols; ++j)
            {
                zero |= matrix[i][j] == 0;
            }
            if (zero)
            {
                matrix[i][0] = 0;
            }
        }
        for (int i = 1; i < rows; ++i)
        {
            for (int j = 1; j < cols; ++j)
            {
                if (matrix[0][j] == 0 || matrix[i][0] == 0)
                {
                    matrix[i][j] = 0;
                }
            }
        }
        if (firstRow)
        {
            for (int i = 0; i < cols; ++i)
            {
                matrix[0][i] = 0;
            }
        }
        if (firstCol)
        {
            for (int i = 0; i < rows; ++i)
            {
                matrix[i][0] = 0;
            }
        }
    }
};