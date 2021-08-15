int rob(int* nums, int numsSize)
{
    int i, j, max;
    int dp[10000];
    
    if(!numsSize) return 0;
    else if (numsSize == 1) return nums[0];

    dp[0] = nums[0];
    dp[1] = nums[0] > nums[1] ? nums[0] : nums[1];
    if (numsSize == 2) return dp[1];
    max = dp[1];

    for (i = 2; i < numsSize; i++)
    {
        dp[i] = 0;
        for (j = 0; j < i - 1; j++)
        {
            dp[i] = dp[i] > (dp[j] + nums[i]) ? dp[i] : (dp[j] + nums[i]);
            max = dp[i] > max ? dp[i] : max;
        }
    }

    return max;
}
