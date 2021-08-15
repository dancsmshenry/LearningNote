#include <math.h>

int kthFactor(int n, int k)
{
    int b, i, j = 0;
    int a[10000];
    b = sqrt(n);

    for(i = 1; i <= b; i++)
    {
        if(n % i == 0)
        {
            j++;
            a[j] = i;
        }
    }

    if (b * b != n)
    {
        if (k <= j) return a[k];
        else if (k > j * 2) return -1;
        else return n / a[2 * j - k + 1];
    }
    else
    {
        if (n == 1 && k == 1) return 1;
        else if (k > j * 2 - 2) return -1;
        else if (k <= j) return a[k];
        else return n / a[2 * j - k];
    }
}
