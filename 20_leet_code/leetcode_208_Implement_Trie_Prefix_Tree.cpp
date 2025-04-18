#include <map>
#include <string>

using namespace std;

class Trie
{
public:
    struct ListNode
    {
        bool leaf;
        map<char, ListNode *> next;
        ListNode(bool leaf) : leaf(leaf), next() {}
    };

    ListNode *root;

    /** Initialize your data structure here. */
    Trie()
    {
        root = new ListNode(false);
    }

    /** Inserts a word into the trie. */
    void insert(string word)
    {
        ListNode *n(root);
        for (int i = 0; i < word.size(); ++i)
        {
            char c(word[i]);
            if (n->next.find(c) == n->next.end())
            {
                n->next[c] = new ListNode(false);
            }
            n = n->next[c];
            if (i == word.size() - 1)
            {
                n->leaf = true;
            }
        }
    }

    /** Returns if the word is in the trie. */
    bool search(string word)
    {
        ListNode *n(root);
        for (int i = 0; i < word.size(); ++i)
        {
            char c(word[i]);
            if (n->next.find(c) == n->next.end())
            {
                return false;
            }
            n = n->next[c];
        }
        return n->leaf;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix)
    {
        ListNode *n(root);
        for (int i = 0; i < prefix.size(); ++i)
        {
            char c(prefix[i]);
            if (n->next.find(c) == n->next.end())
            {
                return false;
            }
            n = n->next[c];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */