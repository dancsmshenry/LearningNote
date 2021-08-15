int shunxu(const void*a, const void*b)
{
    return *(int*)a - *(int*)b;
}

int distributeCandies(int* candies, int candiesSize)
{
    int i, p1 = 0;
    qsort(candies, candiesSize, sizeof(int), shunxu);

    for (i = 1; i < candiesSize; i ++ )
    {
        if (candies[p1] != candies[i]) candies[ ++ p1] = candies[i];
    }

    return (p1 + 1 > (candiesSize / 2)) ? (candiesSize / 2) : p1 + 1;
}