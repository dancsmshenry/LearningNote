bool stoneGame(int* piles, int pilesSize)
{
    int i, j;
    int dp[pilesSize][pilesSize];

    for(i = 0; i < pilesSize; i++)
    {
        for (j = i; j >= 0; j--)
        {
            if (j == i) dp[i][j] = piles[i];
            else 
            dp[j][i] = piles[j] - dp[j + 1][i] > piles[i] - dp[j][i - 1] ? piles[j] - dp[j + 1][i] : piles[i] - dp[j][i - 1];
        }
    }

    return dp[0][pilesSize - 1] > 0;
}
