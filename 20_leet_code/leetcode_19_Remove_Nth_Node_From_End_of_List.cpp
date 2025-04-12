#include <vector>
#include <map>
#include <string>
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        int size(0);
        ListNode *node(head);
        while (node)
        {
            ++size;
            node = node->next;
        }
        if (n == size)
        {
            return head->next;
        }
        ListNode *parent(head);
        node = parent->next;
        for (int i = size - n; i > 1; --i)
        {
            parent = node;
            node = parent->next;
        }
        parent->next = node->next;
        return head;
    }
};