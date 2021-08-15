/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArrayByParity(int* A, int ASize, int* returnSize)
{
    int i, l1, j = 0, l = 0;
    int B[10000];
    int* f = malloc(ASize * sizeof(int));
    *returnSize = ASize;
    
    for (i = 0; i < ASize; i++)
    {
        if (A[i] % 2 == 0) f[j++] = A[i];
        else B[l++] = A[i];
    }

    for (i = j, l1 = 0; i < ASize; i++, l1++)
    f[i] = B[l1];

    return f;
}
