int maxSubArray(int* nums, int numsSize)
{
     int max, sum, i;
     max = sum = nums[0];
     for (i = 1; i < numsSize; i++)
	{
		if (sum >= 0) sum += nums[i];
		else sum = nums[i];
		max = max > sum ? max : sum;
	}
    return max;
}
