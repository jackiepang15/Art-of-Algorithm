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
    ListNode *reverseBetween(ListNode *head, int left, int right)
    {
        vector<ListNode *> vec;
        ListNode *node(head);
        while (node)
        {
            vec.push_back(node);
            node = node->next;
        }
        --left;
        --right;
        while (left < right)
        {
            ListNode *n(vec[left]);
            vec[left] = vec[right];
            vec[right] = n;
            ++left;
            --right;
        }
        vec.back()->next = NULL;
        for (int i = vec.size() - 2; i >= 0; --i)
        {
            vec[i]->next = vec[i + 1];
        }
        return vec.front();
    }
};