#include <unordered_set>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        unordered_set<ListNode *> exist;
        while (head)
        {
            if (exist.count(head) > 0)
            {
                return true;
            }
            exist.insert(head);
            head = head->next;
        }
        return false;
    }
};