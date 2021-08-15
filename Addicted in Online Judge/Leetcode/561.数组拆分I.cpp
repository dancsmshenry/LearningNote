int shunxu(const void*a, const void*b)
{
    return *(int*)a - *(int*)b;
}

int arrayPairSum(int* nums, int numsSize)
{
    int i, sum = 0;
    qsort(nums, numsSize, sizeof(int), shunxu);

    for (i = 0; i < numsSize; i = i + 2)
    sum += nums[i];

    return sum;
}
