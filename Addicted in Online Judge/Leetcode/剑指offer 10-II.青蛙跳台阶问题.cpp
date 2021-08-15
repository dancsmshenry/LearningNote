class Solution {
public:
    int numWays(int n) {
        int a0 = 1, a1 = 1;
        if (n < 2) return 1;

        for(int i = 2;i <= n; ++ i){
            if(i % 2 == 0){
                a0 = a1 + a0;
                a0 = a0 % (1000000007);
            }
            else {
                a1 = a1 + a0;
                a1 = a1 % (1000000007);
            }
        }

        return (n % 2 == 1) ? a1 : a0; 
    }
};