class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string word = "";
        int length = 0;
        if (strs.size() == 1) return strs[0];

        for (int i = 0; i < 200; i ++ ){
            for (int j = 1; j < strs.size(); j ++ ){
                if (i >= strs[j].size()) return word;
                if (j == strs.size() - 1 && strs[j][i] == strs[j - 1][i]){
                    word += strs[j][i];
                }
                if (strs[j][i] != strs[j - 1][i]){
                    return word;
                }
            }
        }

        return word;
    }
};