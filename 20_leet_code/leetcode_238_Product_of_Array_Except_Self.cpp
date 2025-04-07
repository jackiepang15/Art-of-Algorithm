#include <vector>

using namespace std;

class Solution
{
public:
    vector<int> productExceptSelf(vector<int> &nums)
    {
        int size(nums.size());
        vector<int> result(size);
        result[size - 1] = nums[size - 1];
        for (int i = size - 2; i > 0; --i)
        {
            result[i] = result[i + 1] * nums[i];
        }
        int product(nums[0]);
        result[0] = result[1];
        for (int i = 1; i < size - 1; ++i)
        {
            result[i] = result[i + 1] * product;
            product *= nums[i];
        }
        result[size - 1] = product;
        return result;
    }
};