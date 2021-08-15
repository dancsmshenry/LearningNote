bool canJump(int* nums, int numsSize)
{
    bool f[100000];
    memset(f, false, 100000);
    if (numsSize == 1) return true;
    else if (nums[0] == 0) return false;
    f[0] = true;
    
    for (int i = 0; i < numsSize; i++)
    {
        if (f[i] == true)
        {
            for (int j = 1; j <= nums[i]; j++)
            f[i + j] = true;
        }
    }

    return f[numsSize - 1];
}
