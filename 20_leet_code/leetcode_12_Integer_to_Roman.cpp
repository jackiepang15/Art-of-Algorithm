#include <vector>
#include <string>

using namespace std;

class Solution
{
    vector<char> one = {
        'I', 'X', 'C', 'M'};
    vector<char> five = {
        'V', 'L', 'D'};

public:
    string intToRoman(int num)
    {
        vector<int> digits;
        while (num > 0)
        {
            int digit = num % 10;
            digits.push_back(digit);
            num /= 10;
        }
        string result;
        int size(digits.size());
        for (int i = size - 1; i >= 0; --i)
        {
            int digit = digits[i];
            if (digit == 9)
            {
                result.push_back(one[i]);
                result.push_back(one[i + 1]);
            }
            else if (digit == 4)
            {
                result.push_back(one[i]);
                result.push_back(five[i]);
            }
            else
            {
                if (digit >= 5)
                {
                    result.push_back(five[i]);
                    digit -= 5;
                }
                while (digit > 0)
                {
                    result.push_back(one[i]);
                    digit -= 1;
                }
            }
        }
        return result;
    }
};