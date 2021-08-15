int waysToChange(int n)
{
    int i, j, m, sum = 0;
    int coins[10], dp[1000000];
    if (n == 0) return 0;
    else if (n < 5) return 1;

    m = (n - n % 5) / 5;
    coins[0] = 1;
    coins[1] = 2;
    coins[2] = 5;

    dp[0] = 1;
    for (j = 1; j <= m; j++)
    {
        if (j >= coins[0]) dp[j] = dp[j - coins[0]];
        else dp[j] = 0;
    }
    
    for (i = 1; i < 3; i++)
    {
        for (j = 1; j <= m; j++)
        {
            if (j >= coins[i]) dp[j] = dp[j] + dp[j - coins[i]];
            dp[j] = dp[j] % 1000000007;
        }
    }

    for (j = 0; j <= m; j++)
        sum = (sum + dp[j]) % 1000000007;
    return sum;
}
