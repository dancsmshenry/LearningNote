class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    vector<int> f(2, -1);
    if (nums.size() < 1) return f;

    while (left < right)
    {
        int mid = (right + left) / 2;
        if (nums[mid] < target) left = mid + 1;
        else right = mid;
    }
    int mid = left;
    if (nums[mid] != target) return f;

    while (mid < nums.size() && nums[mid] == target) mid ++ ;
    f[1] = -- mid;
    while (mid >= 0 && nums[mid] == target) mid --;
    f[0] = ++ mid;

    return f;
    }
};