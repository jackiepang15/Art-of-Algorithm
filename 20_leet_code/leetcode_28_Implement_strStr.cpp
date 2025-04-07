#include <string>

using namespace std;

class Solution
{
public:
    int strStr(string haystack, string needle)
    {
        int size(haystack.size() - needle.size() + 1);
        for (int i = 0; i < size; ++i)
        {
            bool match(true);
            for (int j = 0; j < needle.size() && match; ++j)
            {
                match = needle[j] == haystack[i + j];
            }
            if (match)
            {
                return i;
            }
        }
        return -1;
    }
};
