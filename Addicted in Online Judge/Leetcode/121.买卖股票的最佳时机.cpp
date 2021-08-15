int maxProfit(int* prices, int pricesSize)
{
    int i, min, sum = 0;
    min = INT_MAX;

    for (i = 0; i < pricesSize; i++)
    {
        min = min < prices[i] ? min : prices[i];
        sum = sum > prices[i] - min ? sum : prices[i] - min;
    }

    return sum;
}
