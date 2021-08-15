int tribonacci(int n)
{
    int i;
    int dp[1000];
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 1;

    for (i = 3; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];

    return dp[n];
}

int tribonacci(int n)
{
    int i;
    int dp[1000];
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 1;

    for (i = 3; i <= n; i++)
        dp[i % 3] = dp[0] + dp[1] + dp[2];

    return dp[n % 3];
}
