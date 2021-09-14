class Solution {
public:
    vector<vector<int>> res;

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        /*
        这道题和面试题 08.08. 有重复字符串的排列组合的思路一模一样
        但是这里用传指针优化了一下，速度上快了不少
        */

        vector<int> ans(22, 0);

        for (int i = 0; i < nums.size(); i ++ ){
            ans[nums[i] + 10] ++ ;
        }
        
        vector<int> nullvector;
        solve(ans, nullvector);
        return res;
    }

    void solve(vector<int>& ans, vector<int>& res1){
        bool flag = true;
        for (int i = 0; i < ans.size(); i ++ ){
            if (ans[i] > 0){
                res1.push_back(i - 10);
                ans[i] -- ;
                solve(ans, res1);
                ans[i] ++ ;
                res1.pop_back();
                flag = false;
            }
        }
        if (flag){
            res.push_back(res1);
        }
    }
};