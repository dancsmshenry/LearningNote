class Solution {
public:
    int minInsertions(string s) {
        /*
        这道题和编辑距离非常的相似，基本是一模一样的
        题解后期review的时候再详细写吧
        */
        int n = s.size();
        int f[n + 1][n + 1];

        for (int i = 0; i < s.size(); i ++ ){
            for (int j = 0; j < s.size() - i; j ++ ){
                if (s[j] == s[j + i] && i < 2){
                    f[j][j + i] = 0;
                    continue;
                }
                if (s[j] == s[j + i]){//如果两个边界相等，且距离大于等于2的话，就将初值设为f[j + 1][j + i - 1]
                    f[j][j + i] = f[j + 1][j + i - 1];
                }else{//如果相等，就可以先把初值设为max值
                    f[j][j + i] = INT_MAX;
                }
                f[j][j + i] = min(f[j][j + i], f[j + 1][j + i] + 1);//接下来就是比较大小，分别和两个边界比较
                f[j][j + i] = min(f[j][j + i], f[j][j + i - 1] + 1);
            }
        }

        return f[0][s.size() - 1];
    }
};