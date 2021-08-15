int countPrimes(int n)
{
    int i, j, sum = 0;
    bool f[n + 10000];
    if (n == 0 || n == 1) return 0;
    memset(f, true, n + 10000);
    f[1] = false;

    for (i = 2; i < n; i++)
    {
        if (f[i] == true)
        {
            sum++;
            for (j = 2; j * i < n; j++)
            f[j * i] = false;
        }
    }

    return sum;
}
