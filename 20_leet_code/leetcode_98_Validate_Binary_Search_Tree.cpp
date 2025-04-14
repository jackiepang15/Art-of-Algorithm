#include <utility>
#include <algorithm>

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
    bool isValidBST(TreeNode *root)
    {
        bool valid(true);
        if (root == nullptr)
        {
            return valid;
        }
        isValidBST(root, valid);
        return valid;
    }

    pair<int, int> isValidBST(TreeNode *root, bool &valid)
    {
        pair<int, int> result(make_pair(root->val, root->val));
        if (root->left)
        {
            pair<int, int> left(isValidBST(root->left, valid));
            if (!valid)
            {
                return result;
            }
            valid = left.second < root->val;
            if (!valid)
            {
                return result;
            }
            result.first = min(result.first, left.first);
        }
        if (root->right)
        {
            pair<int, int> right(isValidBST(root->right, valid));
            if (!valid)
            {
                return result;
            }
            valid = right.first > root->val;
            if (!valid)
            {
                return result;
            }
            result.second = max(result.second, right.second);
        }
        return result;
    }
};