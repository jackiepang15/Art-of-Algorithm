#include <vector>

using namespace std;

class Node
{
public:
    bool val;
    bool isLeaf;
    Node *topLeft;
    Node *topRight;
    Node *bottomLeft;
    Node *bottomRight;

    Node()
    {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf)
    {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node *_topLeft, Node *_topRight, Node *_bottomLeft, Node *_bottomRight)
    {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

class Solution
{
public:
    Node *construct(vector<vector<int>> &grid)
    {
        int n(grid.size());
        return construct(grid, 0, 0, n);
    }

    Node *construct(vector<vector<int>> &grid, int row, int col, int size)
    {
        int value(grid[row][col]);
        bool same(true);
        for (int r = row + size - 1; r >= row && same; --r)
        {
            for (int c = col + size - 1; c >= col && same; --c)
            {
                same = grid[r][c] == value;
            }
        }
        if (same)
        {
            return new Node(value, true);
        }
        size /= 2;
        Node *topLeft = construct(grid, row, col, size);
        Node *topRight = construct(grid, row, col + size, size);
        Node *bottomLeft = construct(grid, row + size, col, size);
        Node *bottomRight = construct(grid, row + size, col + size, size);
        return new Node(value, false, topLeft, topRight, bottomLeft, bottomRight);
    }
};