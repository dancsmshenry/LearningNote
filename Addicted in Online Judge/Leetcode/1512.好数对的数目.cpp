int numIdenticalPairs(int* nums, int numsSize)
{
    int hash[101] = {0};
    int i, ans = 0;

    for(i = 0; i < numsSize; i++)
    {
        hash[nums[i]]++;
        ans = ans + hash[nums[i]] - 1;
    }

    return ans;
}

int numIdenticalPairs(int* nums, int numsSize)
{
    int i, j, ans = 0;
    
    for (i = 0; i < numsSize; i++)
    {
        for (j = i + 1; j < numsSize; j++)
        if (nums[i] == nums[j]) ans++;
    }

    return ans;
}
