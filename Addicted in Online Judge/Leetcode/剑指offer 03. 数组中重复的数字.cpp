class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        int a[100001];
        memset(a, 0, sizeof(a));
        int res = 0;

        for (int i = 0; i < nums.size(); i ++ ){
            a[nums[i]] ++ ;
            if (a[nums[i]] > 1){
                res = nums[i];
                break;
            }
        }

        return res;
    }
};