int countNegatives(int** grid, int gridSize, int* gridColSize)
{
    int i, j, count = 0, m = gridSize, n;
    n = * gridColSize;

    for (i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            if (grid[i][j] < 0) count++;
        }
    }
    
    return count;
}
