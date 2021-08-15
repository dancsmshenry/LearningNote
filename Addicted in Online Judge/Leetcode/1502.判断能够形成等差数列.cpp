int shunxu(const void*a, const void*b)
{
    return *(int*)a - *(int*)b;
}

bool canMakeArithmeticProgression(int* arr, int arrSize)
{
    qsort(arr, arrSize, sizeof(int), shunxu);

    int i, ans = arr[1] - arr[0];
    for (i = 2; i < arrSize; i++)
    if (arr[i] - arr[i - 1] != ans) return false;

    return true;
}
