#include <vector>
#include <map>
#include <set>

using namespace std;

class Solution
{
public:
    int maxPoints(vector<vector<int>> &points)
    {
        map<int, set<int>> verticalLines;
        for (int i = points.size() - 1; i >= 0; --i)
        {
            vector<int> &point(points[i]);
            verticalLines[point[0]].insert(i);
        }
        int maxNumber(0);
        for (auto i = verticalLines.begin(); i != verticalLines.end(); ++i)
        {
            maxNumber = max<int>(maxNumber, i->second.size());
        }
        map<vector<double>, set<int>> otherLines;
        for (int i = points.size() - 1; i >= 1; --i)
        {
            for (int j = i - 1; j >= 0; --j)
            {
                vector<int> &p1(points[i]);
                vector<int> &p2(points[j]);
                if (p1[0] == p2[0])
                {
                    continue;
                }
                double k((double)(p2[1] - p1[1]) / (p2[0] - p1[0]));
                double y(p1[1] - k * p1[0]);
                vector<double> line({k, y});
                otherLines[line].insert(i);
                otherLines[line].insert(j);
            }
        }
        for (auto i = otherLines.begin(); i != otherLines.end(); ++i)
        {
            maxNumber = max<int>(maxNumber, i->second.size());
        }
        return maxNumber;
    }
};