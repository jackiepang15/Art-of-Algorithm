#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int hIndex(vector<int> &citations)
    {
        sort(citations.begin(), citations.end());
        int h(0), size(citations.size());
        for (int i = 0; i < size; ++i)
        {
            h = max(h, min(size - i, citations[i]));
        }
        return h;
    }
};