int mySqrt(int x)
{
    int mid, high, low = 0;
    high = x;
    if (x == 0 || x == 1) return x;

    while(high - low > 1)
    {
        mid = (high + low) / 2;
        if (x / mid == mid) return mid;
        else if (mid > x / mid) high = mid;
        else low = mid;
    }
    return low;
}
