#include <vector>

using namespace std;

class Solution
{
public:
    int candy(vector<int> &ratings)
    {
        vector<vector<int>> list(20000 + 1);
        int size(ratings.size());
        for (int i = 0; i < size; ++i)
        {
            int r(ratings[i]);
            if ((i > 0 && r > ratings[i - 1]) || (i < size - 1 && r > ratings[i + 1]))
            {
                list[r].push_back(i);
            }
        }
        vector<int> candies(size, 1);
        for (int r = 0; r <= 20000; ++r)
        {
            for (int j = list[r].size() - 1; j >= 0; --j)
            {
                int i(list[r][j]);
                if (i > 0 && r > ratings[i - 1])
                {
                    candies[i] = max(candies[i], candies[i - 1] + 1);
                }
                if (i < size - 1 && r > ratings[i + 1])
                {
                    candies[i] = max(candies[i], candies[i + 1] + 1);
                }
            }
        }
        int result(0);
        for (int i = 0; i < size; ++i)
        {
            result += candies[i];
        }
        return result;
    }
};