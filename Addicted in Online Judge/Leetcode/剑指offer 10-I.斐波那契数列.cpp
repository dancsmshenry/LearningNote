class Solution {
public:
    int fib(int n) {
        int a[2] = {0, 1};
        if (n < 2) return a[n];
        for (int i = 2; i <= n; ++ i){
            if (i % 2 == 0) a[i % 2] = (a[i % 2] + a[i % 2 + 1]) % 1000000007;
            else a[i % 2] = (a[i % 2] + a[i % 2 - 1]) % 1000000007;
        }

        return a[n % 2];
    }
};