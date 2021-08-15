class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) return 0;

        int maxn = 0, min = prices[0];

        for (int i = 1; i < prices.size(); ++ i){
            min = min < prices[i] ? min : prices[i];
            maxn = max(maxn, prices[i] - min);
        }

        return maxn;
    }
};