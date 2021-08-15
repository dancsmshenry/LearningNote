int busyStudent(int* startTime, int startTimeSize, int* endTime, int endTimeSize, int queryTime)
{
    int i, sum = 0;
    
    for (i = 0; i < startTimeSize; i++)
        if (startTime[i] <= queryTime && endTime[i] >= queryTime) sum++;

    return sum;
}
