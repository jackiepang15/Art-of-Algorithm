#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> out(numCourses);
        for (const auto &p : prerequisites)
        {
            out[p[0]].push_back(p[1]);
        }

        vector<int> in(numCourses, 0);
        for (const auto &p : prerequisites)
        {
            in[p[1]]++;
        }

        vector<int> zeros;
        for (int i = 0; i < numCourses; ++i)
        {
            if (in[i] == 0)
            {
                zeros.push_back(i);
            }
        }

        vector<int> res;
        vector<bool> visit(numCourses, false);
        while (res.size() < numCourses)
        {
            if (zeros.empty())
            {
                return vector<int>();
            }
            int z(zeros.back());
            zeros.pop_back();
            res.push_back(z);
            for (const auto &o : out[z])
            {
                if (--in[o] == 0)
                {
                    zeros.push_back(o);
                }
            }
        }

        reverse(res.begin(), res.end());
        return res;
    }
};