#include <stdio.h>
#incldue <stdlib.h>
int main()
{
	int Compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int findKthLargest(int* nums, int numsSize, int k)
{
    qsort(nums, numsSize, sizeof(int), Compare);

    return nums[numsSize - k];
}
 } 
