/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* smallerNumbersThanCurrent(int* nums, int numsSize, int* returnSize)
{
    int i, j;
    int* f = malloc(numsSize * sizeof(int));
    *returnSize = numsSize;
    
    for (i = 0; i < numsSize; i++)
    {
        f[i] = numsSize - 1;
        for (j = 0; j < numsSize; j++)
        {
            if (i == j) continue;
            else if (nums[i] <= nums[j]) f[i] = f[i] - 1;
        }
    }

    return f;
}
