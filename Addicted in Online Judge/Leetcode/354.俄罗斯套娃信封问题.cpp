int cmdHelper(const void *a, const void *b)
{
    int *a_arr = *(int **)a;
    int *b_arr = *(int **)b;

    if(a_arr[0] == b_arr[0]) return b_arr[1] - a_arr[1]; 
    else return a_arr[0] - b_arr[0]; 
}

int maxEnvelopes(int** envelopes, int envelopesSize, int* envelopesColSize)
{
    int i, j, max = 0;
    int dp[10000];
    if (envelopesSize == 0) return 0;
    qsort(envelopes, envelopesSize, sizeof(int **), cmdHelper);

    for (i = 0; i < envelopesSize; i++) 
    {
        dp[i] = 1;
        for (j = 0; j < i; j++) 
            if (envelopes[i][1] > envelopes[j][1]) dp[i] = dp[i] > dp[j] + 1 ? dp[i] : dp[j] + 1;
        max = max > dp[i] ? max : dp[i];
    }

    return max;
}
