#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//这道题有点没读懂题目的意思，先把代码抄下来，以后再看

int main(){
    vector<char> a = {'a', 'a', 'b'};
    vector<char> b = {'c', '*', 'a', '*', 'b'};
    // vector<char> b = {'a', 'a', 'a'};

    int m = a.size();
    int n = b.size();

    bool f[m + 1][n + 1];
    for (int i = 0; i <= m; ++ i ){
        f[i][0] = (i == 0);
        for (int j = 1; j <= n; ++ j){
            f[i][j] = false;
            if (b[j - 1] != '*'){
                if (i > 0 && (b[j - 1] == '.' || b[j - 1] == a[i - 1])){
                    f[i][j] |= f[i - 1][j - 1];
                }
            }else{
                if (j >= 2) f[i][j] |= f[i][j - 2];
                if (i > 0 && j >= 2 && (b[j - 2] == '.' || b[j - 2] == a[i - 1])){
                    f[i][j] |= f[i - 1][j];
                }
            }
        }
    }

    cout << f[m][n];
}