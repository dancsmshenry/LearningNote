/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* decompressRLElist(int* nums, int numsSize, int* returnSize)
{
    int i, j, n = 0;
    int* f = malloc(1000000 * sizeof(int));
    
    for (i = 0; i < numsSize; i = i + 2)
    {
        for (j = 0; j < nums[i]; j++)
        {
            f[n++] = nums[i + 1];
        }
    }

    *returnSize = n;
    return f;
}
