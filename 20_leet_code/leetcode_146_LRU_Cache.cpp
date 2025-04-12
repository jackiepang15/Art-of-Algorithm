#include <list>
#include <unordered_map>

using namespace std;

class LRUCache
{
public:
    int capacity;
    list<pair<int, int>> l;
    unordered_map<int, list<pair<int, int>>::iterator> m;

    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key)
    {
        if (m.find(key) == m.end())
        {
            return -1;
        }
        else
        {
            int value(m[key]->second);
            l.erase(m[key]);
            l.push_front(make_pair(key, value));
            m[key] = l.begin();
            return value;
        }
    }

    void put(int key, int value)
    {
        if (m.find(key) != m.end())
        {
            l.erase(m[key]);
        }
        else if (l.size() >= capacity)
        {
            m.erase(l.back().first);
            l.pop_back();
        }
        l.push_front(make_pair(key, value));
        m[key] = l.begin();
    }
};
