class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int mid_01 = 0, mid_02 = 1;
        int a = 0, b = 0;

        for (int i = 0; i < nums.size(); i ++ ){
            mid_01 ^= nums[i];
        }

        while ((mid_02 & mid_01) == 0){
            mid_02 <<= 1;
        }
        
        for (int i = 0; i < nums.size(); i ++ ){
            if (nums[i] & mid_02){
                a ^= nums[i];
            }else{
                b ^= nums[i];
            }
        }

        return vector{a, b};
    }
};