#include <iostream>
#include <cstring>

using namespace std;

const int N = 2e5 + 3, null = 0x3f3f3f3f;  //数组一定要开到数据的两到三倍，减少哈希冲突

int h[N];

int find(int x)
{
    int k = (x % N + N) % N;

    while (h[k] != null && h[k] != x)
    {
        k ++ ;
        if (k == N) k = 0;
    }

    return k;
}

int main()   //开放寻址法
{
    int n;
    scanf("%d", &n);

    memset(h, 0x3f, sizeof(h));        //按字节来算的，int型数组一个数有四个字节，所以每一个字节都是0x3f，即0x3f3f3f3f
    //比较常见的是-1和0，0的话就都是0，-1的话就都是-1

    while (n -- )
    {
        char op[2];
        int x;
        scanf("%s %d", op, &x);

        int k = find(x);
        if (*op == 'I') h[k] = x;
        else
        {
            if (h[k] != null) puts("Yes");
            else puts("No");
        }
    }

    return 0;
}