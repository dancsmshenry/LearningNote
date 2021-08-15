int minimumTotal(int** triangle, int triangleSize, int* triangleColSize)
{
    int i, j, min = INT_MAX, ans;
    int f[100009];
    memset(f, 0, 100009);
    f[0] = triangle[0][0];

    for (i = 1; i < triangleSize; i ++ )
    {
        f[i] = f[i - 1] + triangle[i][i];
        for (j = i - 1; j > 0; j -- ) f[j] = (f[j - 1] < f[j] ? f[j - 1] : f[j]) + triangle[i][j];
        f[0] += triangle[i][0];
    }

    for (i = 0; i < triangleSize; i ++ ) min = min < f[i] ? min : f[i];

    return min;
}