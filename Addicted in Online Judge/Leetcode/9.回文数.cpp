bool isPalindrome(int x)
{
    long total = 0, xx = x;
    if (x == 0) return true;
    if (xx < 0 || xx % 10 == 0) return false;

    while (xx != 0)
    {
        total = 10 * (xx % 10 + total);
        xx = xx / 10;
    }

    if (total / 10 == x) return true;
    else return false;
}
