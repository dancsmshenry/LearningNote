int calculate(char* s)
{
    int i = 0, x = 1, y = 0, len = strlen(s);

    while (i < len)
    {
        if (s[i] == "A") x = x * 2 + y;
        else y = 2 * y + x;
        i++;
    }

    return x + y;
}
