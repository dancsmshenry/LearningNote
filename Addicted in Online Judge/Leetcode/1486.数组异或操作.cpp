int xorOperation(int n, int start)
{
    int i, ans = 0;

    for (i = 0; i < n; ++i) 
    {
        ans = ans ^ (start + i * 2);
    }
    
    return ans;
}
