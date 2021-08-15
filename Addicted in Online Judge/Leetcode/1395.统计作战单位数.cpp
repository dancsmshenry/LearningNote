int numTeams(int* rating, int ratingSize)
{
    int i, j, total = 0;
    int dp[1000];
    
    for (i = ratingSize - 1; i >= 0; i--)
    {
       dp[i] = 0;
       for (j = ratingSize - 1; j > i; j--)
       {
           if (rating[i] > rating[j])
           {
               dp[i] = dp[i] + 1;
               total = total + dp[j];
           }
       }
    }

    for (i = 0; i < ratingSize; i++)
    {
        dp[i] = 0;
        for (j = 0; j < i; j++)
        {
            if (rating[i] > rating[j])
            {
                dp[i] = dp[i] + 1;
                total = total + dp[j];
            }
        }
    }

    return total;
}
