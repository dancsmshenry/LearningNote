void moveZeroes(int* nums, int numsSize)
{
    int i, number = 0, ans = 0;
    
    for (i = 0; i < numsSize; i++)
    if (nums[i] != 0) number = number + 1;

    for (i = 0; i < numsSize; i++)
    {
        if (nums[i] != 0) 
        {
            nums[ans] = nums[i];
            ans  = ans + 1;
        }
    }

    for (i = number; i < numsSize; i++) nums[i] = 0;
}
