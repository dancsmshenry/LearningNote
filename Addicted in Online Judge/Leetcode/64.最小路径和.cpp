#include <stdio.h>
int main()
{
	int n, m, i, j;
	int f[1000][1000], a[1000][1000];
	scanf("%d %d", &n, &m);
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		scanf("%d", &a[i][j]);
	}
	
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		if (i == 0) f[i][j] =  f[i][j - 1] + a[i][j];
		else if (j == 0) f[i][j] =  f[i - 1][j] + a[i][j];
		else f[i][j] = a[i][j] + (f[i][j - 1] > f[i - 1][j] ? f[i - 1][j] : f[i][j - 1]);
	}
	
	printf("%d", f[n - 1][m - 1]);
	return 0;
}
