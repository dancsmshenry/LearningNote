class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        int f[32];
        memset(f, 0, sizeof(f));

        for (int i = 0; i < nums.size(); i ++ ){
            int mid = nums[i];
            for (int j = 0; j < 32; j ++ ){
                if (mid % 2) f[j] ++ ;
                mid /= 2;
            }
        }

        for (long i = 0, mid = 1; i < 31; i ++ ){            
            if (f[i] % 3){
                res += mid;
            }
            mid *= 2;
        }

        return res;
    }
};