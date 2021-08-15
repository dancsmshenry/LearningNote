class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int f[text1.size() + 1][text2.size() + 1];

        for (int i = 0; i <= text1.size(); i ++ ){
            for (int j = 0; j <= text2.size(); j ++ ){
                if (!i || !j){
                    f[i][j] = 0;
                    continue;
                }
                f[i][j] = max(f[i][j - 1], f[i - 1][j]);
                if (text1[i - 1] == text2[j - 1]){
                    f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
                }
            }
        }

        return f[text1.size()][text2.size()];
    }
};