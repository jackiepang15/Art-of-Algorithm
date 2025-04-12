#include <vector>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        vector<ListNode *> vec;
        ListNode *node(head);
        while (node)
        {
            vec.push_back(node);
            node = node->next;
        }
        int end(k - 1);
        while (end < vec.size())
        {
            int right(end), left(right - k + 1);
            while (left < right)
            {
                ListNode *n(vec[left]);
                vec[left] = vec[right];
                vec[right] = n;
                ++left;
                --right;
            }
            end += k;
        }
        vec.back()->next = NULL;
        for (int i = vec.size() - 2; i >= 0; --i)
        {
            vec[i]->next = vec[i + 1];
        }
        return vec.front();
    }
};