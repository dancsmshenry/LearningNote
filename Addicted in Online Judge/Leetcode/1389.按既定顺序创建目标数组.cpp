/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* createTargetArray(int* nums, int numsSize, int* index, int indexSize, int* returnSize)
{
    int i, j;
    int f[10000];
    int* target = malloc(10000 * sizeof(int));
    *returnSize = numsSize;
    memset(target, 0, 10000);
    
    for (i = 0; i < indexSize; i++)
    {
        f[i] = index[i];
        for (j = 0; j < i; j++)
        if (f[i] <= f[j]) f[j] = f[j] + 1;
    }

    for (i = 0; i < indexSize; i++)
    target[f[i]] = nums[i];

    return target;
}
