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
    bool hasPathSum(TreeNode *root, int targetSum)
    {
        if (root == nullptr)
        {
            return false;
        }
        int target(targetSum - root->val);
        if (root->left == nullptr && root->right == nullptr)
        {
            return target == 0;
        }
        if (root->left && hasPathSum(root->left, target))
        {
            return true;
        }
        if (root->right && hasPathSum(root->right, target))
        {
            return true;
        }
        return false;
    }
};