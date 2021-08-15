class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int total = 0, n = matrix.size(), m = matrix[0].size();

        for (int i = 0; i < n; i ++ )
        {
            for (int j = 0; j < m; j ++ )
            {
               if (i && j && matrix[i][j])
                    matrix[i][j] += min({matrix[i - 1][j  -1], matrix[i][j - 1], matrix[i - 1][j]});
               total += matrix[i][j];
            }
        }

        return total;
    }
};