#include <vector>

using namespace std;

vector<int> searchRange(vector<int> &nums, int target)
{
    vector<int> result({-1, -1});
    if (nums.empty())
    {
        return result;
    }
    int begin(0);
    if (nums[begin] > target)
    {
        return result;
    }
    int end(nums.size() - 1);
    if (nums[end] < target)
    {
        return result;
    }
    while (begin < end)
    {
        int mid((begin + end) / 2);
        if (nums[mid] >= target)
        {
            end = mid;
        }
        else
        {
            begin = mid + 1;
        }
    }
    if (nums[begin] == target)
    {
        result[0] = begin;
    }
    begin = 0;
    end = nums.size() - 1;
    while (begin < end)
    {
        int mid((begin + end) / 2);
        if (nums[mid + 1] > target)
        {
            end = mid;
        }
        else
        {
            begin = mid + 1;
        }
    }
    if (nums[begin] == target)
    {
        result[1] = begin;
    }
    return result;
}