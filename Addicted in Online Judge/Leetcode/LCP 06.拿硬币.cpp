int minCount(int* coins, int coinsSize)
{
    int i, sum = 0;

    for (i = 0; i < coinsSize; i++)
    {
        if (coins[i] % 2 == 0) sum = sum + coins[i] / 2;
        else sum = sum + coins[i] / 2 + 1;
    }

    return sum;
}
