/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* replaceElements(int* arr, int arrSize, int* returnSize)
{
    int i, max = arr[arrSize - 1];
    int* f = malloc(1000000 * sizeof(int));
    memset(f, 0, 1000000);
    * returnSize = arrSize;
    
    for (i = arrSize - 1; i >= 0; i--)
    {
        if (i == arrSize - 1) f[i] = -1;
        else
        {
            max = max > arr[i + 1] ? max : arr[i + 1];
            f[i] = max;
        }
    }

    return f;
}
