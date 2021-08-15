class Solution {
public:
    int sumOfUnique(vector<int>& nums) {
        int f[102];
        int res = 0;
        memset(f, 0, sizeof(f));
        
        for (int i = 0; i < nums.size(); i ++ ){
            f[nums[i]] ++ ;
        }
        for (int i = 0; i < 101; i ++ ){
            if (f[i] == 1) res += i;
        }

        return res;
    }
};