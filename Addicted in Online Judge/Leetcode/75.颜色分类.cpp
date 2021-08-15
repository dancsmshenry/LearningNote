#include <stdio.h>
int main() 
{
    int i, n, zero, one;
    int a[10000];
    scanf("%d", &n);
    for (i = 0 ; i < n; i++) scanf("%d", &a[i]);
    
    for (i = 0; i < n; i++)
    {
        if (a[i] == 0) zero++;
        else if (a[i] == 1) one++;
    }

    for (i = 0; i < n; i++)
    {
        if (zero != 0)
        {
            a[i] = 0;
            zero--;
        }
        else if (one != 0)
        {
            a[i] = 1;
            one--;
        }
        else a[i] = 2;
    }
    
    for (i = 0 ; i < n; i++) printf("%d", a[i]);
	return 0;
}
