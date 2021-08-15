class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& A) {
        int p1 = 0, p2 = 1;

        while (1)
        {
            while (p1 < A.size() && A[p1] % 2 == 0) p1 += 2;
            while (p2 < A.size() && A[p2] % 2 == 1) p2 += 2;
            if (p1 >= A.size() || p2 >= A.size()) return A;
            swap(A[p1], A[p2]);
        }

        return A;
    }
};