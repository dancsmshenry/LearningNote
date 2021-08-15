int numDecodings(char * s)
{
    int n, i;
    int dp[10000];
    n = strlen(s);
    if (n == 1 && s[0] == '0') return 0;
    else if (n == 1 && s[0] != '0') return 1;
    if (s[0] == '0') dp[0] = 0;
    else dp[0] = 1;

    for (i = 1; i < n; i++)
    {
        if (s[i] == '0')
        {
            if (s[i - 1] == '1' || s[i - 1] == '2') dp[i] = i > 1 ? dp[i - 2] : dp[i - 1];
            else return 0; 
        }
        else if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] != '7' && s[i] != '8' && s[i] != '9'))
        {
            dp[i] = i > 1 ? (dp[i - 1] + dp[i - 2]) : (dp[i] = dp[i - 1] + 1);
        }
        else dp[i] = dp[i - 1];
    }

    return dp[n - 1];
}
