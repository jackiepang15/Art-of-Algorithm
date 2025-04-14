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
    TreeNode *sortedArrayToBST(vector<int> &nums)
    {
        return sortedArrayToBST(nums.begin(), nums.end() - 1);
    }

    TreeNode *sortedArrayToBST(vector<int>::iterator begin, vector<int>::iterator end)
    {
        if (begin == end)
        {
            return new TreeNode(*begin);
        }
        int size(end - begin + 1);
        vector<int>::iterator mid(begin + size / 2);
        TreeNode *left(sortedArrayToBST(begin, mid - 1));
        TreeNode *right(mid == end ? nullptr : sortedArrayToBST(mid + 1, end));
        return new TreeNode(*mid, left, right);
    }
};