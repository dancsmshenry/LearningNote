/**
 * Note: The returned array must be malloced, assume caller calls free().
 */


bool* kidsWithCandies(int* candies, int candiesSize, int extraCandies, int* returnSize)
{
    bool* f = malloc(candiesSize * sizeof(bool));
    * returnSize = candiesSize;
    int i, max = 0;
    
    for (i = 0; i < candiesSize; i++)
    max = max > candies[i] ? max : candies[i];

    for (i = 0; i < candiesSize; i++)
    f[i] = candies[i] + extraCandies >= max;

    return f;
}
