int findNumbers(int* nums, int numsSize)
{
    int result = 0, i, sum, num;
    
    for (i = 0; i < numsSize; i++)
    {
        sum = 1;
        num = nums[i];
        while(num >= 10)
        {
            num = num / 10;
            sum++;
        }
        if (sum % 2 == 0) result++;
    }

    return result;
}
