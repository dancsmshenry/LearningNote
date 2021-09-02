class Solution {
public:
    vector<vector<int>> res;
    vector<int> ans;

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        solve(0, candidates, res, ans, target);
        //问题来了，怎样保证不重复？？
        //解决办法：给一个限定，在当前位置之前的数字都不能选了，这样就有效避免重复了
        return res;
    }

    void solve(int begin, vector<int>& candidates, vector<vector<int>>& res, vector<int>& ans, int target){
        if (target == 0){
            res.push_back(ans);
            return ;
        }
        for (int i = begin; i < candidates.size(); i ++ ){
            if (target < candidates[i]){
                return ;
            }else{
                ans.push_back(candidates[i]);
                solve(i, candidates, res, ans, target - candidates[i]);
                ans.pop_back();
            }
        }
    }
};