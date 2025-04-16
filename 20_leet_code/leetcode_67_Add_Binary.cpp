#include <string>

using namespace std;

class Solution
{
public:
    string addBinary(string a, string b)
    {
        string c(max(a.size(), b.size()) + 1, '0');
        int indexA(a.size() - 1), indexB(b.size() - 1);
        int carry(0);
        for (int indexC = c.size() - 1; indexC >= 0; --indexC)
        {
            int valA(indexA >= 0 ? a[indexA] - '0' : 0);
            int valB(indexB >= 0 ? b[indexB] - '0' : 0);
            int valC(valA + valB + carry);
            carry = valC / 2;
            valC = valC % 2;
            c[indexC] = '0' + valC;
            --indexA;
            --indexB;
        }
        return c[0] == '0' ? c.substr(1) : c;
    }
};