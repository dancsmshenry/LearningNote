class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> f(n + 1, vector<int>(m + 1, 0));

        for (int i = 0; i < n; i ++ )
            for (int j = 0; j < m; j ++ )
                if (matrix[i][j] == 0) f[i][j] = 1;
        
        for (int i = 0; i < n; i ++ )
            for (int j = 0; j < m; j ++ )
                if (f[i][j] == 1)
                {
                    for (int j1 = 0; j1 < m; j1 ++ ) matrix[i][j1] = 0;
                    for (int i1 = 0; i1 < n; i1 ++ ) matrix[i1][j] = 0;
                }
    }
};
