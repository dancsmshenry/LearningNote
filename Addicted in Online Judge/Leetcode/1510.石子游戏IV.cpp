bool winnerSquareGame(int n)
{
    int i, j;
    bool dp[100000];
    dp[0] = false;
    dp[1] = true;
    
    for (i = 2; i <= n; i++)
    {
        dp[i] = false;
        j = 1;     
        while(i - j * j >= 0)
        {
            if (dp[i - j * j] ==false)
            {
                dp[i] = true;
                break;
            }
            else j++;
        }
    }

    return dp[n];
}
