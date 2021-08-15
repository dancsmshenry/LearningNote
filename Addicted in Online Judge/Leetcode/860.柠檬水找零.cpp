bool lemonadeChange(int *bills, int billsSize)
{
    int five = 0;
    int ten = 0;
    int tewnty = 0;
    int i;
    for (i = 0; i < billsSize; i++)
    {
        if (bills[i] == 5)
        {
            five++;
        }
        else if (bills[i] == 10)
        {
            ten++;
            five--;
        }
        else
        {
            tewnty++;
            if (ten == 0)
            {
                five--;
                five--;
            }
            else
            {
                ten--;
            }
            five--;
        }
        if (five < 0 || ten < 0)
        {
            return false;
        }
    }
    return true;
}
