#include <vector>

using namespace std;

class Solution
{
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        if (prerequisites.empty())
        {
            return true;
        }
        vector<vector<int>> edges(numCourses);
        for (const auto &p : prerequisites)
        {
            edges[p[0]].push_back(p[1]);
        }
        for (int i = 0; i < numCourses; ++i)
        {
            if (edges[i].empty())
            {
                continue;
            }
            vector<bool> visited(numCourses);
            vector<int> vec;
            vec.push_back(i);
            visited[i] = true;
            while (vec.size() > 0)
            {
                int node(vec.back());
                vec.pop_back();
                for (const auto &e : edges[node])
                {
                    if (e == i)
                    {
                        return false;
                    }
                    if (visited[e])
                    {
                        continue;
                    }
                    vec.push_back(e);
                    visited[e] = true;
                }
            }
        }
        return true;
    }
};