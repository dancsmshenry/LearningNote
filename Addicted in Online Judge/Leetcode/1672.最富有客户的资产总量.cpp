class Solution {
public:
    int maximumWealth(vector<vector<int>>& accounts) {
        int maxn = 0;
        
        for (int i = 0; i < accounts.size(); i ++ ){
            int total = 0;
            for (int j = 0; j < accounts[0].size(); j ++ ){
                total += accounts[i][j];
            }
            maxn = max(maxn, total);
        }

        return maxn;
    }
};