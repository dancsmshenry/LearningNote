int maximum69Number (int num)
{
    int i, number = num, ans = 1, n = 0, total;
    int f[100];
    while (number > 0)
    {  
        f[n++] = (number % 10) * ans;
        ans = ans * 10;
        number = number / 10;
    }

    for (i = n - 1; i >= 0; i--)
    {
        if (f[i] % 9 != 0)
        {
            total = num - f[i] + (f[i] / 6) * 9;
            return total;
        }
    }

    return num;
}
