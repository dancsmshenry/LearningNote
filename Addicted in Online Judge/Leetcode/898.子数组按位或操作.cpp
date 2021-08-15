class Solution {
public:
    int subarrayBitwiseORs(vector<int>& A) {
        std::unordered_set<int> f;
        int n = A.size();
        if (n < 2) return n;

        for (int i = n - 1; i >= 0; i -- )
        {
            f.insert(A[i]);
            for (int j = i + 1; j < n; j ++)
            {
                if ((A[i] | A[j]) == A[j]) break;
                A[j] |= A[i];
                f.insert(A[j]); 
            }
        }

        return f.size();
    }
};