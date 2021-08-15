bool isPerfectSquare(int num)
{   
    long left = 0, right = num / 2, mid;
    if (num <= 1) return true;

    while (left <= right)
    {
        mid = right + (left - right) / 2;
        if (mid * mid == num) return true;
        if (mid * mid < num) left = mid + 1;
        else right = mid + 1;
    }

    return 0;
}
