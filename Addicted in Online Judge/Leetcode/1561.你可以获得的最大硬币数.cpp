int shunxu(const void*a, const void*b)
{
    return *(int*)a - *(int*)b;
}

int maxCoins(int* piles, int pilesSize)
{
    int i, j, sum = 0;    
    qsort(piles, pilesSize, sizeof(int), shunxu);

    for (i = pilesSize - 2, j = 0; i > 0, j < pilesSize / 3; i = i - 2, j++)
    {
        sum = sum + piles[i];
    }

    return sum;
}
