class Solution {
public:
    vector<int> addToArrayForm(vector<int>& A, int K) {
        vector<int> res;
        int k2 = 0;
        
        for (int i = A.size() - 1; i >= 0; i -- ){
            int k1 = K % 10;
            K /= 10;
            res.insert(res.begin(), (A[i] + k1 + k2) % 10);
            k2 = (A[i] + k1 + k2) / 10;
        }
        K += k2;

        while (K){
            int k1 = K % 10;
            K /= 10;
            res.insert(res.begin(), k1);
        }

        return res;
    }
};