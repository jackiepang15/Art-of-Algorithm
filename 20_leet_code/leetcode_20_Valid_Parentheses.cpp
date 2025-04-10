#include <string>
#include <stack>

using namespace std;

class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> q;
        for (const auto &c : s)
        {
            if (c == '(' || c == '[' || c == '{')
            {
                q.push(c);
            }
            else
            {
                if (q.empty())
                {
                    return false;
                }
                char t(q.top());
                if ((t != '(' && c == ')') || (t != '[' && c == ']') || (t != '{' && c == '}'))
                {
                    return false;
                }
                q.pop();
            }
        }
        return q.empty();
    }
};