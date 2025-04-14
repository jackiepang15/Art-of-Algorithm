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
    int kthSmallest(TreeNode *root, int k)
    {
        if (root)
        {
            int c = count(root->left);
            if (k <= c)
            {
                return kthSmallest(root->left, k);
            }
            else if (k == c + 1)
            {
                return root->val;
            }
            else
            {
                return kthSmallest(root->right, k - (c + 1));
            }
        }
        else
        {
            return 0;
        }
    }

    int count(TreeNode *root)
    {
        return root ? 1 + count(root->left) + count(root->right) : 0;
    }
};