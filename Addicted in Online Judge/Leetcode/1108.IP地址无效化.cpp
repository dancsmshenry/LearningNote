char * defangIPaddr(char * address)
{
    int i, j = 0, length = strlen(address);
    char * f = (char *)malloc(length + 7);
    memset(f, 0, length + 7);

    for(i = 0; i < length; i++)
    {
        if(address[i] == '.')
        {
            f[j] = '[';
            f[j + 1] = '.';
            f[j + 2] = ']';
            j = j + 3;
        }
        else f[j++] = address[i];
    }

    return f;
}
