int reverse(int x)
{
    long sum = 0, x1 = x;
    if (x == 0 || x > 2147483647 || x < -2147483648) return 0;
    
    while (x1 != 0)
    {
        sum = sum * 10 + x1 % 10;
        x1 = x1 / 10;
    }
    if (sum > INT_MAX || sum < INT_MIN) return 0;
    
    return sum;
}
