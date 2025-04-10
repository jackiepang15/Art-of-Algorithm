#include <vector>
#include <map>
#include <string>

using namespace std;

class Solution
{
public:
    map<char, int> priority = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'(', 3}, {')', 0}};

    bool compare(char o1, char o2)
    {
        if (o1 == '(')
        {
            return false;
        }
        if (o1 == ')')
        {
            return true;
        }
        return priority[o1] >= priority[o2];
    }

    int calculate(string s)
    {
        vector<int> numbers(1);
        vector<char> operators;
        for (auto c : ('(' + s + ')'))
        {
            if (c == ' ')
            {
                continue;
            }
            if (c >= '0' && c <= '9')
            {
                numbers.back() = numbers.back() * 10 + (c - '0');
                continue;
            }
            while (!operators.empty() && compare(operators.back(), c))
            {
                int x(numbers.back());
                numbers.pop_back();
                int y(numbers.back());
                numbers.pop_back();
                char o(operators.back());
                operators.pop_back();
                int z(0);
                switch (o)
                {
                case '+':
                    z = y + x;
                    break;
                case '-':
                    z = y - x;
                    break;
                case '*':
                    z = y * x;
                    break;
                case '/':
                    z = y / x;
                    break;
                default:
                    break;
                }
                numbers.push_back(z);
            }
            if (c == ')')
            {
                operators.pop_back();
            }
            else
            {
                operators.push_back(c);
            }
            if (!(c == '(' || c == ')'))
            {
                numbers.push_back(0);
            }
        }
        return numbers.back();
    }
};