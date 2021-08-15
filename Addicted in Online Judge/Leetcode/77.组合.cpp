class Solution {
public:
    int k1, n1;
    vector<vector<int>> res;

    vector<vector<int>> combine(int n, int k) {
        k1 = k;
        n1 = n;
        bool flag[n + 1];
        memset(flag, false ,sizeof(flag));
        vector<int> v;
        solve(1, flag, v);

        return res;
    }

    void solve(int begin, bool flag[], vector<int> v){
            if (v.size() == k1){
                res.push_back(v);
                return ;
            }
            for (int i = begin; i <= n1; i ++ ){
                if (flag[i] == false){
                vector<int> v1(v);
                v1.push_back(i);
                flag[i] = true;
                solve(i + 1, flag, v1);
                flag[i] = false;
            }
        }
    }
};