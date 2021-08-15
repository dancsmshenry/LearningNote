int longestMountain(int *A, int ASize)
{
    int i, j1, j2, max, sum = 0;

    for (i = 1; i < ASize - 1; i++)
    {
        if (A[i] > A[i - 1] && A[i] > A[i + 1])
        {
            max = 3;
            j2 = i - 1;
            while (j2 > 0)
            {
                if (A[j2 - 1] < A[j2])
                {
                    max++;
                    j2--;
                }
                else
                    break;
            }
            j1 = i + 1;
            while (j1 < ASize - 1)
            {
                if (A[j1 + 1] < A[j1])
                {
                    max++;
                    j1++;
                }
                else
                    break;
            }
            sum = sum > max ? sum : max;
        }
    }

    return sum;
}
