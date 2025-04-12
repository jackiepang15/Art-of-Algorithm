#include <vector>
#include <unordered_map>

using namespace std;

class Node
{
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution
{
public:
    Node *copyRandomList(Node *head)
    {
        if (head == NULL)
        {
            return NULL;
        }
        Node *node(head);
        unordered_map<Node *, int> map = {{node, 0}};
        Node *newHead = new Node(head->val);
        Node *newNode(newHead);
        vector<Node *> vec(1, newNode);
        while (node->next)
        {
            node = node->next;
            map[node] = map.size();
            newNode->next = new Node(node->val);
            newNode = newNode->next;
            vec.push_back(newNode);
        }
        node = head;
        newNode = newHead;
        while (node)
        {
            if (node->random)
            {
                newNode->random = vec[map[node->random]];
            }
            node = node->next;
            newNode = newNode->next;
        }
        return newHead;
    }
};