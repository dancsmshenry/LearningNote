#include <iostream>
#include <string.h>

using namespace std;

const int MAX = 1024;
const int Success = 1;
const int Fail = 0;

typedef struct
{
    char ch[MAX + 1]; //存储串的一维数组
    int length;       //串的当前长度
} SString;

int StrAssign(SString *s, char *chars)
{
    if (!chars)
        return Fail;
    for (int i = 0; i < strlen(chars); ++i)
    {
        s->ch[i] = chars[i];
    }
    s->length = strlen(chars);
    return Success;
} //串赋值

int StrCompare(SString s1, SString s2)
{
    if (s1.length != s2.length)
        return Fail;
    else
    {
        for (int i = 0; i < s1.length; ++i)
        {
            if (s1.ch[i] != s2.ch[i])
                return Fail;
        }
        return Success;
    }
} //串比较

int StrLength(SString s)
{
    return s.length;
} //求串长

int Concat(SString s1, SString s2, SString *s)
{
    for (int i = 0; i < s1.length; ++i)
    {
        s->ch[i] = s1.ch[i];
    }
    for (int i = 0; i < s2.length; ++i)
    {
        s->ch[s1.length + i] = s2.ch[i];
    }
    s->length = s1.length + s2.length;
    return Success;
} //串连结

void SubString()
{
} //求子串，没搞懂是要干嘛

int StrCopy(SString s1, SString *s2)
{
    for (int i = 0; i < s1.length; ++i)
    {
        s2->ch[i] = s1.ch[i];
    }
    s2->length = s1.length;
    return Success;
} //串拷贝

int StrEmpty(SString s)
{
    if (s.length == 0)
        return Fail;
    else
        return Success;
} //串判空

int ClearString(SString *s)
{
    s->length = 0;
    return 1;
} //清空串

int Index(SString s, SString p)
{
    //参考kmp,bf,bm算法
    return Success;
} //寻找子串p在子串s中的位置

void Replace()
{
} //串替换,没搞懂是要干嘛

int StrInsert(SString *s, int pos, char *s1)
{
    for (int i = s->length - 1; i >= pos; i--)
    {
        s->ch[i + strlen(s1)] = s->ch[i];
    }
    for (int i = 0; i < strlen(s1); i++)
    {
        s->ch[i + pos] = s1[i];
    }
    return Success;
} //子串插入

int StrDelete(SString *s, int pos, int len)
{
    for (int i = pos + len; i < s->length; i++)
    {
        s->ch[i - len] = s->ch[i];
    }
    s->length = s->length - len;
    return Success;
} //子串删除

int DestroyString(SString *s)
{
    return 1;
} //子串销毁

//串的链式存储结构--块链结构
typedef struct Chunk //这里要加chunk的原因是定义中要调用本身这个定义
                     //
{
    char ch[MAX + 1];
    struct Chunk *next;
} Chunk;
            
typedef struct
{
    Chunk *head, *tail; //串的头指针和尾指针
    int curlen;         //串的当前长度
} LString;

int main()
{
    cout << Success << endl;
    return 0;
}