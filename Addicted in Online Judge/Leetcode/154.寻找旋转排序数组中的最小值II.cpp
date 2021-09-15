class Solution {
public:
    int findMin(vector<int>& nums) {
        /*思路同剑指offer11旋转数组的最小数字*/
        int left = 0, right = nums.size() - 1;

        while (left < right){
            int mid = (left + right) >> 1;
            if (nums[mid] > nums[right]){
                left = mid + 1;
            }else if (nums[mid] == nums[right]){
                right -- ;
            }else{
                right = mid;
            }
        }

        return nums[left];
    }
};