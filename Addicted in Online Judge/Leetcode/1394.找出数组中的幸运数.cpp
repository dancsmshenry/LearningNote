int findLucky(int* arr, int arrSize)
{
    int i, ans = -1;
    int f[10000];
    memset(f, 0, 10000);
    
    for (i = 0; i < arrSize; i++) 
    f[arr[i]]++;

    for (i = 0; i < arrSize; i++)
    if (f[arr[i]] == arr[i]) ans = ans > arr[i] ? ans : arr[i];

    return ans;
}
