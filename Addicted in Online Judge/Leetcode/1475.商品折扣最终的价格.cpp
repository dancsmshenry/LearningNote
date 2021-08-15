/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* finalPrices(int* prices, int pricesSize, int* returnSize)
{
    int i, j;
    int* f = malloc(10000 * sizeof(int));
    memset(f, 0, 10000);
    * returnSize = pricesSize;
    
    for (i = 0; i < pricesSize; i++)
    {
        for (j = i + 1; j < pricesSize; j++)
        {
            if (prices[i] >= prices[j])
            {
                f[i] = prices[i] - prices[j];
                break;
            }
            else if (j == pricesSize - 1) f[i] = prices[i];
        }
    }

    f[pricesSize - 1] = prices[pricesSize - 1];
    return f;
}
