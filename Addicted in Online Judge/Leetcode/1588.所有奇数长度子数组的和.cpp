int sumOddLengthSubarrays(int* arr, int arrSize)
{
    int i, sum;
    int dp[300][300];
    for (i = 0; i <= arrSize; i++)
    {
        dp[i][0] = i / 2;
        if (i % 2 == 0) dp[i][1] = i / 2;
        else dp[i][1] = i / 2 + 1;
    }

    sum = dp[arrSize][1] * arr[0];
    for (i = 1; i < arrSize; i++)
    {
        sum = sum + ((dp[i][0] + 1) * dp[arrSize - i][1] + dp[i][1] * dp[arrSize - i][0]) * arr[i];
    }

    return sum;
}
