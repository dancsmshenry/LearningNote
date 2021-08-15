class Solution {
public:
    string reverseLeftWords(string s, int n) {
        string t = "";

        for (int i = n; i < s.size(); i ++ ) t += s[i];
        for (int i = 0, j = s.size() - n; j < s.size(); i ++, j ++ ) t += s[i];

        return t;
    }
};