int shunxu(const void*a, const void*b)
{
    return *(int*)a - *(int*)b;
}

int numRescueBoats(int* people, int peopleSize, int limit)
{
    int p1 = 0, p2 = peopleSize - 1, sum = 0;
    qsort(people, peopleSize, sizeof(int), shunxu);

    while (p1 <= p2)
    {
        if (people[p1] + people[p2] <= limit) p1++;
        sum++;
        p2--;
    }
    
    return sum;
}
