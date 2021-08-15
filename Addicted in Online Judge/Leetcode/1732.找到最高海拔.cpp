class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int maxn = 0, ans = 0;
        
        for (int i = 0; i < gain.size(); i ++ ){
            ans += gain[i];
            maxn = max(maxn, ans);
        }

        return maxn;
    }
};