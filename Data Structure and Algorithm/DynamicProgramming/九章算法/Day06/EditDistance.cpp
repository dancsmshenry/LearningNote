#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * 写了这么久的代码，发现自己有几个地方是始终没有做好的
 * 第一个是对问题的抽象能力，很多时候都知道应该这么做，但是到后面却无法将问题抽象为一个具体的方程
 * 第二个就是代码能力，就无法将问题所求出的方程转化为一段非常不错而优美的代码
 * 
 * 转移方程：
 * f[i][j] = min{f[i][j - 1] + 1, f[i - 1][j - 1] + 1, f[i - 1][j] + 1, f[i - 1][j - 1]|a[i - 1] = b[j - 1]}
 * 插入一个字母，替换一个字母，删掉一个字母，什么都不做（前提是相等）
 * 
 * dp：
 * 数组数据初始化
 * 设置循环范围
 *  在循环中迭代状态转移方程
 * 输出结果
 * 
 * leetcode 72 编辑距离
 **/ 

int main(){
    vector<char> a = {'m','a','r','t'};
    vector<char> b = {'k','a','r','m','a'};

    int m = a.size();
    int n = b.size();
    // int f[m + 1][n + 1];

    // //init
    // for (int j = 0; j <= n; j ++ ){
    //     //当原来的字母数为0的时候，要改为任意大小样式的字符串代价都是该字符串的长度
    //     f[0][j] = j;
    // }

    // //dp
    // for (int i = 1; i <= m; i ++ ){
    //     //和上面的一样，同理
    //     f[i][0] = i;
    //     for (int j = 1; j <= n; j ++ ){
    //         //开始迭代状态方程
    //         f[i][j] = min(f[i - 1][j] + 1, f[i - 1][j - 1] + 1);
    //         f[i][j] = min(f[i][j], f[i][j - 1] + 1);
    //         if (a[i - 1] == b[j - 1]){
    //             f[i][j] = min(f[i][j], f[i - 1][j - 1]);
    //         }
    //     }
    // }
    
    // //cout result
    // cout << f[m][n];

    //下面用滚动数组进行优化
    int f[2][n + 1];
    int old  = 0, now = 0;

    for (int i = 0; i <= m; i ++ ){//注意到这里的i是从0开始的
        old = now;
        now = 1 - old;
        for (int j = 0; j <= n; j ++ ){
            if (i == 0){
                f[now][j] = j;
                continue;
            }

            if (j == 0){
                f[now][j] = i;
                continue;
            }

            f[now][j] = min(f[old][j] + 1,f[now][j - 1] + 1);

            f[now][j] = min(f[now][j], f[old][j - 1] + 1);

            if (a[i - 1] == b[j - 1]){
                f[now][j] = min(f[now][j], f[old][j - 1]);
            }
        }
    }

    cout << f[now][n];
}