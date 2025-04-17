#include <vector>

using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        if (prices.empty())
        {
            return 0;
        }
        vector<int> leftValue(prices.size());
        int leftCurrent(0);
        for (int i = 1; i < prices.size(); ++i)
        {
            leftCurrent += prices[i] - prices[i - 1];
            leftValue[i] = max(leftValue[i - 1], leftCurrent);
            if (leftCurrent < 0)
            {
                leftCurrent = 0;
            }
        }
        vector<int> rightValue(prices.size());
        int rightCurrent(0);
        for (int i = prices.size() - 1; i > 0; --i)
        {
            rightCurrent += prices[i] - prices[i - 1];
            rightValue[i - 1] = max(rightValue[i], rightCurrent);
            if (rightCurrent < 0)
            {
                rightCurrent = 0;
            }
        }
        int maxValue(rightValue[0]);
        for (int k = 1; k < prices.size(); ++k)
        {
            maxValue = max(maxValue, leftValue[k - 1] + rightValue[k]);
        }
        return maxValue;
    }
};