    class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxn = INT_MIN, max1 = 1, min1 = 1;

        for (int i = 0; i < nums.size(); i ++ )
        {
            if (nums[i] < 0) swap(max1, min1);
            max1 = max(nums[i], max1 * nums[i]);
            min1 = min(nums[i], min1 * nums[i]);
            maxn = max(maxn, max1);
        }

        return maxn;
    }
};

//动态规划未优化版
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int max1[100000], min1[100000];
        int maxn = nums[0];//这里注意是nums[0],因为下main是从1开始算的
        max1[0] = min1[0] = nums[0];

        for (int i = 1; i < nums.size(); i ++ )
        {
            max1[i] = max(max1[i - 1] * nums[i], max(nums[i], min1[i - 1] * nums[i]));
            min1[i] = min(min1[i - 1] * nums[i], min(nums[i], max1[i  -1] * nums[i]));
            maxn = max(maxn, max1[i]);
        }

        return maxn;
    }
};