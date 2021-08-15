/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* shuffle(int* nums, int numsSize, int n, int* returnSize)
{
    int i = 0, j1 = 0, j2 = n;
    int* f = malloc(numsSize * sizeof(int));
    * returnSize = numsSize;

    while(i < numsSize)
    {
        if (i % 2 == 0)
        {
            f[i] = nums[j1];
            j1 = j1 + 1;
        }
        else
        {
            f[i] = nums[j2];
            j2 = j2 + 1;
        }
        i = i + 1;
    }

    return f;
}
