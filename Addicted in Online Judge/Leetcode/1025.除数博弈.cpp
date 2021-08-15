bool divisorGame(int N)
{
    int i, j;
    bool dp[1000000];
    dp[1] = false;

    for (i = 2; i <= N; i++)
    {
        dp[i] = false;
        if (dp[i - 1] == false) dp[i] = true;
        else
        {
            for (j = 1; j < i; j++)
                if (i % j == 0 && dp[i - j] == false) dp[i] = true;
        }
    }

    return dp[N];
}
