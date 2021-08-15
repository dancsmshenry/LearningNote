#include <stdio.h>
int main()
{
	int uniquePaths(int m, int n)
{
   int i, j;
   int dp[1000][1000];
   
   for(j = 0; j < n; j++)
   {
       for (i = 0; i < m; i++)  
            {
                if (i == 0 && j == 0) dp[i][j] = 1;
                else if (j == 0) dp[i][j] = dp[i- 1][j];
                else if (i == 0) dp[i][j] = dp[i][j - 1];
                else dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
            }
   }

   return dp[m - 1][n - 1];
}
 } 
