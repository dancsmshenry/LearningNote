int minDays(int n)
{
    int dp[200000];
    dp[0] = 0;
    
    for (int i = 1; i <= n; i++)
    {
        dp[i] = dp[i - 1] + 1;
        if (i % 2 == 0) dp[i] = dp[i / 2] + 1 > dp[i] ? dp[i] : dp[i / 2] + 1;
        if (i % 3 == 0) dp[i] = dp[i] > dp[i / 3] + 1 ? dp[i / 3] + 1 : dp[i];
    }

    return dp[n];
}
