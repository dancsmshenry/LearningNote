int singleNumber(int* nums, int numsSize)
{
    int i, one = 0;

    for(i = 0; i < numsSize; i++)
    {
        one = one ^ nums[i];
    }

    return one;
}
