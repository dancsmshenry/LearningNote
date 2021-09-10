class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        /**
        感觉只要是遇到矩阵区域的问题，都是可以用前缀和来解决
        而前缀和我又总是和动态规划联系起来..(不过这道题起始也很符合动态规划的思想，每一步都是由前面的一步来决定的)

        先初始化f[i][j]数组：f[i][j] = f[i][j - 1] + f[i - 1][j] - f[i - 1][j - 1]

        判断式子f[i][j] - f[i][j - t] - f[i - t][j] + f[i - t][j - t](t为当前矩阵的长度)
        如果s[i][j] <= threshold ,那就用t来更新maxn
        否则就停止退出当前的循环

        出bug了，原因是，没有考虑到矩阵的范围能够取到最左边的情况（如我想取到(2,2)的这个矩阵，但是我的这个算法因为为了不过界就没有考虑到这个方面）
        想到的解决办法：对f数组进行改造，即空出坐标为0的那一行和那一列，然后全部设为0，然后再调整t的范围
        这样就可以找到一个普适的方法来判断了

        结论：以后，遇到要计算这种前缀和类似动规的，就先预留一行一列不写任何东西，即设为0
        **/
        int maxn = 0;
        int m = mat.size(), n = mat[0].size();
        int f[m + 2][n + 2];

        //数组init
        for (int i = 0; i <= m; i ++ ){
            for (int j = 0; j <= n; j ++ ){
                if (!i || !j){
                    f[i][j] = 0;
                }else{
                    f[i][j] = f[i][j - 1] + f[i - 1][j] - f[i - 1][j - 1] + mat[i - 1][j - 1];
                }
            }
        }
        
        //判断是否符合条件来更新maxn
        for (int i = 1; i <= m; i ++ ){
            for (int j = 1; j <= n; j ++ ){
                for (int t = 1; t <= min(i, j); t ++ ){
                    if ((f[i][j] - f[i][j - t] - f[i - t][j] + f[i - t][j - t]) <= threshold){
                        maxn = max(maxn, t);
                    }else{
                        break;
                    }
                }
            }
        }

        return maxn;
    }
};