int shunxu(const void*a, const void*b)
{
    return *(int*)a - *(int*)b;
}

int maxSatisfaction(int* satisfaction, int satisfactionSize)
{
    int i, sum = 0, max = INT_MIN;
    int f[1000000];

    qsort(satisfaction, satisfactionSize, sizeof(int), shunxu);//¿ìÅÅÄ£°å
    if (satisfaction[satisfactionSize - 1] <= 0) return 0;

    f[0] = satisfaction[0];
    for (i = 1; i < satisfactionSize; i++) 
    f[i] = f[i - 1] + satisfaction[i];

    for (i = satisfactionSize - 1; i >= 0; i--)
    {
        sum = sum + f[satisfactionSize - 1] - (i > 0 ? f[i - 1] : 0);
        max = max > sum ? max : sum;
    }
    
    return max;
}
