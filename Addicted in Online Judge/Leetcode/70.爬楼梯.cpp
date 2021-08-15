#include <stdio.h>
int main()
{
	int climbStairs(int n)
{
    int a[2];
    a[0] = 1;
    a[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        a[i % 2] = a[0] + a[1];
    }

    return a[n % 2];
}
}
