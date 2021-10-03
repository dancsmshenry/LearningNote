#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

/**
给一个整数数组，调整每个数的大小，使得相邻的两个数的差不大于一个给定的整数target，
调整每个数的代价为调整前后的差的绝对值，求调整代价之和最小是多少。
你可以假设数组中每个整数都是正整数，且小于等于100。
 
样例1：
输入: [1,4,2,3], target=1
输出: 2
**/

int main(){
    int n = 4, target = 2;
    vector<int> a = {3,5,4,7};
    
    int f[n + 1][101];
    //第一个变量表示当前表示的是前i个数字的情况，第二个变量表示当前这个数改为这个变量所需要的代价
    for (int i = 1; i <= 100; i ++){
        f[1][i] = abs(a[0] - i);
        //数组初始化，对于第一个数字，f数组储存的值便是要改为i的代价
    }

    for (int i = 2; i <= n; i ++){
        for (int j = 1; j <= 100; j ++){
            f[i][j] = INT_MAX;
            for (int k = j - target; k <= j + target; k ++){
                if (k < 1 || k > 100){
                    continue;
                }
                f[i][j] = min(f[i][j], f[i - 1][k] + abs(a[i - 1] - j));
            }
        }
    }

    int res = INT_MAX;
    for (int j = 1; j <= 100; j ++ ){
        res = min(f[n][j], res);
    }
    cout << res << endl;

    return 0;
}