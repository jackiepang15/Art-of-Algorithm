class Node
{
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution
{
public:
    Node *connect(Node *root)
    {
        if (root == nullptr)
        {
            return root;
        }
        Node *parent(root), *child(new Node());
        while (parent)
        {
            child->next = nullptr;
            Node *nParent(parent), *nChild(child);
            while (nParent)
            {
                if (nParent->left)
                {
                    nChild->next = nParent->left;
                    nChild = nChild->next;
                }
                if (nParent->right)
                {
                    nChild->next = nParent->right;
                    nChild = nChild->next;
                }
                nParent = nParent->next;
            }
            parent = child->next;
        }
        return root;
    }
};