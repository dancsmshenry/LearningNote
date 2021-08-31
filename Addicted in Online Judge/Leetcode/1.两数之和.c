/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    int i, j;
    int* f = malloc(numsSize * sizeof(int));
    * returnSize = 2;
    f[0] = 0;
    f[1] = 0;

    for (i = 0; i < numsSize; i++)
    {
        for (j = numsSize - 1; j > i; j--)
        if (nums[i] + nums[j] == target)
        {
            f[0] = i;
            f[1] = j;

            return f;
        }
    }

    return f;
}
