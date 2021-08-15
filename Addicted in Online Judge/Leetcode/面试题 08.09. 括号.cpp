class Solution {
public:
    vector<string> res;
    int number;

    vector<string> generateParenthesis(int n) {
        number = n;
        solve(1, 0, "(");

        return res;
    }

    void solve(int left, int right, string exemple){
        if (right > left) return;
        if (left == right && left == number){
            res.push_back(exemple);
            return ;
        }
         if (left >= right && left < number){
             solve(left + 1, right, exemple + "(");
             solve(left, right + 1, exemple + ")");
         }else{
             solve(left, right + 1, exemple + ")");
         }
    }
};