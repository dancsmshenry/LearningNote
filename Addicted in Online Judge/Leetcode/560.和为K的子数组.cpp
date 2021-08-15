/*
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int number[nums.size() + 1];
        int total = 0;

        number[0] = nums[0];
        for (int i = 1; i < nums.size(); i ++ ){
            number[i] = nums[i] + number[i - 1];
        }

        for (int i = 0; i < nums.size(); i ++ ){
            if (number[i] == k) total ++ ;
            for (int j = 0; j < i; j ++ ){
                if (number[i] - number[j] == k) total ++ ;
            }
        }

        return total;
    }
};
*/
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        mp[0] = 1;
        int total = 0;

        for (int i = 0, pre = 0; i < nums.size(); i ++ ) {
            pre += nums[i];
            if (mp.find(pre - k) != mp.end()) {
                total += mp[pre - k];
            }
            mp[pre]++;
        }

        return total;
    }
};