class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> res;
        if (target == 1 || target == 2){
            return res;
        }

        for (int i = 2; i < target / 2; i ++ ){
            int sum = (1 + i) * i / 2;//爆仓了
            if (target >= sum && (target - sum) % i == 0){
                vector<int> ans;
                for (int j = 1, t = (target - sum) / i; j <= i; j ++ ){
                    ans.push_back(j + t);
                }
                res.push_back(ans);
            }else if (sum > target){
                break;
            }
        }

        sort(res.begin(), res.end());//序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。
        return res;
    }
};