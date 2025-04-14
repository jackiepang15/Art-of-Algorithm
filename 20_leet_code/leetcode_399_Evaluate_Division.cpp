#include <string>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

class Solution
{
public:
    vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
    {
        unordered_map<string, vector<int>> edges;
        int size(equations.size());
        for (int i = 0; i < size; ++i)
        {
            for (const auto &e : equations[i])
            {
                edges[e].push_back(i);
            }
        }
        map<pair<string, string>, double> answers;
        unordered_map<string, bool> visited;
        for (const auto &e : edges)
        {
            const string &n(e.first);
            if (visited.count(n) > 0 && visited[n])
            {
                continue;
            }
            vector<string> vec;
            vec.push_back(n);
            visited[n] = true;
            answers[make_pair(n, n)] = 1.0;
            int start(0);
            while (start < vec.size())
            {
                int size(vec.size());
                for (int i = start; i < size; ++i)
                {
                    string n0(vec[i]);
                    for (const auto &index : edges[n0])
                    {
                        vector<string> &e(equations[index]);
                        string n1(e[0] == n0 ? e[1] : e[0]);
                        if (visited.count(n1) > 0 && visited[n1])
                        {
                            continue;
                        }
                        vec.push_back(n1);
                        visited[n1] = true;
                        double v(answers[make_pair(n, n0)] * (e[0] == n0 ? values[index] : 1.0 / values[index]));
                        answers[make_pair(n, n1)] = v;
                        answers[make_pair(n1, n)] = 1.0 / v;
                        answers[make_pair(n1, n1)] = 1.0;
                    }
                }
                start = size;
            }
            int size(vec.size());
            for (int i = size - 1; i >= 2; --i)
            {
                string &n1(vec[i]);
                for (int j = i - 1; j >= 1; --j)
                {
                    string &n0(vec[j]);
                    double v(answers[make_pair(n, n1)] / answers[make_pair(n, n0)]);
                    answers[make_pair(n0, n1)] = v;
                    answers[make_pair(n1, n0)] = 1.0 / v;
                }
            }
        }
        vector<double> result;
        for (const auto &q : queries)
        {
            pair<string, string> key(make_pair(q[0], q[1]));
            if (answers.count(key) > 0)
            {
                result.push_back(answers[key]);
            }
            else
            {
                result.push_back(-1.0);
            }
        }
        return result;
    }
};
