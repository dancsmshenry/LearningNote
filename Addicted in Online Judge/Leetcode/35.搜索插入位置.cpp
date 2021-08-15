class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;

        while (left < right){
            int mid = (left + right) >> 1;
            if (nums[mid] < target) left = mid + 1;
            else right = mid;
        }

        if (nums[right] == target) return right;

        for (int i = 0; i < nums.size(); i ++ ){
            if (nums[i] >= target){
                return i;
            }
        }

        return nums.size();
    }
};