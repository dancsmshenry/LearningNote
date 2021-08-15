char * toLowerCase(char * str)
{
    int i, n = strlen(str);
    char * f = (char *)malloc(n + 7);
    memset(f, 0, n + 7);  

    for (i = 0; i < n; i++)
    {
        if (str[i] <= 'Z' && str[i] >= 'A') f[i] = str[i] + 32;
        else f[i] = str[i];
    }

    return f;
}
