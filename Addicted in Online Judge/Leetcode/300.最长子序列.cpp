#include <stdio.h>
int main()
{
    int i, j, n, max = 0;
    int dp[100000], a[100000];
    
    scanf("%d", &n);
	for (i = 0; i < n; i++) scanf("%d", &a[i]);
    dp[0] = 1;
    
    for (i = 1; i < n; i++)
    {
        dp[i] = 1;
		for (j = 0; j < i; j++)
        	if (a[i] > a[j]) dp[i] = dp[i] < dp[j] + 1 ? dp[j] + 1 : dp[i];
        max = max > dp[i] ? max : dp[i];
    }
    
	printf("%d", max);
	return 0;	
}
