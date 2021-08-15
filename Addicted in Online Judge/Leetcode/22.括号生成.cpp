class Solution {
public:
    vector<string> res;

    void check(int n, int left, int right, string str){
        if (left < n) check(n, left + 1, right, str + "(");
        if (right < left) check(n, left, right + 1, str + ")");
        if (right == n) res.push_back(str);
    }

    vector<string> generateParenthesis(int n) {
        check(n, 0, 0, "");
        return res;
    }
};