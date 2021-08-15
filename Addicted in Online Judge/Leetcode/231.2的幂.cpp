bool isPowerOfTwo(int n)
{
    long m;
    m = 1;
    if (n <= 0) return false;

    while(1)
    {
        if (n == m) return true;
        else if (n < m) return false; 
        else m = m * 2;
    }

    return true;
}
