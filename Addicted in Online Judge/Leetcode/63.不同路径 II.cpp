int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize) 
{
    int i, j, n = obstacleGridSize, m = obstacleGridColSize[0];
    int f[10000];
    memset(f, 0, 10000);
    if (obstacleGrid[0][0] == 1) return 0;
    else f[0] = 1;

    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < m; j++) 
        {
            if (obstacleGrid[i][j] == 1) 
            {
                f[j] = 0;
                continue;
            }
            if (j >= 1 && obstacleGrid[i][j - 1] == 0) 
                f[j] = f[j] + f[j - 1];
        }
    }

    return f[m - 1];
}//优化版本 

int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize) 
{
    int i, j, n = obstacleGridSize, m = obstacleGridColSize[0];
    int f[10000][10000];
    if (obstacleGrid[0][0] == 1) return 0;
    else f[0][0] = 1;

    for(i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (obstacleGrid[i][j] == 1) f[i][j] = 0;
            else if (j == 0 || i == 0) f[i][j] = 1;
            else f[i][j] = f[i - 1][j] + f[i][j -1];
        }
    }

    return f[n - 1][m - 1];
}//未优化版本 
