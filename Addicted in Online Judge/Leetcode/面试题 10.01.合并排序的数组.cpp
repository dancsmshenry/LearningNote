class Solution {
public:
    void merge(vector<int>& A, int m, vector<int>& B, int n) {
        if (n == 0) return;
        int a1 = m - 1, b1 = n - 1;
        int point = A.size() - 1;

        while(a1 >= 0 && b1 >= 0){
            if (A[a1] >= B[b1]){
                A[point -- ] = A[a1 -- ];
            }else{
                A[point -- ] = B[b1 -- ];
            }
        }

        while (a1 >= 0) A[point -- ] = A[a1 -- ];
        while (b1 >= 0) A[point -- ] = B[b1 -- ];
    }
};