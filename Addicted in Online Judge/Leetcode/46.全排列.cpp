class Solution {
public:
    vector<vector<int>> res;
    int n;

    vector<vector<int>> permute(vector<int>& nums) {
        n = nums.size();
        bool flag[n];
        vector<int> v;
        memset(flag, false ,sizeof(flag));
        solve(nums, flag, v);
        return res;
    }

        void solve(vector<int>& nums, bool flag[], vector<int> v){
            if (v.size() == n){
                res.push_back(v);
                return ;
            }
            for (int i = 0; i < n; i ++ ){
                if (flag[i] == false){
                vector<int> v1(v);
                v1.push_back(nums[i]);
                flag[i] = true;
                solve(nums, flag, v1);
                flag[i] = false;
            }
        }
    }
};