class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int dp[10000];
        memset(dp, 0, 10000);
        dp[1] = arr[0];

        for (int i = 2; i <= arr.size(); i ++ )
        {   
            for (int j = 1, maxn = INT_MIN; j <= k && j <= i; j ++ )
            {
                maxn = max(maxn, arr[i - j]);
                dp[i] = max(dp[i], (dp[i - j] + maxn * j));
            }
        }

        return dp[arr.size()];
    }
};