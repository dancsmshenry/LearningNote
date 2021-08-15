/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* runningSum(int* nums, int numsSize, int* returnSize)
{
    int* f = malloc(numsSize * sizeof(int));
    * returnSize = numsSize;
    f[0] = nums[0];

    for(int i = 1; i < numsSize; i++)
        f[i] = f[i - 1] + nums[i];
    
    return f;
}
