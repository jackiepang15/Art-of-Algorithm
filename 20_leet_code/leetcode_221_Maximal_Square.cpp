#include <vector>

using namespace std;

class Solution
{
public:
    int maximalSquare(vector<vector<char>> &matrix)
    {
        int rows(matrix.size()), cols(matrix.front().size());
        vector<vector<int>> area(rows + 1, vector<int>(cols + 1));
        for (int r = 1; r <= rows; ++r)
        {
            for (int c = 1; c <= cols; ++c)
            {
                area[r][c] = area[r][c - 1] + area[r - 1][c] - area[r - 1][c - 1] + (matrix[r - 1][c - 1] - '0');
            }
        }
        vector<vector<int>> maxSize(rows, vector<int>(cols));
        int maxArea(0);
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < cols; ++c)
            {
                if (matrix[r][c] == '0')
                {
                    maxSize[r][c] = 0;
                }
                else
                {
                    maxSize[r][c] = 1;
                    if (r > 0 && c > 0)
                    {
                        int size(maxSize[r - 1][c - 1]);
                        for (int s = size; s >= 1; --s)
                        {
                            if (((area[r][c + 1] - area[r - s][c + 1]) - (area[r][c] - area[r - s][c]) == s) && ((area[r + 1][c] - area[r + 1][c - s]) - (area[r][c] - area[r][c - s]) == s))
                            {
                                maxSize[r][c] = s + 1;
                                break;
                            }
                        }
                    }
                    int a = maxSize[r][c] * maxSize[r][c];
                    if (a > maxArea)
                    {
                        maxArea = a;
                    }
                }
            }
        }
        return maxArea;
    }
};