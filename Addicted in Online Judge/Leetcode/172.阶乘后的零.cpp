int trailingZeroes(int n)
{
    int total = 0, sum = n / 5;

    while(sum != 0)
    {
        total = total + sum;
        sum = sum / 5;
    }
    return total;
}
