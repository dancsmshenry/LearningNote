int findComplement(int num)
{
    int num1 = num, ans = 0, total = 0;

    while (num1 != 0)
    {
        if (num1 % 2 == 0) total = total + pow(2, ans);
        ans++;
        num1 /= 2;
    }

    return total;
}