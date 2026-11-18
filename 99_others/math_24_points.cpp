#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void print(vector<vector<int>> &permutations, int n)
{
    int size = permutations.size();
    for (int i = 0; i < size; ++i)
    {
        vector<int> &permutation = permutations[i];
        cout << i + 1 << ": (" << permutation[0];
        for (int j = 1; j < n; ++j)
        {
            cout << ", " << permutation[j];
        }
        cout << ")" << endl;
    }
}

void next(vector<vector<int>> &permutations, vector<int> &permutation, vector<bool> &used, int m, int n, bool duplicate)
{
    if (permutation.size() == m)
    {
        permutations.push_back(permutation);
    }
    else
    {
        if (duplicate)
        {
            for (int i = 0; i < n; ++i)
            {
                permutation.push_back(i);
                next(permutations, permutation, used, m, n, duplicate);
                permutation.pop_back();
            }
        }
        else
        {

            for (int i = 0; i < n; ++i)
                if (!used[i])
                {
                    permutation.push_back(i);
                    used[i] = true;
                    next(permutations, permutation, used, m, n, duplicate);
                    used[i] = false;
                    permutation.pop_back();
                }
        }
    }
}

int main(int argc, char *argv[])
{
    int n = 4;
    vector<int> a(n, 0);
    for (int i = 0; i < n; ++i)
    {
        cout << "a_" << i + 1 << " = ";
        cin >> a[i];
    }
    vector<vector<int>> persA, persO;
    vector<int> permutation;
    vector<bool> used(n, false);
    next(persA, permutation, used, n, n, false);
    print(persA, n);
    next(persO, permutation, used, n - 1, n, true);
    print(persO, n - 1);
    vector<char> opt = {'+', '-', '*', '/'};
    for (int i = persA.size() - 1; i >= 0; --i)
    {
        for (int j = persO.size() - 1; j >= 0; --j)
        {
            bool valid(true);
            double result(a[persA[i][n - 1]]);
            for (int k = n - 2; k >= 0 && valid; --k)
            {
                double v = a[persA[i][k]];
                switch (opt[persO[j][k]])
                {
                case '+':
                    result += v;
                    break;
                case '-':
                    result -= v;
                    break;
                case '*':
                    result *= v;
                    break;
                case '/':
                    if (abs(v) < 1e-5)
                        valid = false;
                    else
                        result /= v;
                    break;
                default:
                    break;
                }
            }
            if (valid && abs(result - 24) < 1e-5)
            {
                cout << a[persA[i][n - 1]];
                for (int k = n - 2; k >= 0; --k)
                {
                    cout << " " << opt[persO[j][k]] << " " << a[persA[i][k]];
                }
                cout << " = 24" << endl;
            }
        }
    }

        return 0;
}