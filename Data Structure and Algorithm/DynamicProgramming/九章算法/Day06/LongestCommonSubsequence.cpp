#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * 1、确定状态（从问题的最后一步思考；将问题转换为相同的子问题来求解；动规的本质就是枚举
 * 所以求解必然是层层比较所得的）
 * 2、写出转移方程（根据子问题来写动态方程）
 * 3、注意初始条件和边界条件
 * 4、计算顺序（循环顺序）
 * 
 * 状态方程：f[i][j] = max{f[i-1][j], f[i][j - 1], f[i - 1][j - 1] + 1}
 * 
 * leetcode  1143
 **/ 

int main(){
    vector<char> a = {'A', 'B', 'C', 'D'};
    vector<char> b = {'E', 'A', 'C', 'B'};
    int m = a.size();
    int n = b.size();

    int f[2][n + 1];
    int old = 0, now = 0;
    for (int i = 0; i <= n; i ++ ){
        f[0][i] = 0;
    }

    for (int i = 1; i <= m; i ++ ){
        old = now;  
        now = 1 - now;//滚动数组一个比较好的表达方式（我之前都是用%2来表示的..）
        for (int j = 0; j <= n; j ++ ){
            f[now][j] = f[old][j];//这里相当于继承f[i - 1][j]
            if (j > 0){
                f[now][j] = max(f[now][j], f[now][j - 1]);
            }

            if (j > 0 && a[i - 1] == b[j - 1]){
                f[now][j] = max(f[now][j], f[old][j - 1] + 1);
            }
        }
    }

    cout << f[now][n];
}