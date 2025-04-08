class Solution
{
public:
    int climbStairs(int n)
    {
        if (n < 3)
        {
            return n;
        }
        int x(1), y(2);
        for (int i = 3; i <= n; ++i)
        {
            int z(x + y);
            x = y;
            y = z;
        }
        return y;
    }
};