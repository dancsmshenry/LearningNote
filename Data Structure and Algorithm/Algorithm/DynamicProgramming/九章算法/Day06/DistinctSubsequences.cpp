#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    vector<char> a = {'r', 'a', 'b', 'b', 'b', 'i', 't'};
    vector<char> b = {'r', 'a', 'b', 'b', 'i', 't'};
    //问题：看b在a中出现了多少次
    int m = a.size();
    int n = b.size();

    int f[m + 1][n + 1];
    f[0][0] = 1;//都是空的话就相当于出现了1次
    for (int j = 1; j <= n; j ++ ){
        f[0][j] = 0;//如果a是空串，那b只要长度大于1，就出现了0次
    }

    for (int i = 1; i <= m; i ++ ){
        f[i][0] = 1;//如果b是空串，那在a中就出现了1次
        for (int j = 1; j <= n; j ++ ){
            f[i][j] = f[i - 1][j];//先记录前i-1中和前j个匹配的个数
            if (a[i - 1] == b[j - 1]){
                f[i][j] += f[i - 1][j - 1];
            }
        }
    }

    cout << f[m][n];
}