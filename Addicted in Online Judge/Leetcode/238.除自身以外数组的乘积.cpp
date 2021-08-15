class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> f, left(n, 1), right(n, 1);

        for (int i = 1; i < n; i ++ )
        {
            left[i] = nums[i - 1] * left[i - 1];
            right[n - i - 1] = nums[n - i] * right[n - i];
        }

        for (int i = 0; i < n; i ++ ) f.push_back(left[i] * right[i]);
        
        return f;
    }
};