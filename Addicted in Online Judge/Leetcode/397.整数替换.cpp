class Solution 
{
    public:
        int integerReplacement(int n) 
        {   
            int ans = 0;
            if (n >= INT_MAX) return 32;

            while (n != 1)
            {
                if (n % 2 == 0) n = n / 2;
                else n += ((n & 2) == 0 || n == 3) ? -1 : 1;
                ans ++ ;
            }

            return ans;
        }
};