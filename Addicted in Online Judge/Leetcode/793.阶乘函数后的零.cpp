int preimageSizeFZF(int K)
{
    int ans = 0;
    
    while (ans < K) ans = ans * 5 + 1;

    while (K > 0)
    {
        ans = (ans - 1) / 5;
        if (K / ans == 5) return 0;
        K %= ans;
    }

    return 5;
}