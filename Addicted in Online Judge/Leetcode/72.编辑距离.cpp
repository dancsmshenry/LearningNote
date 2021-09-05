class Solution {
public:
    int minDistance(string word1, string word2) {
        int old = 0, now = 0;
        int m = word1.size(), n = word2.size();
        int f[2][n + 1];//这里用的是滚动数组

        //循环的边界都要是=，因为同时要计算0的情况
        for (int i = 0; i <= m; i ++ ){
            /**
            滚动数组的精华：
            之前的now变为现在的old
            现在的now变为1 - old(精华)
            **/
            old = now;
            now = 1 - old;

            for (int j = 0; j <= n; j ++ ){
                if (!i){//如果i为0的时候，即当原字符串的长度为0的时候，要修改的次数就是目标字符串的长度（就全部都插入）
                    f[now][j] = j;
                    continue;
                }

                if (!j){//如果j为0的时候，即目标字符串的长度为0的时候，要修改的次数就是原字符串的长度（就全部都删除）
                    f[now][j] = i;
                    continue;
                }
                
                /**
                状态转移方程：f[i][j] = min{f[i][j - 1] + 1, f[i - 1][j - 1] + 1, f[i - 1][j] + 1, f[i - 1][j - 1]|a[i - 1] = b[j - 1]}
                f[i][j - 1] + 1：插入一个字母，即当前i个可以变为前j-1个的时候，再插入一个字母就可以变为前j个
                f[i - 1][j - 1] + 1：替换一个字母，即前i-1个可以变为前j-1个的时候，将word1[i]变为word2[j]
                f[i - 1][j] + 1：删除一个字母，即前i-1个可以变为前j个的时候，就删掉word1[i]
                f[i - 1][j - 1]：什么都不做（这里的前提是word1[i - 1] == b[j - 1]）
                **/
                f[now][j] = min(f[old][j] + 1,f[now][j - 1] + 1);

                f[now][j] = min(f[now][j], f[old][j - 1] + 1);

                if (word1[i - 1] == word2[j - 1]){
                    f[now][j] = min(f[now][j], f[old][j - 1]);
                }
            }
        }

        return f[now][n];
    }
};