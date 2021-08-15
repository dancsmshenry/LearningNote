int subtractProductAndSum(int n)
{
    int zhiji, zhihe, num, m;
    zhiji = 1;
    zhihe = 0;
    num = n;

    while (num != 0)
    {
        m = num % 10;
        zhihe = zhihe + m;
        zhiji = zhiji * m;
        num = num / 10;
    }
    
    return zhiji - zhihe;
}
