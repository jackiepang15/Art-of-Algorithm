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
    vector<int> rightSideView(TreeNode *root)
    {
        vector<int> result;
        if (root == nullptr)
        {
            return result;
        }
        vector<TreeNode *> vec;
        int start(vec.size());
        vec.push_back(root);
        while (start < vec.size())
        {
            result.push_back(vec.back()->val);
            int size(vec.size());
            for (int i = start; i < size; ++i)
            {
                TreeNode *n(vec[i]);
                if (n->left)
                {
                    vec.push_back(n->left);
                }
                if (n->right)
                {
                    vec.push_back(n->right);
                }
            }
            start = size;
        }
        return result;
    }
};