class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        int n = arr.size();
        int num = 1e5;
        int ans = 0;
        vector<int> dp(2e5);

        for (int i = 0; i < n; i++) {
            int idx = num + arr[i]; 
            dp[idx] = max(dp[idx], dp[idx-difference] + 1);
            dp[idx] = max(dp[idx], 1);
            ans = max(ans, dp[idx]);
        }

        return ans;
    }
};
//WA的代码
int longestSubsequence(int* arr, int arrSize, int difference)
{
    int i, j, max = 1;
    int dp[100000];
    memset(dp, 0, 100000);
    dp[0] = 1;
    
    for (i = 1; i < arrSize; i++)
    {
        dp[i] = 1;
        for (j = 0; j < i; j++)
        {
            if (arr[i] - arr[j] == difference) dp[i] = dp[i] > dp[j] + 1 ? dp[i] : dp[j] + 1;
        }
        max = max > dp[i] ? max : dp[i];
    }

    return max;
}