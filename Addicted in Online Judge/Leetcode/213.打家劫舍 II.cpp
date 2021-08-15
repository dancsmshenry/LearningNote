int rob(int* nums, int numsSize)
{
    int dp1[10000], dp2[10000];
    int i, max1, max2;
    if (numsSize == 0) return 0;
    else if (numsSize == 1) return nums[0];
    
    dp2[0] = nums[0];
    dp2[1] = nums[1] > nums[0] ? nums[1] : nums[0];
    if (numsSize == 2) return dp2[1];
    for (i = 2; i < numsSize - 1; i++)
    {
        dp2[i] = nums[i] + dp2[i - 2] > dp2[i - 1] ? nums[i] + dp2[i - 2] : dp2[i - 1];
        if (i > 2) dp2[i] = dp2[i] > dp2[i - 3] + nums[i] ? dp2[i] : dp2[i - 3] + nums[i];
    }
    max2 = dp2[numsSize - 2];

    dp1[0] = 0;
    dp1[1] = nums[1];
    dp1[2] = nums[1] > nums[2] ? nums[1] : nums[2];
    for (i = 3; i < numsSize; i++)
    {
        dp1[i] = nums[i] + dp1[i - 2] > dp1[i - 1] ? nums[i] + dp1[i - 2] : dp1[i - 1];
        dp1[i] = dp1[i] > dp1[i - 3] + nums[i] ? dp1[i] : dp1[i - 3] + nums[i];
    }
    max1 = dp1[numsSize - 1];
    
    return max1 > max2 ? max1 : max2;
}
