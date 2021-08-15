int jump(int *nums, int numsSize)
{
    int i, j;
    int f[100000];
    bool dp[100000];
    memset(dp, false, 100000);
    memset(f, 1000000, 100000);
    dp[0] = true;
    f[0] = 0;
    //if (nums[0] == 25000) return 2;这种做法无异于作弊，根本得不到提升

    for (i = 0; i < numsSize; i++)
    {
        if (dp[i] == true)
        {
            for (j = 1; j <= nums[i] && j + i < numsSize; j++)
            {
                dp[i + j] = true;
                f[i + j] = f[i + j] < f[i] + 1 ? f[i + j] : f[i] + 1;
            }
        }
    }

    return f[numsSize - 1];
}

//正确的做法
class Solution
{
public:
    int jump(vector<int> &nums)
    {
        int maxPos = 0, n = nums.size(), end = 0, step = 0;
        for (int i = 0; i < n - 1; ++i)
        {
            if (maxPos >= i)
            {
                maxPos = max(maxPos, i + nums[i]);
                if (i == end)
                {
                    end = maxPos;
                    ++step;
                }
            }
        }
        return step;
    }
};