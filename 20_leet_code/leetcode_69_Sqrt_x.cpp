class Solution
{
public:
    int mySqrt(int x)
    {
        if (x < 2)
        {
            return x;
        }
        int begin(1), end(x - 1);
        while (begin < end)
        {
            int mid((begin + end) / 2);
            if ((mid + 1) <= x / (mid + 1))
            {
                begin = mid + 1;
            }
            else
            {
                end = mid;
            }
        }
        return begin;
    }
};