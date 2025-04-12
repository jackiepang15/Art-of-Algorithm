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
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        vector<vector<int>> result;
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
            vector<int> level(size - start);
            for (int i = start; i < size; ++i)
            {
                TreeNode *n(vec[i]);
                level[i - start] = n->val;
                if (n->left)
                {
                    vec.push_back(n->left);
                }
                if (n->right)
                {
                    vec.push_back(n->right);
                }
            }
            result.push_back(level);
            start = size;
        }
        return result;
    }
};