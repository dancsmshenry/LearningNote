int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int findContentChildren(int* g, int gSize, int* s, int sSize)
{
    int j = sSize - 1, i = gSize - 1, sum = 0;
    if (gSize == 0 || sSize == 0) return 0;
    qsort (g, gSize, sizeof(int), compare);
    qsort (s, sSize, sizeof(int), compare);
    
    while (i >=0 && j >=0)
    {
        if (s[j] >= g[i])
        {
            i--;
            j--;
            sum++;
        }
        else i--;
    }

    return sum;
}
