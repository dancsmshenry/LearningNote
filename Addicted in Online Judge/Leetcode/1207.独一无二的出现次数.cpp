int shunxu(const void*a, const void*b)
{
    return *(int*)a - *(int*)b;
}

bool uniqueOccurrences(int* arr, int arrSize)
{
    int i, ans = 1;
    int f[10000];
    memset(f, 0, 10000);
    qsort(arr, arrSize, sizeof(int), shunxu);

    for (i = 1; i < arrSize; i ++ )
    {
        if (arr[i] == arr[i - 1]) ans ++ ;
        else
        {
            f[ans] ++ ;
            if (i == arrSize - 1) f[1] ++ ;
            if (f[ans]  > 1 || f[1] > 1) return false;
            ans = 1;
        }
    }
    if (ans != 1 && f[ans] + 1 > 1) return false;

    return true;
}