int minCostClimbingStairs(int* cost, int costSize)
{
    int i;
    int f[100000];
    f[0] = cost[0];
    f[1] = cost[1];
    
    for (i = 2; i < costSize; i++)
    {
        f[i] = f[i - 1] > f[i - 2] ? f[i - 2] : f[i - 1];
        f[i] = f[i] + cost[i];
    }
    return f[costSize - 1]  > f[costSize - 2] ? f[costSize - 2] : f[costSize - 1];
}
