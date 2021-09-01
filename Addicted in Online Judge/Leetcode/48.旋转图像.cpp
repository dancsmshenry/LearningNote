#include <algorithm>

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        /**
            思路：
            将矩阵分为一层一层的，所以每一次旋转都是对该层进行处理
            对于每一层的处理：
            对于每一行，从左到右，对四条边的相对应位置的数字就进行swap
        **/
        int n = matrix.size();
        for (int j = 0; j < (n / 2); j ++ ){
            int min = j, max = n - j - 1;
            for (int i = 0; i < max - min; i ++ ){
                swap(matrix[min][min + i], matrix[min + i][max]);
                swap(matrix[min][min + i], matrix[max][max - i]);
                swap(matrix[min][min + i], matrix[max - i][min]);
            }
        }
        return ;
    }
};