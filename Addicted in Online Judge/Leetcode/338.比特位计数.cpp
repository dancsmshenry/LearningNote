int* countBits(int num, int* returnSize)
{
    int i;
    int a[10000];
    a[0] = 0;
    a[1] = 1;

    for (i = 2; i <= num; i++)
    {
        if (i % 2 == 0) a[i] = a[i / 2]; 
        else a[i] = a[i - 1] + 1;
    }

    return a;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countBits(int num, int* returnSize)
{
    int i;
    int *f = calloc(num + 1, sizeof(int));
    *returnSize = num + 1;
    if(num == 0) return f;
    f[0] = 0;
    f[1] = 1;

    for(i = 2; i <= num; i++)
    {
        if(i % 2 == 0) f[i] = f[i / 2];
        else f[i] = f[i - 1] + 1;
    }

    return f;
}
