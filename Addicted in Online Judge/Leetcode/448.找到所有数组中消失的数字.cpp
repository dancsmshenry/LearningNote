class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> ans;
        int n = nums.size();

        for (int i = 0; i < n; i ++){
            nums[(nums[i] - 1) % n] += n;
            //问题是这里为什么要%n啊，感觉不%也行啊
            //哦，原来如果不%的话就会出现爆仓的情况
        }

        for (int i = 0; i < n; i ++){
            if (nums[i] <= n) ans.push_back(i + 1);
        }

        return ans;
    }
};