int numJewelsInStones(char * J, char * S)
{
    int i, j;
    int length1, length2, total = 0;   
    length1 = strlen(J);
    length2 = strlen(S);

    for (i = 0; i < length1; i++)
    {
        for (j = 0; j < length2; j++)
        {
            if (J[i] == S[j]) total++;
        }
    }

    return total;
}
