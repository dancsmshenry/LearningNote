bool threeConsecutiveOdds(int* arr, int arrSize)
{
    int i, sum;
    if (arrSize <= 2) return false;
    
    for (i = 2; i < arrSize; i++)
    {
        sum = arr[i - 2] % 2 + arr[i - 1] % 2 + arr[i] % 2;
        if (sum == 3) return true;
    }

    return false;
}
