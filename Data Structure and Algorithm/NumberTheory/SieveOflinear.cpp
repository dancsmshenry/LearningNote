#include <stdio.h>
#include <string.h>

int main()
{
	int n, total = 0;
	int a[100000];
	bool f[100000];
	scanf("%d", &n);
	memset(f, true, sizeof(f));
	
	for (int i = 2; i <= n; i ++ )
	{
		if (f[i] == true) a[total ++ ] = i;
		for (int j = 0; j < total && i * a[j] <= n; j ++ )
		{
			f[i * a[j]] = false;
			if (i % a[j] == 0) break;
		}
	}
	
	for (int i = 0; i < total; i ++ ) printf("%d ", a[i]);

	return 0;
} 