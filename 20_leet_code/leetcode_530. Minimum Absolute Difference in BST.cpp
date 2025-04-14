#include <vector>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    int getMinimumDifference(TreeNode *root)
    {
        vector<TreeNode *> vec;
        vector<TreeNode *> q(1, root);
        while (q.size() > 0)
        {
            TreeNode *n(q.back());
            if (n->left)
            {
                q.push_back(n->left);
                n->left = nullptr;
                continue;
            }
            vec.push_back(q.back());
            q.pop_back();
            if (n->right)
            {
                q.push_back(n->right);
                n->right = nullptr;
            }
        }
        int minDiff(100000);
        for (int i = vec.size() - 2; i >= 0; --i)
        {
            int diff(vec[i + 1]->val - vec[i]->val);
            minDiff = min(minDiff, diff);
        }
        return minDiff;
    }
};