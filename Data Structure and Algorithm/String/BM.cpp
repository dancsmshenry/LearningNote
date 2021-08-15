#include <cstdio>
#include <string.h>

#define MAX(x, y) x > y ? x : y

const int SIZE = 256;
const int MAX_CHAR = 256;

void PreBmBc(char *pattern, int m, int *bmBc)
{
    memset(bmBc, m, sizeof(bmBc));

    for (int i = 0; i < m - 1; i++)
    {
        bmBc[pattern[i]] = m - 1 - i;
    }
}

void suffix_old(char *pattern, int m, int suff[])
{
    suff[m - 1] = m;

    for (int i = m - 2; i >= 0; i--)
    {
        int j = i;
        while (j >= 0 && pattern[j] == pattern[m - 1 - i + j])
            j--;

        suff[i] = i - j;
    }
}

void suffix(char *pattern, int m, int suff[])
{
    int f;

    suff[m - 1] = m;
    int g = m - 1;
    for (int i = m - 2; i >= 0; --i)
    {
        if (i > g && suff[i + m - 1 - f] < i - g)
            suff[i] = suff[i + m - 1 - f];
        else
        {
            if (i < g)
                g = i;
            f = i;
            while (g >= 0 && pattern[g] == pattern[g + m - 1 - f])
                --g;
            suff[i] = f - g;
        }
    }
}

void PreBmGs(char *pattern, int m, int *bmGs)
{
    int suff[SIZE];

    // 计算后缀数组
    suffix(pattern, m, suff);

    // 先全部赋值为m，包含Case3
    memset(bmGs, m, sizeof(bmGs));

    // Case2
    for (int i = m - 1, j = 0; i >= 0; i--)
    {
        if (suff[i] == i + 1)
        {
            for (; j < m - 1 - i; j++)
            {
                if (bmGs[j] == m)
                    bmGs[j] = m - 1 - i;
            }
        }
    }

    // Case1
    for (int i = 0; i < m - 1; i++)
    {
        bmGs[m - 1 - suff[i]] = m - 1 - i;
    }
}

void BoyerMoore(char *pattern, int m, char *text, int n)
{
    int i, j = 0, bmBc[MAX_CHAR], bmGs[SIZE];

    // Preprocessing
    PreBmBc(pattern, m, bmBc);
    PreBmGs(pattern, m, bmGs);

    // Searching
    while (j <= n - m)
    {
        for (i = m - 1; i >= 0 && pattern[i] == text[i + j]; i--)
            ;
        if (i < 0)
        {
            printf("Find it, the position is %d\n", j);
            j += bmGs[0];
            return;
        }
        else
        {
            j += MAX(bmBc[text[i + j]] - m + 1 + i, bmGs[i]);
        }
    }
}

int main()
{
    char text[256], pattern[256];

    scanf("%s%s", text, pattern);
    BoyerMoore(pattern, strlen(pattern), text, strlen(text));

    return 0;
}