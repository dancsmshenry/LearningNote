#include <iostream>

using namespace std;

typedef struct
{                         //总共有2n-1个结点，不使用0下标；每合成一个点就把新的点添加到后面
    int weight;           //存储当前这个结点的权值
    int parent, lch, rch; //parent=0表示当前还是单个结点，即没有合成为其他的子树；否则就表示它双亲的下标位置
    //lch和rch表示子树的两个儿子的下标
} HTNode, *HuffmanTree;

void Select(HuffmanTree HT, int j, int &s1, int &s2)
{
}

void CreateHuffmanTree(HuffmanTree HT, int n)
{ //哈夫曼算法
    if (n <= 1)
        return;
    int m = 2 * n - 1;      //数组中一共2*n-1个元素
    HT = new HTNode[m + 1]; //0号元素不用，HT[m]表示根结点
    for (int i = 1; i <= m; i++)
    { //将2n-1个元素的lch,rch,parent设置为0
        HT[i].lch = 0;
        HT[i].rch = 0;
        HT[i].parent = 0;
    }
    for (int i = 1; i <= n; ++i)
    { //输入前n个元素的weight值
        cin >> HT[i].weight;
    }

    //初始化结束，下面建立哈夫曼树

    for (int i = n + 1; i <= m; ++i)
    { //合并产生n-1个结点-构造HuffmanTree
        int s1 = 0, s2 = 0;
        Select(HT, i - 1, s1, s2); //在HT[k]中选择两个其双亲域为0，且权值最小的结点，并返回它们在HT中的序号s1和s2
        HT[s1].parent = i;
        HT[s2].parent = i; //表示从F中删除s1，s2
        HT[i].lch = s1;
        HT[i].rch = s2;                               //s1,s2为该结点的左右孩子
        HT[i].weight = HT[s1].weight + HT[s2].weight; //i的权值为左右孩子权值之和
    }
}