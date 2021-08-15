int breakfastNumber(int* staple, int stapleSize, int* drinks, int drinksSize, int x)
{
    int i, sum = 0;
    int f[1000000];
    memset(f, 0, 1000000);
    f[0] = 0;
    
    for (i = 0; i < stapleSize; i++) f[staple[i]]++;
    
    for (i = 1; i < 200000; i++) f[i] = f[i] + f[i - 1];

    for (i = 0; i < drinksSize; i++)
    {
        if (x - drinks[i] >= 0) sum = sum + f[x - drinks[i]];
        sum = sum % 1000000007;
    }

    return sum;
}

//超时的愚蠢方法，一秒能够进行的运算时1e9次，超过了就会超时
int breakfastNumber(int* staple, int stapleSize, int* drinks, int drinksSize, int x)
{
    long i, j, sum = 0;
    
    for (i = 0; i < stapleSize; i++)
    {
        for (j = 0; j < drinksSize; j++)
        {
            if (staple[i] + drinks[j] <= x) sum = (sum + 1) % 1000000007;
        }
    }

    return sum;
}