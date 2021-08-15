#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e6 + 3;     //一定要是质数，这样发生哈希冲突的概率会比较小

int h[N], e[N], ne[N], idx = 0;   //h[N]表示哈希表，e[N]和ne[N]表示链表

void insert(int x)
{
    int k = (x % N + N) % N;   //这里如果x为负数的话，那正常情况下x%N就是负数，而这样可以华为正数
    e[idx] = x;
    ne[idx] = h[k];
    h[k] = idx ++ ;
}

bool find(int x)
{
    int k = (x % N + N) % N;
    for (int i = h[k]; i != -1; i = ne[i])
        if (e[i] == x)
            return true;
    
    return false;
}

int main()        //拉链法形成哈希表
{
    int n;
    scanf("%d", &n);

    memset(h, -1, sizeof(h));

    while (n -- )
    {
        char op[2];   //规范输出，防止吸进其他的字符
        int x;
        scanf("%s%d", op, &x);

        if (*op == 'I') insert(x);
        else
        {
            if (find(x)) puts("yes");
            else puts("no");
        }
    }

    return 0;
}