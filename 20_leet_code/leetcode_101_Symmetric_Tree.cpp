struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
public:
    bool isSymmetric(TreeNode *root)
    {
        return root == nullptr || isSymmetric(root->left, root->right);
    }

    bool isSymmetric(TreeNode *left, TreeNode *right)
    {
        if (left == nullptr || right == nullptr)
        {
            return left == right;
        }
        else
        {
            return left->val == right->val && isSymmetric(left->left, right->right) && isSymmetric(left->right, right->left);
        }
    }
};