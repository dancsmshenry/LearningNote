class Solution {
public:
    int countVowelStrings(int n) {
        int f[1000];
        f[1] = 5;
        f[2] = 15;

        for (int i = 3; i <= n; i ++ )
            f[i] = 2 * f[i - 1] - f[i - 2] + (i + 1) * (i + 2) / 2;

        return f[n];
    }
};