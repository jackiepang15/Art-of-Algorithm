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
    int sumNumbers(TreeNode *root)
    {
        return sumNumbers(root, 0);
    }

    int sumNumbers(TreeNode *root, int number)
    {
        if (root)
        {
            number = number * 10 + root->val;
            if (root->left || root->right)
            {
                int sum(0);
                if (root->left)
                {
                    sum += sumNumbers(root->left, number);
                }
                if (root->right)
                {
                    sum += sumNumbers(root->right, number);
                }
                return sum;
            }
            return number;
        }
        return 0;
    }
};