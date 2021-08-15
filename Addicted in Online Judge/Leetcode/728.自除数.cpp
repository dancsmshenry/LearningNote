/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* selfDividingNumbers(int left, int right, int* returnSize)
{
    int i, y, tmp, count = 0;
    int *num=(int *)malloc(sizeof(int)*200);
    bool f[100000];
    memset(f, true, 10001);
    for(i = left; i <= right; i++)
    {
        tmp = i;
        while(tmp != 0)
        {
            y = tmp % 10;
            if(y == 0 || i % y != 0)
            {
                f[i] = false;
                break;
            }
            tmp = tmp / 10;
        }
        if(f[i] == true)
        {
            num[count] = i;
            count++;
        }
    }

    *returnSize = count;
    return num;
}
