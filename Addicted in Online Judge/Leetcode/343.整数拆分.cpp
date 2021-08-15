int integerBreak(int n)
{
    int i, j, num1, num2;
    int dp[1000];
    dp[1] = 1;
    
    for (i = 2; i <= n; i++)
    {
        dp[i] = 0;
        for (j = 1; j < i; j++)
        {
            num1 = (dp[i - j] > (i - j) ? dp[i - j] : (i - j)) * j;
            num2 = dp[j] * dp[i - j] > dp[i] ? dp[j] * dp[i - j] : dp[i];
            dp[i] = num1 > num2 ? num1 : num2;
        }
    }

    return dp[n];
}
