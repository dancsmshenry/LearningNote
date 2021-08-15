class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int dp[1000][1000];
        if (nums.size() % 2 == 0) return true;

        for (int i = 0; i < nums.size(); i ++ ) dp[i][i] = nums[i];

        for (int i = nums.size() - 1; i >= 0; i -- )
        {
            for (int j = i + 1; j < nums.size(); j ++ )
            {
                dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
            }
        }

        return dp[0][nums.size() - 1] >= 0 ? true : false;
    }
};