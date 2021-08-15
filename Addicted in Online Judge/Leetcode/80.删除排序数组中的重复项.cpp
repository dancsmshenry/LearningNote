int removeDuplicates(int* nums, int numsSize)
{
    int i, p = 2;
    if (numsSize <= 2) return numsSize;

    for (i = 2; i < numsSize; i++)
    {
        if (nums[i] != nums[p - 2]) nums[p++] = nums[i];
    }

    return p;
}
