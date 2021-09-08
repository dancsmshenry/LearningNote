class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 1));//vector二维数组初始化大小
        int row_max = n - 1, row_min = 0, column_max = n - 1, column_min = 0;
        int number = 1;

        //如何处理循环变量的边缘问题(只在最后才对边缘进行处理)
        while (number <= n * n){
            //对奇数进行处理
            if (number == n * n){
                res[row_max][column_max] = number;
                number ++;
            }

            for(int i = column_min; i < column_max; i ++ ,number ++ ){
                res[row_min][i] = number;
            }//向右走

            for(int i = row_min; i < row_max; i ++ ,number ++ ){
                res[i][column_max] = number;
            }//向下走

            for(int j = column_max; j > column_min; j -- ,number ++ ){
                res[row_max][j] = number;
            }//向左走

            for(int j = row_max; j > row_min; j -- ,number ++ ){
                res[j][column_min] = number;
            }//向上走

            //对边缘进行处理
            row_min ++ ;
            row_max -- ;
            column_min ++ ;
            column_max -- ;
        }

        return res;
    }
};