#include <vector>

using namespace std;

class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        int start(0), end(height.size() - 1);
        int h(min(height[start], height[end]));
        int area((end - start) * h);
        while (start < end)
        {
            while (start < end && height[start] <= h)
            {
                ++start;
            }
            while (end > start && height[end] <= h)
            {
                --end;
            }
            if (start < end)
            {
                h = min(height[start], height[end]);
                area = max(area, (end - start) * h);
            }
        }
        return area;
    }
};