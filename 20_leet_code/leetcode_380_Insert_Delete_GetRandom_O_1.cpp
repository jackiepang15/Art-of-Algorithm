#include <vector>
#include <unordered_map>
#include <stdlib.h>

using namespace std;

class RandomizedSet
{
    vector<int> v;
    unordered_map<int, int> m;

public:
    RandomizedSet()
    {
    }

    bool insert(int val)
    {
        auto i(m.find(val));
        if (i == m.end())
        {
            m[val] = v.size();
            v.push_back(val);
            return true;
        }
        return false;
    }

    bool remove(int val)
    {
        auto i(m.find(val));
        if (i != m.end())
        {
            m[v.back()] = i->second;
            v[i->second] = v.back();
            m.erase(val);
            v.pop_back();
            return true;
        }
        return false;
    }

    int getRandom()
    {
        if (v.empty())
        {
            return 0;
        }
        return v[rand() % v.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */