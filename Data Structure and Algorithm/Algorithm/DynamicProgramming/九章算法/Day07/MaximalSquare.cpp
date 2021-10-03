#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * leetcode221:
 * 在一个由 '0' 和 '1' 组成的二维矩阵内，找到只包含 '1' 的最大正方形，并返回其面积。
 * https://leetcode-cn.com/problems/maximal-square/
 **/ 

/**
 * 这道题我最开始的思路是先看i,j的地方有没有1，如果没有的话就直接跳过
 * 如果有的话，就先看i-1,j-1的地方有没有1，如果没有就直接跳过
 * 如果有，那就对i,j的位置的横向和纵向都进行搜索，搜索的范围因该是以i-1,j-1为右下角的一个正方形
 * 但是这里的话，就出现说新建的二维数组要记录以当前右下角的正方形为顶点的正方形的边长
 * 其实细想也是可以的，不过每一次都要从行列去搜索有没有1，倒也是挺麻烦的
 * 
 * 所以本题提供了一个比较好的思路，就是在i-1,j;i,j-1;i-1.j-1这三个地方去找是不是不为0
 * ps：这里的新建的数组也是和我之前所想的一样，来储存边长的
 * 接上文：然后找这几个当中最小的那一个
 **/ 

int main(){
    vector<vector<int>> a = {{1,0,1,0,0}, {1,0,1,1,1}, {1,1,1,1,1}, {1,0,0,1,0}};

    if (a.size() == 0 || a[0].size() == 0){
        cout << 0;
    }

    int m = a.size();   
    int n = a[0].size();

    int f[m][n];
    int res = 0;
    for (int i = 0; i < m; i ++ ){
        for (int j = 0; j < n; j ++ ){
            if (a[i][j] == 0){
                f[i][j] = 0;
                continue;
            }

            if (i == 0 || j == 0){
                f[i][j] = 1;
                res = max(1, res);
                continue;
            }

            int min1 = min(f[i - 1][j], f[i - 1][j - 1]);
            int min2 = min(min1, f[i][j - 1]) + 1;
            f[i][j] = min2;
            res = max(f[i][j] * f[i][j], res);
        }
    }

    cout << res << endl;

    return 0;
}