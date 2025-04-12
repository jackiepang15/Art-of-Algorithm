#include <vector>
#include <cstddef>

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
    ListNode *partition(ListNode *head, int x)
    {
        int size(0), sizeLess(0);
        ListNode *node(head);
        while (node)
        {
            ++size;
            if (node->val < x)
            {
                ++sizeLess;
            }
            node = node->next;
        }
        if (size < 2)
        {
            return head;
        }
        int indexLess(0), indexGreater(sizeLess);
        vector<ListNode *> vec(size);
        node = head;
        while (node)
        {
            if (node->val < x)
            {
                vec[indexLess++] = node;
            }
            else
            {
                vec[indexGreater++] = node;
            }
            node = node->next;
        }
        vec[size - 1]->next = NULL;
        for (int i = size - 2; i >= 0; --i)
        {
            vec[i]->next = vec[i + 1];
        }
        return vec[0];
    }
};
