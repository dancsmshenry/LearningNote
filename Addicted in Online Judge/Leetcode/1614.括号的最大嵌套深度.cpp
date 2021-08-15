class Solution {
public:
    int maxDepth(string s) {
        int ans = 0;

        for (int i = 0, left = 0; i < s.size(); i ++ )
        {
            if (s[i] == '(' )
            {
                left ++ ;
                ans = max (ans, left);
            }
            else if (s[i] == ')') left -- ;
        }

        return ans;
    }
};