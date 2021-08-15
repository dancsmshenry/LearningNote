int findTheDistanceValue(int* arr1, int arr1Size, int* arr2, int arr2Size, int d)
{
    int i, j, sum = 0;
    
    for (i = 0; i < arr1Size; i++)
    {
        for (j = 0; j < arr2Size; j++)
        {
            if (abs(arr1[i] - arr2[j]) <= d) break;
            else if (j == arr2Size - 1) sum++;
        }
    }

    return sum;
}
