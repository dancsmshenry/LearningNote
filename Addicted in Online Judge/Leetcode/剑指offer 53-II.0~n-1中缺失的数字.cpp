class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int sum = 0, sum1 = 0;

        for (int i = 0; i < nums.size(); ++ i){
            sum += nums[i];
            sum1 += i;
            sum1 ++ ;
        }

        return sum1 - sum;
    }
};