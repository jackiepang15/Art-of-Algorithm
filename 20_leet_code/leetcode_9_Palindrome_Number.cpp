#include <vector>

using namespace std;

class Solution
{
public:
    bool isPalindrome(int x)
    {
        if (x < 0)
        {
            return false;
        }
        vector<int> digits;
        while (x > 0)
        {
            digits.push_back(x % 10);
            x /= 10;
        }
        int start(0), end(digits.size() - 1);
        while (start <= end)
        {
            if (digits[start] != digits[end])
            {
                return false;
            }
            ++start;
            --end;
        }
        return true;
    }
};