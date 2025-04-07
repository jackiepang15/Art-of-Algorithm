#include <vector>

using namespace std;

class Solution
{
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int size(gas.size());
        for (int i = 0; i < size;)
        {
            int tank(0);
            int k = i;
            for (int j = 0; j < size && tank >= 0; ++j)
            {
                k = (i + j) % size;
                tank += gas[k] - cost[k];
            }
            if (tank >= 0)
            {
                return i;
            }
            if (k < i)
            {
                return -1;
            }
            if (k > i)
            {
                i = k;
            }
            else
            {
                ++i;
            }
        }
        return -1;
    }
};
