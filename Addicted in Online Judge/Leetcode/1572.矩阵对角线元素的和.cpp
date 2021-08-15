int diagonalSum(int** mat, int matSize, int* matColSize)
{
    int i, sum = 0;
    if (mat == NULL) return 0;
    
    for (i = 0; i < matSize; i++)
    {
        sum = sum + mat[i][i];
        if (matSize - i - 1 != i) sum = sum + mat[i][matSize - i - 1];
    }

    return sum;
}
