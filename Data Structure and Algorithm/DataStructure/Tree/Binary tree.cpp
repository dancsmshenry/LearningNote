#include <iostream>

using namespace std;

//顺序存储
typedef struct BiNode
{ //二叉链表
    int data;
    struct BiNode *lchild, *rchild; //左右孩子指针
} BiNode, *BiTree;

typedef struct TriTNode
{ //三叉链表
    int data;
    struct TriTNode *lchild, *rchild, *parent;
} TriTNode, *TriTree;

//先序遍历
int PreOrderTraverse(BiTree T)
{
    if (T == NULL)
        return 1; //空二叉树
    else
    {
        cout << T;                   //访问根节点
        PreOrderTraverse(T->lchild); //递归遍历左子树
        PreOrderTraverse(T->rchild); //递归遍历右子树
    }
}

//中序遍历
int InOrderTraverse(BiTree T)
{
    if (T == NULL)
        return 1; //空二叉树
    else
    {
        InOrderTraverse(T->lchild); //递归遍历左子树
        cout << T;                  //访问根节点
        InOrderTraverse(T->rchild); //递归遍历右子树
    }
}

//中序遍历非递归
/*
int InOrderTraverse(BiTree T)
{
    BiTree p;
    InitStack(S);
    p = T;
    while (p || !StackEmpty(S))
    {
        if (p)
        {
            Push(S, p);
            p = p->lchild;
        }
        else
        {
            Pop(S, p);
            cout << q->data;
            p = q->rchild;
        }
    }
    return 1;
}
*/

//后序遍历
int PostOrderTraverse(BiTree T)
{
    if (T == NULL)
        return 1; //空二叉树
    else
    {
        PostOrderTraverse(T->lchild); //递归遍历左子树
        PostOrderTraverse(T->rchild); //递归遍历右子树
        cout << T;                    //访问根节点
    }
}


//双亲表示法
typedef struct PTNode
{
    int data;
    int parent; //双亲的位置域
} PTNode;

typedef struct
{
    PTNode nodes[10000];
    int r, n; //根节点的位置和个数
} RTree;

//孩子链表表示法
//每个点都是一个双亲结点，每个双亲都可以是孩子，但是孩子不一定是双亲（用孩子结点是为了表示双亲和孩子之间的关系）
typedef struct CTNode
{                        //孩子结点结构
    int child;           //存储该孩子结点的地址
    struct CTNode *next; //存储和这个孩子有着一样双亲的下一个孩子的地址
} * ChildPtr;

typedef struct
{                        //双亲结点结构
    int data;            //存储该双亲结点的值
    ChildPtr firstChild; //孩子链表头指针
} CTBox;

typedef struct
{
    CTBox nodes[10000]; //用一个顺序表存储所有的结点
    int n, r;           //结点数和根的位置
} CTree;

//孩子兄弟表示法
typedef struct CSNode
{
    int data;                                //数据域
    struct CSNode *firstChild, *nextsibling; //第一个孩子结点和下一个兄弟结点
} CSNode, *CSTree;

typedef struct
{
    int key;
} Elem;

typedef struct BSTNode
{
    Elem data;                       //数据域
    struct BSTNode *lchild, *rchild; //左右孩子指针
} BSTNode, *BSTree;

BSTree SearchBST(BSTree T, int key)
{ //二叉排序树的查找
    if ((!T) || key == T->data.key)
        return T;
    else if (key < T->data.key)
        return SearchBST(T->lchild, key); //在左子树中继续查找
    else
        return SearchBST(T->rchild, key); //在右子树中继续查找
}