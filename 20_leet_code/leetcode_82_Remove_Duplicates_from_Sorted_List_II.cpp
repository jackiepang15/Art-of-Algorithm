#include <cstddef>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        ListNode *node(head), *newHead(NULL), *newNode(NULL);
        while (node)
        {
            int count(1);
            ListNode *n(node->next);
            while (n && n->val == node->val)
            {
                ++count;
                n = n->next;
            }
            if (count == 1)
            {
                if (newNode)
                {
                    newNode->next = node;
                    newNode = newNode->next;
                }
                else
                {
                    newNode = newHead = node;
                }
            }
            node = n;
        }
        if (newNode)
        {
            newNode->next = NULL;
        }
        return newHead;
    }
};