/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* T, int TSize, int* returnSize)
{
    int i, j = 0, j1;
    int a[40000] = {0};//a是一个栈，其中存储的是数组的坐标
    int* f = malloc(40000 * sizeof(int));
    memset(f, 0, 40000);
    *returnSize = TSize;

    for (i = 1; i < TSize; i++)
    {
        if (T[i] > T[a[j]])
        {
            j1 = j;//j是栈顶的坐标
            while(j1 >= 0 && T[i] > T[a[j1]])//如果栈顶不为空，并且当前元素大于栈顶元素
            {
                f[a[j1]] = i - a[j1];//则栈顶元素踢出，栈顶元素在f数组的坐标等于当前元素的坐标减去栈顶元素
                a[j1--] = i; //踢出栈顶元素后，新元素入栈（可为什么要减减啊？？）
                //j--的解释：当前的j1是用来检验从栈顶元素到栈底元素是否有小于当前元素的
            }
        }
        else a[++j] = i;//如果当前元素小于等于栈顶元素，则当前元素进栈
    }

    return f;
}
/*
 * Note: The returned array must be malloced, assume caller calls free().
int* dailyTemperatures(int* T, int TSize, int* returnSize)
{
    int i, j, count;
    int *result = (int *)malloc(sizeof(T[0])*TSize);
    *returnSize = TSize;

    for (i = 0; i < TSize; i++)
    {
        count = 0;
        for (j = i + 1; j < TSize; j++) 
        {
            if (T[i] < T[j]) 
            {
                count = j - i;
                break;
            }
        }
        result[i] = count;
    }

    return result;
}
*/
//这是一种超时的写法，n方确实难顶，所以如果能用数据结构就用数据结构来解决问题