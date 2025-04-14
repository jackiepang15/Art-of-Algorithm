#include <vector>
#include <limits>

using namespace std;

class Solution
{
public:
    vector<int> indexToPosition(int n, int index)
    {
        int row = (n - 1 - index / n);
        int col = (n - 1 - row) % 2 == 0 ? index % n : n - 1 - index % n;
        return vector<int>({row, col});
    }

    int snakesAndLadders(vector<vector<int>> &board)
    {
        int n(board.size());
        int size(n * n);
        vector<int> starts(size);
        vector<vector<int>> ends(size);
        for (int i = 0; i < size; ++i)
        {
            vector<int> position(indexToPosition(n, i));
            int row = position[0];
            int col = position[1];
            int start = board[row][col];
            if (start != -1)
            {
                ends[board[row][col] - 1].push_back(i);
            }
            starts[i] = start;
        }
        vector<int> steps(size, numeric_limits<int>::max());
        steps[0] = 0;
        bool changed(true);
        while (changed)
        {
            changed = false;
            for (int i = 1; i < size; ++i)
            {
                for (const auto &index : ends[i])
                {
                    if (index != -1)
                    {
                        for (int j = 1; j <= 6; ++j)
                        {
                            if (index < j || steps[index - j] == numeric_limits<int>::max())
                            {
                                continue;
                            }
                            int step = steps[index - j] + 1;
                            if (step < steps[i])
                            {
                                steps[i] = step;
                                changed = true;
                            }
                        }
                    }
                }
                if (starts[i] != -1)
                {
                    continue;
                }
                for (int j = 1; j <= 6; ++j)
                {
                    if (i < j || steps[i - j] == numeric_limits<int>::max())
                    {
                        continue;
                    }
                    int step = steps[i - j] + 1;
                    if (step < steps[i])
                    {
                        steps[i] = step;
                        changed = true;
                    }
                }
            }
        }
        return steps[size - 1] == numeric_limits<int>::max() ? -1 : steps[size - 1];
    }
};