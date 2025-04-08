#include <vector>

using namespace std;

class Solution
{
public:
    int trap(vector<int> &height)
    {
        int maxHeight(-1), maxIndex(-1);
        int size(height.size());
        for (int i = 0; i < size; ++i)
        {
            int h(height[i]);
            if (h > maxHeight)
            {
                maxHeight = h;
                maxIndex = i;
            }
        }
        int result(0), peak(-1);
        peak = 0;
        for (int i = 0; i < maxIndex; ++i)
        {
            int h(height[i]);
            if (h > peak)
            {
                peak = h;
            }
            result += peak - h;
        }
        peak = 0;
        for (int i = size - 1; i > maxIndex; --i)
        {
            int h(height[i]);
            if (h > peak)
            {
                peak = h;
            }
            result += peak - h;
        }
        return result;
    }
};