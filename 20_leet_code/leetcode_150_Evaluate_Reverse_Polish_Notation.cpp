#include <vector>
#include <string>
#include <set>

using namespace std;

class Solution
{
public:
    int evalRPN(vector<string> &tokens)
    {
        set<string> operators({"+", "-", "*", "/"});
        vector<string> stack;
        for (const auto &t : tokens)
        {
            if (operators.count(t) == 0)
            {
                stack.push_back(t);
            }
            else
            {
                int y(stoi(stack.back()));
                stack.pop_back();
                int x(stoi(stack.back()));
                stack.pop_back();
                if (t.compare("+") == 0)
                {
                    stack.push_back(to_string(x + y));
                }
                else if (t.compare("-") == 0)
                {
                    stack.push_back(to_string(x - y));
                }
                else if (t.compare("*") == 0)
                {
                    stack.push_back(to_string(x * y));
                }
                else
                {
                    stack.push_back(to_string(x / y));
                }
            }
        }
        return stoi(stack.back());
    }
};