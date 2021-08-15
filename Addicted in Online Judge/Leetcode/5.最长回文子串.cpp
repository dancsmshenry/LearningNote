class Solution {
public:
    string longestPalindrome(string s) {
        string ans;
        vector<vector<int>> dp(s.size(), vector<int>(s.size()));

        for (int l = 0; l < s.size(); l ++ ) 
        {
            for (int i = 0; i + l < s.size(); i ++ ) 
            {
                if (l == 0) dp[i][i + l] = 1;
                else if (l == 1) dp[i][i + l] = (s[i] == s[i + l]);
                else dp[i][i + l] = (s[i] == s[i + l] && dp[i + 1][i + l - 1]);
                if (dp[i][i + l] && l + 1 > ans.size()) ans = s.substr(i, l + 1);
            }
        }

        return ans;
    }
};