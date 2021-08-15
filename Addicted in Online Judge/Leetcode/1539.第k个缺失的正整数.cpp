int findKthPositive(int* arr, int arrSize, int k)
{
    int i, j = 0, k1 = k;
    
    for (i = 1; i <= arr[arrSize - 1] + k; i++)
    {
        if (i != arr[j])
        {
            k1 = k1 - 1;
            if (k1 == 0) return i;
        }
        else if (i == arr[j] && j + 1 != arrSize) j++;
    }

    return 0;
}
