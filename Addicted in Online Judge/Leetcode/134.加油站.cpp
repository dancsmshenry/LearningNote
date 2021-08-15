#include <stdio.h>
int main()
{
    int i, oil = 0, total_oil = 0;
    int gasSize, costSize, station = 0;
    int gas[1000], cost[1000];
    scanf("%d %d", &gasSize, &costSize);
    for(i = 0; i < gasSize; i++) scanf("%d", &gas[i]);
    for(i = 0; i < costSize; i++) scanf("%d", &cost[i]);
    
    for (i = 0; i < gasSize; i++)
    {
        total_oil += gas[i] - cost[i];
        oil += gas[i] - cost[i];
        if (oil < 0)
        {
            oil = 0;
            station = i + 1;
        }
    }

    printf("%d", total_oil < 0 ?  -1: station);
    return 0;
} 
