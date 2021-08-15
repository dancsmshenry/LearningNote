char * restoreString(char * s, int* indices, int indicesSize)
{
    int i;
    char * f = (char *)malloc(indicesSize + 7);
    memset(f, 0, indicesSize + 7);
    
    for (i = 0; i < indicesSize; i++)
    {
        f[indices[i]] = s[i];
    }

    return f;
}
