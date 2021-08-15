int removeDuplicates(int* nums, int numsSize)
{
    int i, point1 = nums[0], point2 = 0;
    if (numsSize < 2) return numsSize;
    
    for (i = 1; i < numsSize; i++)
    {
        if (nums[i] != point1)
        {
            nums[point2++] = point1;
            point1 = nums[i];
        }
    }
    nums[point2] = point1;

    return point2 + 1;
}
