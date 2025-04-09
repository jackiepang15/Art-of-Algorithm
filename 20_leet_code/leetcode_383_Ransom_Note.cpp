#include <unordered_map>
#include <string>

using namespace std;

class Solution
{
public:
    bool canConstruct(string ransomNote, string magazine)
    {
        unordered_map<char, int> ransomNoteSet;
        for (const auto &c : ransomNote)
        {
            ++ransomNoteSet[c];
        }
        unordered_map<char, int> magazineSet;
        for (const auto &c : magazine)
        {
            ++magazineSet[c];
        }
        for (const auto &kv : ransomNoteSet)
        {
            if (kv.second > magazineSet[kv.first])
            {
                return false;
            }
        }
        return true;
    }
};