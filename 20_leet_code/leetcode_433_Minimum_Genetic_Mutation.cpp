#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution
{
public:
    int minMutation(string startGene, string endGene, vector<string> &bank)
    {
        unordered_set<string> bankSet(bank.begin(), bank.end());
        bankSet.insert(startGene);
        if (bankSet.count(endGene) == 0)
        {
            return -1;
        }
        bank = vector<string>(bankSet.begin(), bankSet.end());

        int startIndex(-1), endIndex(-1);
        int geneSize(startGene.size()), bankSize(bank.size());
        vector<vector<bool>> m(bankSize, vector<bool>(bankSize));
        for (int i = 0; i < bankSize; ++i)
        {
            string &iStr(bank[i]);
            if (iStr == startGene)
            {
                startIndex = i;
            }
            if (iStr == endGene)
            {
                endIndex = i;
            }
            for (int j = i + 1; j < bankSize; ++j)
            {
                string &jStr(bank[j]);
                int count(0);
                for (int k = 0; k < geneSize; ++k)
                {
                    if (iStr[k] != jStr[k])
                    {
                        ++count;
                    }
                }
                if (count == 1)
                {
                    m[i][j] = true;
                    m[j][i] = true;
                }
            }
        }
        if (startIndex == endIndex)
        {
            return 0;
        }
        vector<int> vec;
        vector<bool> visited(bankSize);
        vec.push_back(startIndex);
        visited[startIndex] = true;
        int start(0), number(0);
        while (start < vec.size() && !visited[endIndex])
        {
            int size(vec.size());
            for (int i = start; i < size; ++i)
            {
                int node(vec[i]);
                for (int j = 0; j < bankSize; ++j)
                {
                    if (visited[j] || !m[node][j])
                    {
                        continue;
                    }
                    vec.push_back(j);
                    visited[j] = true;
                }
            }
            start = size;
            if (start < vec.size())
            {
                ++number;
            }
        }
        return visited[endIndex] ? number : -1;
    }
};