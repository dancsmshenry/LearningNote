int maxValue(int** grid, int gridSize, int* gridColSize)
{
    int row = gridSize, col = *gridColSize;
    if (grid == NULL || gridSize <= 0) return 0;
    
    for (int i = 1; i < col; i++)
    grid[0][i] += grid[0][i - 1];
    for (int i = 1; i < row; i++)
    grid[i][0] += grid[i - 1][0];

    for (int i = 1; i < row; i++) 
    {
        for (int j = 1; j < col; j++) 
        {
            grid[i][j] += grid[i - 1][j] > grid[i][j - 1] ? grid[i - 1][j] : grid[i][j - 1];
        }
    }

    return grid[row - 1][col - 1];
}
