/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getRow(int rowIndex, int* returnSize)
{
    int * f = malloc(100000 * sizeof(long));
    * returnSize = rowIndex + 1;
    
    for (int i = 0; i <= rowIndex; i ++ )
    {
        if (i == 0 || i == rowIndex) f[i] = 1;
        else f[i] = (long long)f[i - 1] * (rowIndex - i + 1) / i;
    }

    return f;
}