class Solution 
{
    public:
        int majorityElement(vector<int>& nums) 
        {
            int result = 0;
            
            for (long i = 0, two = 1; i < 32; i ++ )
            {
                int number = 0;
                for (int j = 0; j < nums.size(); j ++ ) number += (nums[j] >> i) & 1;
                if (number > nums.size() / 2) result += two;
                two *= 2;
            }

            return result;
        }
};