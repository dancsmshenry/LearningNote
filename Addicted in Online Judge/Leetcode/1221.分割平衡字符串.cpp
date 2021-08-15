class Solution {
public:
    int balancedStringSplit(string s) {
        int ans = 0, r = 0;

        for (int i = 0; i < s.size(); i ++ )
        {
            if (s[i] == 'R') r ++ ;
            else r -- ;
            if (r == 0) ans ++ ;
        }

        return ans;
    }
};