#include <utility>

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
    void flatten(TreeNode *root)
    {
        if (root)
        {
            flat(root);
        }
    }

    pair<TreeNode *, TreeNode *> flat(TreeNode *root)
    {
        pair<TreeNode *, TreeNode *> result;
        result.first = root;
        TreeNode *right(root->right);
        if (root->left)
        {
            pair<TreeNode *, TreeNode *> p = flat(root->left);
            root->left = nullptr;
            root->right = p.first;
            root = p.second;
        }
        if (right)
        {
            pair<TreeNode *, TreeNode *> p = flat(right);
            root->left = nullptr;
            root->right = p.first;
            root = p.second;
        }
        result.second = root;
        return result;
    }
};