class Solution
{
public:
    double myPow(double x, int n)
    {
        if (x == 0.0)
        {
            return 0.0;
        }
        double ret(1.0);
        double p(n > 0 ? x : 1.0 / x);
        while (n != 0)
        {
            if (n % 2 != 0)
            {
                ret *= p;
            }
            p *= p;
            n /= 2;
        }
        return ret;
    }
};