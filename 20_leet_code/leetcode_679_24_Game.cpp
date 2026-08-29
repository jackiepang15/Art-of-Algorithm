#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

class Solution
{
    const double EPS = 1e-6;

    struct Node
    {
        double val;
        string expr;
    };

    // generate all possible operations between two nodes
    void get_ops(const Node &a, const Node &b, vector<Node> &res)
    {
        res.push_back({a.val + b.val, "(" + a.expr + " + " + b.expr + ")"});
        res.push_back({a.val - b.val, "(" + a.expr + " - " + b.expr + ")"});
        res.push_back({b.val - a.val, "(" + b.expr + " - " + a.expr + ")"});
        res.push_back({a.val * b.val, "(" + a.expr + " * " + b.expr + ")"});
        if (abs(b.val) > EPS)
            res.push_back({a.val / b.val, "(" + a.expr + " / " + b.expr + ")"});
        if (abs(a.val) > EPS)
            res.push_back({b.val / a.val, "(" + b.expr + " / " + a.expr + ")"});
    }

    void print_solutions(const set<string> &solutions)
    {
        if (solutions.empty())
        {
            cout << "No solution found." << endl;
        }
        else
        {
            cout << "Find " << solutions.size() << " different solutions:" << endl;
            for (const string &s : solutions)
            {
                cout << s << " = 24" << endl;
            }
        }
    }

public:
    bool judgePoint24(vector<int> &nums)
    {
        return !solve(nums).empty();
    }

    set<string> solve(vector<int> &nums)
    {
        set<string> solutions; // used for result deduplication
        sort(nums.begin(), nums.end());

        do
        {
            vector<Node> d(4);
            for (int i = 0; i < 4; ++i)
                d[i] = {(double)nums[i], to_string(nums[i])};

            // --- Topology A: ((a op b) op c) op d ---
            vector<Node> res1, res2, res3;
            get_ops(d[0], d[1], res1);
            for (auto &n1 : res1)
            {
                res2.clear();
                get_ops(n1, d[2], res2);
                for (auto &n2 : res2)
                {
                    res3.clear();
                    get_ops(n2, d[3], res3);
                    for (auto &n3 : res3)
                    {
                        if (abs(n3.val - 24) < EPS)
                            solutions.insert(n3.expr);
                    }
                }
            }

            // --- Topology B: (a op b) op (c op d) ---
            res1.clear();
            vector<Node> res_pair;
            get_ops(d[0], d[1], res1);
            get_ops(d[2], d[3], res_pair);
            for (auto &nL : res1)
            {
                for (auto &nR : res_pair)
                {
                    res3.clear();
                    get_ops(nL, nR, res3);
                    for (auto &n3 : res3)
                    {
                        if (abs(n3.val - 24) < EPS)
                            solutions.insert(n3.expr);
                    }
                }
            }
        } while (next_permutation(nums.begin(), nums.end()));
        return solutions;
    }
};

int main(int argc, char *argv[])
{
    Solution solution;
    int max = 10;
    int count = 0;

    map<int, vector<pair<vector<int>, string>>> all_solutions;
    for (int i = 1; i <= max; ++i)
    {
        for (int j = i; j <= max; ++j)
        {
            for (int k = j; k <= max; ++k)
            {
                for (int l = k; l <= max; ++l)
                {
                    vector<int> nums = {i, j, k, l};
                    set<string> solutions(solution.solve(nums));
                    if (!solutions.empty())
                    {
                        all_solutions[solutions.size()].push_back({nums, *solutions.begin()});
                    }
                }
            }
        }
    }

    for (auto it = all_solutions.begin(); it != all_solutions.end(); ++it)
    {
        int num_solutions = it->first;
        const auto &entries = it->second;
        cout << num_solutions << " solution(s): " << entries.size() << " combination(s)" << endl;
        
        for (const auto &entry : entries)
        {
            const vector<int> &nums = entry.first;
            const string &expr = entry.second;
            cout << " (" << nums[0] << ", " << nums[1]
                 << ", " << nums[2] << ", " << nums[3]
                 << ") - " << expr << endl;
            count++;
        }
    }
    /*
    int n = 4;
    vector<int> nums(n);
    cout << "Please input " << n << " numbers." << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << "Number " << i + 1 << ": ";
        cin >> nums[i];
    }
    Solution solution;
    bool result = solution.judgePoint24(nums);
    return 0;
    */
}
