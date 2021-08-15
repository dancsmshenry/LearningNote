/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* plusOne(int* digits, int digitsSize, int* returnSize)
{
    int i, ans = 0, buer = 0;
    int* f = malloc(100000 * sizeof(int));

    for (i = 0; i < digitsSize; i++)
    {
        if (digits[i] == 9) buer++;
        if (buer == digitsSize)
        {
            f[0] = 1;
            for (i = 1; i <= digitsSize; i++) f[i] = 0;
            * returnSize = digitsSize + 1;
            return f;
        }
    }

    for (i = digitsSize - 1; i >= 0; i--)
    {
        if (i == digitsSize - 1)
        {
            f[i] = (digits[i] + 1 + ans) % 10;
            if ((digits[i] + 1 + ans) > 9) ans = 1;
            else ans = 0;
        }
        else
        {
            f[i] = (digits[i] + ans) % 10;
            if ((digits[i] + ans) > 9) ans = 1;
            else ans = 0;
        }
    }

    * returnSize = digitsSize;
    return f;
}
