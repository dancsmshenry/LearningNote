class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0){
            return false;
        }
        int n = matrix.size(), m = matrix[0].size() - 1;
        int i = 0, j = m;

        while (i < n && j >= 0){
            if (matrix[i][j] == target){
                return true;
            }else if (matrix[i][j] > target){
                j -- ;
            }else{
                i ++ ;
            }
        }

        return false;
    }
};