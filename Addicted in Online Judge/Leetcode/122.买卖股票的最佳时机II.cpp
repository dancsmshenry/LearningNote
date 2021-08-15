int maxProfit(int* prices, int pricesSize)
{
    int i, sum = 0;
    
    for (i = 1; i < pricesSize; i++)
        if (prices[i] > prices[i - 1]) sum = sum + prices[i] - prices[i - 1];

    return sum;
}
