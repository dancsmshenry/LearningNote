class Solution {
public:
    vector<vector<string>> result;
    int f[20][20];
    int length;

    vector<vector<string>> partition(string s) {
        length = s.size();

        for (int j = 0; j < length; j ++ ){
            for (int i = 0; i < length - j; i ++ ){
                if (j == 0){
                    f[i][i + j] = 1;
                    continue;
                }
                if (s[i] == s[i + j]){
                    if (j == 1) f[i][i + j] = 1;
                    else if (f[i + 1][i + j - 1] == 1) f[i][i + j] = 1;
                }
                else f[i][i + j] = 0;
            }
        }

        vector<string> vec;
        search(s, vec, 0);

        return result;
    }

    void search(const string& s, vector<string> vec , int begin){
        if (begin >= length){
            result.push_back(vec);
            return ;
        }
        vector<string> vec_1(vec);
        for (int i = begin; i < length; i ++){
            if (f[begin][i]){
                vec.push_back(s.substr(begin, i - begin + 1));
                search(s, vec, i + 1);
            }
            vec = vec_1;
        }
    }
};
//看了方法二，感觉也是dfs，但是为什么效率这么低啊......