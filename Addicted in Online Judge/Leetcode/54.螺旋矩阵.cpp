class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int row_min = 0, line_min = 0;
        int row_max = matrix.size() - 1, line_max = matrix[0].size() - 1;
        int total = matrix.size() * matrix[0].size();
        vector<int> res;

        while(total >= 1){
            for(int i = line_min; i <= line_max && total >= 1; i ++ ){
                res.push_back(matrix[row_min][i]);
                total -- ;
            }
            row_min ++ ;//行最小，向右走
            
            for(int i = row_min; i <= row_max && total >= 1; i ++ ){
                res.push_back(matrix[i][line_max]);
                total -- ;
            }
            line_max -- ;//列最大，向下走
                
            for(int i = line_max; i >= line_min && total >= 1; i -- ){
                res.push_back(matrix[row_max][i]);
                total -- ;
            }
            row_max -- ;//行最大，向左走

            for(int i = row_max; i >= row_min && total >= 1; i -- ){
                res.push_back(matrix[i][line_min]);
                total -- ;
            }
            line_min ++ ;//列最小，向上走
        }

        return res;//bug，for循环里面要用&&不能用，
    }
};