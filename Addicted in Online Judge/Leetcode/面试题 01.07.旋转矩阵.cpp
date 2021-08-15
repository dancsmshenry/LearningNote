class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix[0].size();

        for (int min = 0, max = n - 1; min < max; min ++ , max -- )
        {
            for (int j = 0; j < max - min; j ++ )
            {
                swap(matrix[min][min + j], matrix[max - j][min]);
                swap(matrix[max - j][min], matrix[max][max - j]);
                swap(matrix[max][max - j], matrix[min + j][max]);
            }
        }
    }
};