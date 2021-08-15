int countDigitOne(int n)
{
    long number, n1 = n, sum = 0, ans = 1;

    if (n <= 0) return 0;
    
    while(n1 != 0)
    {
        number = n1 % 10;
        if (number > 1) sum = sum + (1 + n1 / 10) * ans;
        else if (number == 1) sum = sum + (n % ans) + 1 + (n1 / 10) * ans;
        else sum = sum + (n1 / 10) * ans;
        ans = ans * 10;
        n1 = n1 / 10;
    }

    return sum;
}
