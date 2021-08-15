class Solution 
{
    public:
        int singleNumber(vector<int>& nums) 
        {
            int result = 0;
            
            for (int i = 0; i < 32; i ++ )
            {
                long number = 0;
                for (int j = 0; j < nums.size(); j ++ ) number += (nums[j] >> i) & 1;
                result += (number % 3) << i;
            }

            return result;
        }
};