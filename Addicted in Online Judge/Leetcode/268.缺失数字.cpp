int missingNumber(int* nums, int numsSize)
{
    int i, sum = 0;
    for(i = 0; i < numsSize; i++)
    sum = nums[i] + sum; 
    return numsSize * (numsSize + 1) / 2 - sum;
}
