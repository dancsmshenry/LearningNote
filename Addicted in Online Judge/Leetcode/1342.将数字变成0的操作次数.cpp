int numberOfSteps (int num)
{
    int n, sum = 0;
    n = num;

    while (n != 0)
    {
        if (n % 2 == 0) n = n /2;
        else n = n - 1;
        sum = sum + 1;
    }

    return sum;
}
