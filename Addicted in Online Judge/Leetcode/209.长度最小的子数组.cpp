class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        /**
        这不就是双指针吗..
        首先先创建left和right两个指针同时指向0的位置
        然后先对right进行右移，
        如果left和right当前范围的值大于等于target，就和res做比较，然后left++
        如果小于，则right ++ 
        淦，之前理解成了==target了，想了好久..
        **/
        int left = 0, right = 0;
        int n = nums.size();
        int ans = nums[0], res = INT_MAX;

        while (right < n){
            if (ans >= target){
                res = min(res, right - left + 1);
                ans -= nums[left];
                left ++ ;
            }else{
                right ++ ;
                if (right < n){
                    ans += nums[right];
                }
            }
        }

        return res != INT_MAX ? res : 0;
    }
};