class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        /*
        这道题的思路：
        先用二分查找找到目标数，如果没有，就返回-1-1
        然后，这里二分查找的巧妙之处在于，每次都能返回这个数字第一次出现的地方（可以模拟一遍）
        然后就是常规操作了
        */

        int left = 0, right = nums.size() - 1;
        vector<int> f(2, -1);
        if (right < 0) return f;

        while (left < right){
            // int mid = right + (left - right) / 2;//这样就会超时？
            int mid = (right + left) / 2;
            if (nums[mid] < target){
                left = mid + 1;
            }else{
                right = mid;
            }
        }
        if (nums[left] != target) return f;

        f[0] = left;
        while (left < nums.size() && nums[left] == target){
            left ++ ;
        }
        f[1] = -- left;

        return f;
    }
};