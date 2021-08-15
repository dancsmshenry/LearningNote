#include <stdio.h>
#include <math.h>
#include <string.h>

int main()
{
	int n;
	bool f[1000000];
	memset(f, true, 1000000);
	scanf("%d", &n);
	
	for (int i = 2; i <= sqrt(n); i ++ )
	{
		if (f[i])
			for (int j = 2; i * j <= n; j ++ ) 
				f[i * j] = false;
	}
	
	for (int i = 2; i <= n; i ++ )
		if (f[i]) 
			printf("%d ", i);

	return 0;
} 