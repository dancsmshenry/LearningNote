#include <stdio.h>
int main()
{
	int dp[10000], a[100];
    int i, j, n;
    scanf("%d", &n);
    dp[1] = 1;
    
    for (i = 2; i <= n; i++)
    {
        dp[i] = 0;
		for (j = 1; j < i; j++)
        {
            dp[i] = (dp[i - j] *j) > dp[i] ? (dp[i - j] *j) : dp[i];
            dp[i] = ((i - j) * j) > dp[i] ? ((i - j) * j) : dp[i];
        }
    }
    
    printf("%d", dp[n]);
    return 0;
}
