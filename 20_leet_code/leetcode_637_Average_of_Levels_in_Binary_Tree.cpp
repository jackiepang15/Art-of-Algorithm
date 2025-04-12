#include <vector>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    vector<double> averageOfLevels(TreeNode *root)
    {
        vector<double> result;
        if (root == nullptr)
        {
            return result;
        }
        vector<TreeNode *> vec;
        int start(vec.size());
        vec.push_back(root);
        while (start < vec.size())
        {
            int size(vec.size());
            double val(0.0);
            for (int i = start; i < size; ++i)
            {
                TreeNode *n(vec[i]);
                val += n->val;
                if (n->left)
                {
                    vec.push_back(n->left);
                }
                if (n->right)
                {
                    vec.push_back(n->right);
                }
            }
            result.push_back(val / (size - start));
            start = size;
        }
        return result;
    }
};