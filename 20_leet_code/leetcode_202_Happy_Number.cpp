#include <unordered_set>

using namespace std;

class Solution
{
public:
    bool isHappy(int n)
    {
        unordered_set<int> exist;
        while (exist.count(n) == 0)
        {
            exist.insert(n);
            int sum(0);
            while (n > 0)
            {
                int digit(n % 10);
                sum += digit * digit;
                n /= 10;
            }
            n = sum;
        }
        return n == 1;
    }
};