#include <vector>

using namespace std;

class Solution
{
public:
    vector<int> plusOne(vector<int> &digits)
    {
        int i = digits.size() - 1;
        ++digits[i];
        while (i > 0 && digits[i] > 9)
        {
            int d(digits[i] / 10);
            digits[i] = digits[i] % 10;
            --i;
            digits[i] += d;
        }
        if (i == 0 && digits[i] > 9)
        {
            int d(digits[i] / 10);
            digits[i] = digits[i] % 10;
            digits.insert(digits.begin(), d);
        }
        return digits;
    }
};