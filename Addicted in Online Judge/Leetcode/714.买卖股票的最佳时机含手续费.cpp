class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int maxn = 0, n = prices.size();
        int f[n][3];
        f[0][0] = 0;
        f[0][1] = - prices[0];

        for (int i = 1; i < n; ++ i){
            f[i][0] = max(f[i - 1][0], f[i - 1][1] + prices[i] - fee);
            f[i][1] = max(f[i - 1][0] - prices[i], f[i - 1][1]);
            maxn = max(f[i][0], maxn);
        }

        return maxn;
    }
};