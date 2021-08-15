int hammingDistance(int x, int y)
{
    int x1 = x, y1 = y, sum = 0;

    while (x1 > 0 || y1 > 0)
    {
        if ((x1 % 2) != (y1 % 2)) sum++;
        x1 = x1 / 2;
        y1 = y1 / 2;
    }

    return sum;
}
