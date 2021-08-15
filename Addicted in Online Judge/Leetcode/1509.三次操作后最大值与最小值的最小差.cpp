int shunxu(const void*a, const void*b)
{
    return *(int*)a - *(int*)b;
}

int minDifference(int* nums, int numsSize)
{
    int i, min = INT_MAX;
    if (numsSize < 5) return 0;
    qsort(nums, numsSize, sizeof(int), shunxu);

    for (i = 1; i < 5; i++)
    {
        min = min < (nums[numsSize - i] - nums[4 - i]) ? min : (nums[numsSize - i] - nums[4 - i]);
    }

    return min;
}