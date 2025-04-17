#include <vector>

using namespace std;

class Solution
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        if (prices.empty())
        {
            return 0;
        }
        int n = prices.size();
        if (k > n / 2)
        {
            int profit(0);
            for (int i = 1; i < prices.size(); ++i)
            {
                if (prices[i] > prices[i - 1])
                {
                    profit += prices[i] - prices[i - 1];
                }
            }
            return profit;
        }
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(k + 1, vector<int>(2)));
        for (int j = k; j >= 1; j--)
        {
            dp[0][j][0] = 0;
            dp[0][j][1] = -prices[0];
        }
        for (int i = 1; i < n; i++)
        {
            for (int j = k; j >= 1; j--)
            {
                dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);
                dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i]);
            }
        }
        return dp[n - 1][k][0];
    }
};