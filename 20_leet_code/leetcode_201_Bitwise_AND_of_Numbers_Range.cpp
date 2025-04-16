class Solution
{
public:
    int rangeBitwiseAnd(int left, int right)
    {
        int l(left), r(right);
        int result(0), v(1);
        while (r > 0)
        {
            if (r == l && (r & 1) == 1)
            {
                result += v;
            }
            l >>= 1;
            r >>= 1;
            v <<= 1;
        }
        return result;
    }
};