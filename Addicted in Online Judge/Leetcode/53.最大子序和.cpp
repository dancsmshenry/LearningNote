/*
#include <stdio.h>
int main()
{
	int n, i, j, max = 0;
	int a[100000], dp[100000];
	scanf("%d", &n);
	for (i = 0; i < n; i++) scanf("%d", &a[i]);
	
	dp[0] = 0;
	dp[1] = a[0];
	for (i = 2; i <= n; i++)
	{
		dp[i] = a[i - 1] + dp[i - 1];
		for (j = 0; j < i; j++) max = max > (dp[i] - dp[j]) ? max : (dp[i] - dp[j]);
	}
	
	printf("%d", max);
	return 0;
}
    前缀和的写法 
*/ 

#include <stdio.h>
int main()
{
	int n, i, max, sum;
	int a[100000];
	scanf("%d", &n);
	for (i = 0; i < n; i++) scanf("%d", &a[i]);
	sum = a[0];
	max = a[0];
	
	for (i = 1; i < n; i++)
	{
		if (sum >= 0) sum += a[i];
		else sum = a[i];
		max = max > sum ? max : sum;
	}
	
	printf("%d", max);
	return 0;
} 
	//DP的写法 
