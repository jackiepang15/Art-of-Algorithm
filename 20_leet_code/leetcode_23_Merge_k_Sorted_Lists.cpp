#include <vector>
#include <queue>

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
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for (int i = lists.size() - 1; i >= 0; --i)
        {
            ListNode *&n(lists[i]);
            if (n)
            {
                pq.push(make_pair(n->val, i));
            }
        }
        ListNode dump;
        ListNode *cur = &dump;
        while (pq.size() > 0)
        {
            int i(pq.top().second);
            pq.pop();
            ListNode *&n(lists[i]);
            cur->next = n;
            cur = n;
            n = n->next;
            if (n)
            {
                pq.push(make_pair(n->val, i));
            }
        }
        return dump.next;
    }
};