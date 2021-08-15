int shunxu(const void*a, const void*b)
{
    return *(int*)a - *(int*)b;
}

int findDuplicate(int* nums, int numsSize)
{
    qsort(nums, numsSize, sizeof(int), shunxu);
    
    for(int i = 1; i < numsSize; i++)
    {
        if (nums[i] == nums[i - 1]) return nums[i];
    }

    return 0;
}
