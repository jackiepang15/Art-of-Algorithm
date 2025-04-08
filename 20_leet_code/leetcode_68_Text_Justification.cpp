#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    vector<string> fullJustify(vector<string> &words, int maxWidth)
    {
        if (words.empty())
        {
            return vector<string>();
        }
        vector<string> lines;
        int size(words.size());
        for (int i = 0; i < size;)
        {
            vector<string> w;
            int width(0);
            w.push_back(words[i]);
            width += words[i].size();
            ++i;
            while (i < size && width + 1 + words[i].size() <= maxWidth)
            {
                w.push_back(words[i]);
                width += 1 + words[i].size();
                ++i;
            }
            string line;
            if (i == size || w.size() == 1)
            {
                line = w[0];
                for (int j = 1; j < w.size(); ++j)
                {
                    line.push_back(' ');
                    line.append(w[j]);
                }
                for (int j = maxWidth - width; j > 0; --j)
                {
                    line.push_back(' ');
                }
            }
            else
            {
                int spaces = (maxWidth - width) / (w.size() - 1);
                int count = (maxWidth - width) - spaces * (w.size() - 1);
                line = w[0];
                for (int j = 1; j < w.size(); ++j)
                {
                    for (int k = spaces; k > 0; --k)
                    {
                        line.push_back(' ');
                    }
                    if (j <= count)
                    {
                        line.push_back(' ');
                    }
                    line.push_back(' ');
                    line.append(w[j]);
                }
            }
            lines.push_back(line);
        }
        return lines;
    }
};