int lengthOfLongestSubstring(char * s)
{
    int i, n = strlen(s), max = INT_MIN, point1 = 0, point2 = 1;
    if (n < 2) return n; 

    while (point2 < n)
    {
        for (i = point1; i < point2; i++)
        {
            if (s[i] == s[point2])
            {
                point1 = i + 1;
                break;
            }
        }
        max = max > (point2 - point1 + 1) ? max : (point2 - point1 + 1);
        point2 = point2 + 1;
    }

    return max;
}
