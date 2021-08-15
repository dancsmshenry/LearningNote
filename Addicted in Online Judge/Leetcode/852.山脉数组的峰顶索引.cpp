int peakIndexInMountainArray(int* arr, int arrSize)
{
    int i;
    
    for (i = 1; i < arrSize - 1; i++)
    {
        if (arr[i - 1] < arr[i] && arr[i + 1] < arr[i]) return i;
    }

    return 0;
}
