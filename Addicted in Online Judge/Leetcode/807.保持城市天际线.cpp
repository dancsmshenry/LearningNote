class Solution {
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), sum = 0;//n表示有多少行，m表示有多少列
        int line[100000], row[100000];

        for (int i = 0; i < n || i < m; i ++ ){
            line[i] = 0;
            row[i] = 0;
        }

        for (int i = 0; i < n; i ++ ){
            for (int j = 0; j < m; j ++ ){
                line[i] = max(line[i], grid[i][j]);
                row[j] = max(row[j], grid[i][j]);
            }
        }

        for (int i = 0; i < n; i ++ ){
            for (int j = 0; j < m; j ++ ){
                sum += min(line[i], row[j]) - grid[i][j];
            }
        }

        return sum;
    }
};