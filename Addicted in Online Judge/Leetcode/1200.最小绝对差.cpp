int shunxu(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int **minimumAbsDifference(int *arr, int arrSize, int *returnSize, int **returnColumnSizes)
{
    int **res = malloc(1024 * 1024 * sizeof(int *));
    int i, cow = 0, diff = INT_MAX;    
    if (!arr || arrSize < 2) 
    {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    qsort(arr, arrSize, sizeof(int), shunxu);
    for (i = 0; i < arrSize - 1; i++) 
        if (fabs(arr[i] - arr[i + 1]) < diff) diff = fabs(arr[i] - arr[i + 1]);

    for (i = 0; i < arrSize - 1; i++) 
    {
        if (fabs(arr[i] - arr[i + 1]) == diff) 
        {
            res[cow] = malloc(2 * sizeof(int));
            res[cow][0] = arr[i];
            res[cow][1] = arr[i + 1];
            cow++;
        }
    }

    int *retColSize = malloc(cow * sizeof(int));
    for (i = 0; i < cow; i++) retColSize[i] = 2;
    *returnColumnSizes = retColSize;
    *returnSize = cow;
    return res;
}