class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> res;
        vector<int> max1(n), max2(n);

        for (int i = 0; i < n; i ++ ){
            if (i % k == 0){
                max1[i] = nums[i];
            }else{
                max1[i] = max(max1[i - 1], nums[i]);
            }
        }

        for (int i = n - 1; i >= 0; i -- ){
            if (i == n - 1 || (i + 1) % k == 0){
                max2[i] = nums[i];
            }else{
                max2[i] = max(max2[i + 1], nums[i]);
            }
        }

        for (int i = 0; i <= n - k; i ++ ){
            res.push_back(max(max2[i], max1[i + k - 1]));
        }

        return res;
    }
};