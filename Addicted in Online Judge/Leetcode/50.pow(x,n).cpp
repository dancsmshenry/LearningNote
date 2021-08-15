double myPow(double x, int n)
{
    double result = 1;

    if (n == 0) return 1;
    else if (n > 0)
    {
        while (n != 1)
            if (n % 2 == 0)
            {
                x = x * x;
                n = n / 2;
            }
            else
            {
                result = result * x;
                n = n - 1;
                x = x * x;
                n = n / 2;
            }
        return result * x;
    }
    else
    {
        while (n != -1)
            if (n % 2 == 0)
            {
                x = x * x;
                n = n / 2;
            }
            else
            {
                result = result * x;
                n = n + 1;
                x = x * x;
                n = n / 2;
            }
        return (1 / (result * x));
    }
}
