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
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        return buildTree(postorder.begin(), postorder.end() - 1, inorder.begin(), inorder.end() - 1);
    }

    TreeNode *buildTree(vector<int>::iterator postStart, vector<int>::iterator postEnd, vector<int>::iterator inStart, vector<int>::iterator inEnd)
    {
        int val(*postEnd);
        vector<int>::iterator inIndex(inStart);
        while (*inIndex != val)
        {
            ++inIndex;
        }
        vector<int>::iterator postIndex(postStart + (inIndex - inStart));
        TreeNode *node = new TreeNode(val);
        if (inIndex != inStart)
        {
            node->left = buildTree(postStart, postIndex - 1, inStart, inIndex - 1);
        }
        if (inIndex != inEnd)
        {
            node->right = buildTree(postIndex, postEnd - 1, inIndex + 1, inEnd);
        }
        return node;
    }
};