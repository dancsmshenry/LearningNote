int change(int amount, int* coins, int coinsSize)
{
    int i, j;
    int dp[10000];
    if (amount == 0) return 1;
    else if (coinsSize == 0) return 0;
    dp[0] = 1;
    for (j = 1; j <= amount; j++)
    {
        if (j >= coins[0]) dp[j] = dp[j - coins[0]];
        else dp[j] = 0;
    }
    
    for (i = 1; i < coinsSize; i++)
    {
        for (j = 1; j <= amount; j++)
        {
            if (j >= coins[i]) dp[j] = dp[j] + dp[j - coins[i]];
        }
    }

    return dp[amount];
}
