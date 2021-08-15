class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int ret = 0;

        for (int n : nums) ret ^= n;
        int div = ret & (-ret);

        int a = 0, b = 0;
        for (int n : nums)
            if (div & n) a ^= n;
            else b ^= n;
        
        return vector<int>{a, b};
    }
};