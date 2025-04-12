#include <cstddef>

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
    ListNode *rotateRight(ListNode *head, int k)
    {
        if (head == NULL || head->next == NULL)
        {
            return head;
        }
        int size(1);
        ListNode *parent(head), *node(parent->next);
        while (node)
        {
            ++size;
            parent = node;
            node = node->next;
        }
        parent->next = head;
        node = parent->next;
        for (int i = size - ((k - 1) % size + 1); i > 0; --i)
        {
            parent = node;
            node = node->next;
        }
        parent->next = NULL;
        return node;
    }
};