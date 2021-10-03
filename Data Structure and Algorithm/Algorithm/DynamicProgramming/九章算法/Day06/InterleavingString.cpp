#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * 一开始想的就是建一个二维数组，第一个变量存放的是总字符（目标字符）的数组下标
 * 第二个变量存放的是1、2，用来表示当前位置是选择a字符串的变量还是b字符串的变量
 * 而该二维数组的值则存放的是当前用到了第1或第2个字符串的第几位
 **/ 

int main(){
    vector<char> a = {'a','a','b','c','c'};
    vector<char> b = {'d','b','b','c','a'};
    vector<char> c = {'a','a','d','b','b','c','b','c','a','c'};

    int m = a.size();
    int n = b.size();
    if (c.size() != m + n){
        cout << false;
    }

    bool f[m + 1][n + 1];

    for (int i = 0; i <= m; i ++ ){
        for (int j = 0; j <= n; j ++ ){

            //init
            if (i == 0 && j == 0) {
                f[i][j] = true;
                continue;
            }

            //dp
            f[i][j] = false;
            if (i > 0 && c[i + j - 1] == a[i - 1]){
                f[i][j] |= f[i - 1][j];
            }
            
            if (j > 0 && c[i + j - 1] == b[j - 1]){
                f[i][j] |= f[i][j - 1];
            }
        }
    }

    cout << f[m][n];
}