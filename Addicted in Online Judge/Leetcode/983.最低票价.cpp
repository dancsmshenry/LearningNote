#define MAX(a, b) (a > b ? a : b)

int mincostTickets(int* days, int daysSize, int* costs, int costsSize)
{
    int i, one, seven, thirty, num = 0;
    int dp[10000];
    dp[0] = 0;
    
    for (i = 1; i <= days[daysSize - 1]; i++)
    {
        if (i == days[num])
        {
            one = dp[MAX(0, i - 1)] + costs[0];
            seven = dp[MAX(0, i - 7)] + costs[1];
            thirty = dp[MAX(0, i - 30)] + costs[2];
            dp[i] = one < seven ? one : seven;
            dp[i] = dp[i] < thirty ? dp[i] : thirty;
            num++;
        }
        else dp[i] = dp[i - 1];
    }

    return dp[days[daysSize - 1]];
}
