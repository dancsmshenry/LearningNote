int maxScore(int* cardPoints, int cardPointsSize, int k)
{
    int i, max, number;
    int f[100000];
    
    f[0] = cardPoints[0];
    for (i = 1; i < cardPointsSize; i++)
    {
        f[i] = f[i - 1] + cardPoints[i];
    }
    if (k == cardPointsSize) return f[k - 1];

    max = f[cardPointsSize - 1] - f[cardPointsSize - 1 - k];
    for (i = 1; i <= k; i++)
    {
        number = f[cardPointsSize - 1] - (f[cardPointsSize - 1 - k + i] - f[i - 1]);
        max = max > number ? max : number;
    }

    return max;
}
