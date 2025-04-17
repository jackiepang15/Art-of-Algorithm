#include <set>

using namespace std;

class MedianFinder
{
public:
    multiset<int> left, right;

    MedianFinder()
    {
    }

    void addNum(int num)
    {
        if (left.size() <= right.size())
        {
            left.insert(num);
        }
        else
        {
            right.insert(num);
        }
        if (right.size() > 0)
        {
            int leftVal(*prev(left.end()));
            int rightVal(*right.begin());
            if (leftVal > rightVal)
            {
                left.erase(prev(left.end()));
                left.insert(rightVal);
                right.erase(right.begin());
                right.insert(leftVal);
            }
        }
    }

    double findMedian()
    {
        if (left.size() > 0)
        {
            if (left.size() == right.size())
            {
                return (*left.rbegin() + *right.begin()) / 2.0;
            }
            else
            {
                return *left.rbegin();
            }
        }
        else
        {
            return 0.0;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
