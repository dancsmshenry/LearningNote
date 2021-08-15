class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int len1 = mat.size(), len2 = mat[0].size();//len1是行数,len2是列数
        //错误的原因，循环的变量条件设置错误，导致vector越界....大无语事件

        for (int i = 0; i < len2; i ++ ){//先在第一行中从左到右遍历
            vector<int> mid;

            for (int j = 0; j < len1 && j + i < len2; j ++ ){
                mid.push_back(mat[j][j + i]);
            }
            sort(mid.begin(), mid.end());

            for (int l1 = 0, l2 = 0;l1 < len1 && l1 + i < len2; l1 ++ , l2 ++ ){
                mat[l1][l1 + i] = mid[l2];
            }
        }

        for (int i = 1; i < len1; i ++ ){//再在第一列中从上到下遍历
            vector<int> mid;

            for (int j = 0; j + i < len1 && j < len2; j ++ ){
                mid.push_back(mat[j + i][j]);
            }
            sort(mid.begin(), mid.end());

            for (int l1 = 0, l2 = 0; l1 + i < len1 && l1 < len2; l1 ++ , l2 ++ ){
                mat[l1 + i][l1] = mid[l2];
            }
        }
        

        return mat;
    }
};