int maxProduct(int* nums, int numsSize)
{
    int i, one = INT_MIN, two = INT_MIN;
    
    for (i = 0; i < numsSize; i++)
    {
        if (nums[i] >= one)
        {
            two = one;
            one = nums[i];
        }
        else if (nums[i] >= two) two = nums[i];
    }

    return (one - 1) * (two - 1);
}
