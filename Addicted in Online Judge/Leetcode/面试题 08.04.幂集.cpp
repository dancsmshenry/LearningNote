class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size(), length = 1;
        vector<vector<int>> ans;

        for (int i = 0; i < n; i ++ ){
            length *= 2;
        }

        for (int i = 0; i < length; i ++ ){
            int l1 = i, l2, l3 = 0;
            vector<int> len;
            while (l1){
                l2 = l1 % 2;
                if (l2) len.push_back(nums[l3]);
                l3 ++ ;
                l1 /= 2;
            }
            ans.push_back(len);
        }

        return ans;
    }
};