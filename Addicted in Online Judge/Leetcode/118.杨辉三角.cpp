/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generate(int numRows, int* returnSize, int** returnColumnSizes)
{
    *returnSize = numRows;
    *returnColumnSizes = (int*)malloc(numRows * sizeof(int));
    int **res = (int**)malloc((*returnSize) * sizeof(int*));

    for(int i = 0; i < *returnSize; i++)
    {
        (*returnColumnSizes)[i] = i + 1;
        res[i] = (int*)malloc((*returnColumnSizes)[i] * sizeof(int));
        res[i][0] = 1;
        res[i][i] = 1; 
    }

    for(int i = 2; i <= numRows - 1; i++)
    {
        for(int j = 1; j < i; j++)
            res[i][j] = res[i - 1][j - 1] + res[i - 1][j];
    }
    
    return res;
}