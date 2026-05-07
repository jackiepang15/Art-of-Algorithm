#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution
{
    const double EPS = 1e-6;

    // 尝试对 a 和 b 进行 6 种运算，结果存入 res
    // 返回生成的有效结果数量
    inline int get_ops(double a, double b, double res[])
    {
        res[0] = a + b;
        res[1] = a - b;
        res[2] = b - a;
        res[3] = a * b;
        int count = 4;
        if (abs(b) > EPS)
            res[count++] = a / b;
        if (abs(a) > EPS)
            res[count++] = b / a;
        return count;
    }

    bool check(double nums[])
    {
        double a = nums[0], b = nums[1], c = nums[2], d = nums[3];
        double res1[6], res2[6], res3[6];

        // --- 拓扑 A: ((a op b) op c) op d ---
        int cnt1 = get_ops(a, b, res1);
        for (int i = 0; i < cnt1; ++i)
        {
            int cnt2 = get_ops(res1[i], c, res2);
            for (int j = 0; j < cnt2; ++j)
            {
                int cnt3 = get_ops(res2[j], d, res3);
                for (int k = 0; k < cnt3; ++k)
                {
                    if (abs(res3[k] - 24) < EPS)
                        return true;
                }
            }
        }

        // --- 拓扑 B: (a op b) op (c op d) ---
        // 注意：由于 next_permutation 会遍历所有排列，
        // 我们只需要检查 (a op b) 和 (c op d) 的组合即可覆盖所有情况
        cnt1 = get_ops(a, b, res1);
        int cnt_pair = get_ops(c, d, res2);
        for (int i = 0; i < cnt1; ++i)
        {
            for (int j = 0; j < cnt_pair; ++j)
            {
                int cnt3 = get_ops(res1[i], res2[j], res3);
                for (int k = 0; k < cnt3; ++k)
                {
                    if (abs(res3[k] - 24) < EPS)
                        return true;
                }
            }
        }
        return false;
    }

public:
    bool judgePoint24(vector<int> &nums)
    {
        // 先排序以配合 next_permutation
        sort(nums.begin(), nums.end());
        double d_nums[4];
        for (int i = 0; i < 4; ++i)
            d_nums[i] = (double)nums[i];

        // 遍历 4! = 24 种全排列
        do
        {
            if (check(d_nums))
                return true;
        } while (next_permutation(d_nums, d_nums + 4));

        return false;
    }
};

int main(int argc, char *argv[])
{
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
    cout << "Can the numbers " << nums[0] << ", " << nums[1] << ", " << nums[2] << ", " << nums[3] << " be used to get 24? " << (result ? "Yes" : "No") << endl;
    return 0;
}
