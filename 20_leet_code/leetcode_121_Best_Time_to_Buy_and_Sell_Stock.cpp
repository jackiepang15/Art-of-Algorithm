#include <vector>

using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int profit(0);
        if (prices.empty())
        {
            return profit;
        }
        int size(prices.size()), buy(prices.front());
        for (int i = 1; i < size; ++i)
        {
            int sell(prices[i]);
            if (sell >= buy)
            {
                profit = max(profit, sell - buy);
            }
            else
            {
                buy = sell;
            }
        }
        return profit;
    }
};
