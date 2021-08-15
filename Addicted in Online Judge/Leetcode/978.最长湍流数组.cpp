class Solution {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        int maxn = 1, n = arr.size();
        int f[n][3];
        f[0][0] = f[0][1] = 1;

        for (int i = 1; i < n; ++ i){
            if (arr[i - 1] < arr[i]){
                f[i][0] = f[i - 1][1] + 1;
                f[i][1] = 1;
            }
            else if (arr[i - 1] > arr[i]){
                f[i][1] = f[i - 1][0] + 1;
                f[i][0] = 1;
            }
            else{
                f[i][1] = f[i][0] = 1;
            }
            
            int max1 = max(f[i][0], f[i][1]);
            maxn = max(maxn, max1);
        }

        return maxn;
    }
};