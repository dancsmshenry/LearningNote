int numPairsDivisibleBy60(int* time, int timeSize)
{
    int i, j, ans = 0;
    int f[10000];
    memset(f, 0, 10000);
    
    for (i = 0; i < timeSize; i ++ ) f[time[i] % 60] ++;

    for (i = 1; i < 30; i ++ ) ans = ans + f[i] * f[60 - i];

    if (f[30] > 1) ans += f[30] * (f[30] - 1) / 2;
    if (f[0] > 1) ans += f[0] * (f[0] - 1) / 2;

    return ans;
}

//超时的做法
/*
int numPairsDivisibleBy60(int* time, int timeSize)
{
    int i, j, ans = 0;
    
    for (i = 0; i < timeSize; i ++ )
    {
        for (j = 0; j < i; j ++ )
        if ((time[i] + time[j]) % 60 == 0) ans++;
    }

    return ans;
}
*/