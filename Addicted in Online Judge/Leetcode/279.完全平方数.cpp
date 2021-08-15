#include <stdio.h>
#include <limits.h>
int main()
{
	int mid, j, i, n;
    int dp[100000];
    scanf("%d", &n);
    dp[1] = 1;
    
    if (n > 1)
	{
    	for (i = 2; i <= n; i++)
    	{
        	dp[i] = INT_MAX;
        	for (j = 1; j * j <= i; j++)
        	{
            	mid = dp[i - j * j] + 1;
            	dp[i] = mid > dp[i] ? dp[i] : mid;
        	}
    	}
    }
    
    printf("%d", dp[n]);
    return 0;
}
