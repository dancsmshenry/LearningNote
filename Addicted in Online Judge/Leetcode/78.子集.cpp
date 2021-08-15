class Solution {
public:
    vector<int> t;
    vector<vector<int>> ans;

    vector<vector<int>> subsets(vector<int>& nums) 
    {      
        for (int i = 0, ans = 1; i < nums.size(); i ++ ) ans *= 2;

        for (int i = 0; i < (1 << nums.size()); i ++ )
        {
            int number = i;
            t.clear();
            for (int j = 0; j < nums.size(); j ++ )
            {
                if (number % 2 == 1) t.push_back(nums[j]);
                number /= 2;     
            }
            ans.push_back(t);
        }

        return ans;
    }
};