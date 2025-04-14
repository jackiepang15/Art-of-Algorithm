#include <vector>
#include <unordered_map>

using namespace std;

class Node
{
public:
    int val;
    vector<Node *> neighbors;
    Node()
    {
        val = 0;
        neighbors = vector<Node *>();
    }
    Node(int _val)
    {
        val = _val;
        neighbors = vector<Node *>();
    }
    Node(int _val, vector<Node *> _neighbors)
    {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution
{
public:
    Node *cloneGraph(Node *node)
    {
        if (node == nullptr)
        {
            return node;
        }
        vector<Node *> vec, vecClone;
        unordered_map<Node *, int> index;
        index[node] = vec.size();
        vec.push_back(node);
        vecClone.push_back(new Node(node->val));
        int start(0);
        while (start < vec.size())
        {
            int size(vec.size());
            for (int i = 0; i < size; ++i)
            {
                Node *node(vec[i]);
                for (const auto &n : node->neighbors)
                {
                    if (index.count(n) > 0)
                    {
                        continue;
                    }
                    index[n] = vec.size();
                    vec.push_back(n);
                    vecClone.push_back(new Node(n->val));
                }
            }
            start = size;
        }
        for (int i = vec.size() - 1; i >= 0; --i)
        {
            Node *node(vec[i]);
            Node *nodeClone(vecClone[i]);
            for (const auto &n : node->neighbors)
            {
                nodeClone->neighbors.push_back(vecClone[index[n]]);
            }
        }
        return vecClone.front();
    }
};