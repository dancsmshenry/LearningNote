class Solution {
public:
    int solve(vector<int> number){
        int first = number[0], second = max(number[0], number[1]);
        for (int i = 2; i < number.size(); i++) {
            int temp = second;
            second = max(first + number[i], second);
            first = temp;
        }
        return second;
    }

    int deleteAndEarn(vector<int>& nums) {
        int maxn = 0;

        for (int i = 0; i < nums.size(); i ++ ){
            maxn = max(nums[i], maxn);
        }

        vector<int> number(maxn + 1, 0);
        for (int i = 0; i < nums.size(); i ++ ){
            number[nums[i]] += nums[i];
        }

        return solve(number);
    }
};