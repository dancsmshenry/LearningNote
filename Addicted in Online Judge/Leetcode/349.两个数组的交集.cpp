/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int shunxu(const void*a, const void*b)
{
    return *(int*)a - *(int*)b;
}

int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize)
{
    int i, j, sum = 0;
    int* f = malloc(1000000 * sizeof(int));
    if (nums1Size == 0 || nums2Size == 0)
    {
        *returnSize = 0;
        return f;
    }
    for (i = 0; i < nums1Size; i++)
    {
        for (j = 0; j < nums2Size; j++)
        {
            if (nums1[i] == nums2[j]) f[sum++] = nums1[i];
        }
    }
    if (sum == 0)
    {
        *returnSize = 0;
        return f;
    }

    j = 1;
    qsort(f, sum, sizeof(int), shunxu);
    for (i = 1; i < sum; i++)
    {
        if (f[i] != f[i - 1]) f[j++] = f[i];
    }

    * returnSize = j;
    return f;
}
