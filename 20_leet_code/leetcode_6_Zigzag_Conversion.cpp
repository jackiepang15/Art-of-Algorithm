#include <vector>
#include <string>

using namespace std;

class Solution {
    public:
        string convert(string s, int numRows) {
            if (numRows == 1) {
                return s;
            }
            vector<string> lines(numRows);
            int index(1), delta(-1);
            int size(s.size());
            for (int i = 0; i < size; ++i) {
                index += delta;
                lines[index].push_back(s[i]);
                if (delta == -1 && index == 0) {
                    delta = 1;
                }
                if (delta == 1 && index == numRows - 1) {
                    delta = -1;
                }
            }
            string result;
            for (int i = 0; i < numRows; ++i) {
                result.append(lines[i]);
            }
            return result;
        }
    };