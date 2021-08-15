class Solution {
public:
    int minPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int res = 0;
        int n = nums.size();
        for (int i = 0; i < n; i ++ ){
            res = res > (nums[i] + nums[n - i - 1]) ? res : (nums[i] + nums[n - i - 1]);
        }

        return res;
    }
};