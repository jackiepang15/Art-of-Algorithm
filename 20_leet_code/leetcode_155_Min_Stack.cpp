#include <vector>

using namespace std;

class MinStack
{
    vector<int> stack;
    vector<int> min;

public:
    MinStack()
    {
    }

    void push(int val)
    {
        stack.push_back(val);
        min.push_back(min.empty() ? val : std::min<int>(val, min.back()));
    }

    void pop()
    {
        stack.pop_back();
        min.pop_back();
    }

    int top()
    {
        return stack.empty() ? 0 : stack.back();
    }

    int getMin()
    {
        return min.empty() ? 0 : min.back();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */