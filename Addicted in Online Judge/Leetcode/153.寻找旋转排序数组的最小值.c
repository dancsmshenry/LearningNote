int findMin(int* nums, int numsSize)
{
    int i, min = nums[0];

    for (i = 1; i < numsSize; i++)
    {
        if (nums[i - 1] < nums[i]) continue;
        else
        {
            min = min < nums[i] ? min : nums[i];
            break;
        }
    }

    return min;
}