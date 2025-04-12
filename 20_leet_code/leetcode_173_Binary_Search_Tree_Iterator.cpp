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

class BSTIterator
{
public:
    vector<TreeNode *> vec;
    int index;

    BSTIterator(TreeNode *root)
    {
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
        index = 0;
    }

    int next()
    {
        return vec[index++]->val;
    }

    bool hasNext()
    {
        return index < vec.size();
    }
};
