#include <cstddef>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        ListNode *head(NULL), *list3(NULL);
        while (list1 || list2)
        {
            if (list2 == NULL || (list1 && list1->val < list2->val))
            {
                if (list3)
                {
                    list3->next = list1;
                    list3 = list3->next;
                }
                else
                {
                    list3 = head = list1;
                }
                list1 = list1->next;
            }
            else
            {
                if (list3)
                {
                    list3->next = list2;
                    list3 = list3->next;
                }
                else
                {
                    list3 = head = list2;
                }
                list2 = list2->next;
            }
        }
        return head;
    }
};