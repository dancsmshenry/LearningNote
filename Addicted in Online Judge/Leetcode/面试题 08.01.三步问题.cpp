int waysToStep(int n)
{
    long long dp[1000000];
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;
    
    for (int i = 3; i <= n; i++)
    {
        dp[i % 3] = dp[(i - 1) % 3] + dp[(i - 2) % 3] + dp[(i - 3) % 3];
        dp[i % 3] = dp[i % 3] % 1000000007;
    }
    
    return dp[n % 3];
}
