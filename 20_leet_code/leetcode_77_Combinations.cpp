#include <vector>

using namespace std;

class Solution
{
public:
    void generate(int n, int k, vector<vector<int>> &combinations,
                  int index, vector<int> &position)
    {
        if (index == k)
        {
            combinations.push_back(position);
        }
        else
        {
            int min = index == 0 ? 1 : position[index - 1] + 1;
            for (int i = min; i <= n; i++)
            {
                position[index] = i;
                generate(n, k, combinations, index + 1, position);
                position[index] = -1;
            }
        }
    }

    vector<vector<int>> combine(int n, int k)
    {
        vector<vector<int>> combinations;
        vector<int> position(k, -1);
        generate(n, k, combinations, 0, position);
        return combinations;
    }
};