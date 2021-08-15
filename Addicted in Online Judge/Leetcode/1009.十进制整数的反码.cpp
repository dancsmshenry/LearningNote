int bitwiseComplement(int N)
{
    int num1 = N, ans = 0, total = 0;
    if (num1 == 0) return 1;

    while (num1 != 0)
    {
        if (num1 % 2 == 0) total = total + pow(2, ans);
        ans++;
        num1 /= 2;
    }

    return total;
}