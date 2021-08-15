int maxSubArray(int* nums, int numsSize)
{
    int f[100000];
    int i, j, max = INT_MIN;
    f[0] = nums[0];
    
    for (i = 1; i < numsSize; i++)
    f[i] = f[i - 1] + nums[i];

    for (i = 0; i < numsSize; i++)
    {
        max = max > f[i] ? max : f[i];
        for (j = 0; j < i; j++)
        {
            max = max > f[i] - f[j] ? max : f[i] - f[j];
        }
    }

    return max;
}
