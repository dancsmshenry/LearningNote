#include <iostream>
#include <vector>

using namespace std;

/**
给定 n 个不同的正整数，整数 k(k≤n)以及一个目标数字 target。 
在这 n 个数里面找出 k 个数，使得这 k 个数的和等于目标数字，求问有多少种方案？

样例一：
输入：A = [1,2,3,4]
k = 2
target = 5

输出：2
**/

int main(){
    vector<int> a = {1, 2, 3, 4};
    int k = 2, target = 5;
    int n = a.size();
    int f[n + 1][k + 1][target + 1];

    //init
    for (int i = 0; i <= k; i ++ ){
        for (int j = 0; j <= target; j ++ ){
            f[0][i][j] = 0;
        }
    }

    f[0][0][0] = 1;

    //dp
    for (int i = 1; i <= n; i ++ ){
        for (int j = 0; j <= k; j ++ ){
            for (int l = 0; l <= target; l ++ ){
                //do not select a[i - 1]
                f[i][j][l] = f[i - 1][j][l];

                //select a[i - 1]
                if (j > 0 && l >= a[i - 1]){
                    f[i][j][l] += f[i - 1][j - 1][l - a[i - 1]];
                }
            }
        }
    }

    cout << f[n][k][target];
}