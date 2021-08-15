class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double k1 = k;
        
        int length = 0;
        for (int i = 0; i < k; i ++ ){
            length += nums[i];
        }
        
        int maxn = length;
        for (int i = k; i < nums.size(); i ++ ){
            length = length + nums[i] - nums[i - k];
            maxn = max(maxn, length);
        }

        return maxn / k1;
    }
};