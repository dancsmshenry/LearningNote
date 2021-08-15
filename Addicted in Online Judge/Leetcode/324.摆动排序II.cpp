int shunxu(const void*a, const void*b)
{
    return *(int*)a - *(int*)b;
}

void wiggleSort(int* nums, int numsSize)
{   
    int i, i1 = 0, j, j1 = 0;
    int mid = (numsSize % 2 == 0) ? numsSize / 2 - 1: numsSize / 2;
    int min[10000000], max[10000000];
    qsort(nums, numsSize, sizeof(int), shunxu);

    for (i = 0; i <= mid; i ++ ) min[i1 ++ ] = nums[i];
    for (j = mid + 1; j < numsSize; j ++ ) max[j1 ++ ] = nums[j];

    for (i = 0; i < numsSize; i ++ )
    {
        if (i % 2 == 0) nums[i] = min[ -- i1];
        else nums[i] = max[ -- j1]; 
    }
}