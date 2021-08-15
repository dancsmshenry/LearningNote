class Solution {
public:
    bool isSubsequence(string s, string t) {
        int record = 0;
        if (s.size() == 0) return true;
        else if (t.size() == 0) return false;

        for (int i = 0; i < s.size(); i ++ )
        {
            for (int j = record; j < t.size(); j ++ )
            {
                if (s[i] == t[j])
                {
                    record = j + 1;
                    break;
                }
                if (j == t.size() - 1) return false;
            }
            if (record == t.size() && i < s.size() - 1) return false;
        }

        return true;
    }
};