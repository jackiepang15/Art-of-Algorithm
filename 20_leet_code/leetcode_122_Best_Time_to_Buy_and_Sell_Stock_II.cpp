#include <vector>

using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int prpfit(0);
        if (prices.empty())
        {
            return prpfit;
        }
        int size(prices.size());
        for (int i = 1; i < size; ++i)
        {
            int delta(prices[i] - prices[i - 1]);
            if (delta > 0)
            {
                prpfit += delta;
            }
        }
        return prpfit;
    }
};