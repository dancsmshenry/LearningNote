class Solution {
public:
    vector<int> printNumbers(int n) {
        vector<int> f;
        int m = 1;

        for (int i = 0; i < n; i ++) m *= 10;

        for (int i = 1; i < m; i ++) f.push_back(i);

        return f;
    }
};