#include <limits.h>

int coinChange(int* coins, int coinsSize, int amount)
{
    int i, j;
    int dp[100000];
    
    dp[0] = 0;
    for (i = 1; i <= amount; i++)
    {
        dp[i] = INT_MAX;
        for (j = 0; j < coinsSize; j++)
        {
            if (i - coins[j] >= 0) dp[i] = dp[i] < dp[i - coins[j]] + 1 ? dp[i] : dp[i - coins[j]] + 1;
        }
    }

    if (dp[amount] == INT_MAX) return -1;
    else return dp[amount];
}
