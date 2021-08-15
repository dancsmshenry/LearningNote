/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* distributeCandies(int candies, int num_people, int* returnSize)
{
    int i = 0, total = candies, number = 1;
    int* f = malloc(10000 * sizeof(int));
    memset(f, 0, 10000);
    * returnSize = num_people;
    
    while (1)
    {
        if (total >= number)
        {
            f[i % num_people] = f[i % num_people] + number;
            total = total - number;
            number++;
            i++;
        }
        else
        {
            f[i % num_people] = f[i % num_people] + total;
            break;
        }
    }

    return f;
}
