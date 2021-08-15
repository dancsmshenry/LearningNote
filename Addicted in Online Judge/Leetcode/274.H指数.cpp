int shunxu(const void*a, const void*b)
{
    return *(int*)a - *(int*)b;
}

int hIndex(int* citations, int citationsSize)
{
    int i ,length = citationsSize;
    qsort(citations, citationsSize, sizeof(int), shunxu);

    for (i = 0; i < citationsSize; i++)
    {
        if (citations[i] < length) length--;
    }

    return length;
}//解法一

int shunxu(const void*a, const void*b)
{
    return *(int*)a - *(int*)b;
}

int hIndex(int* citations, int citationsSize)
{
    qsort(citations, citationsSize, sizeof(int), shunxu);

    for (int i = 0; i < citationsSize; i++)
    {
        if (citations[i] >= (citationsSize - i)) return citationsSize - i;
    }

    return 0;
}//解法二
//能不写就别写吧，这个数据是有问题的
/*
题目的意思是说h指数，是发的h篇文章中，每篇被引用的次数至少为h，原文：
Since the researcher has 3 papers with at least 3 citations each
但是，在下面又说：
the remaining two with no more than 3 citations each, their h-index is 3.
我真的是佛了555（即3是不超过3，也最少是3）
 */