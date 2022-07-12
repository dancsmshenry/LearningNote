- 最基本的二维数组解法

- ```cpp
  class Solution {
  public:
      int longestCommonSubsequence(string text1, string text2) {
          int n = text1.size(), m = text2.size();
          vector<vector<int>> dp(n + 1, vector<int> (m + 1, 0));
  
          for (int i = 1; i <= n; ++ i) {
              for (int j = 1; j <= m; ++ j) {
                  dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                  if (text1[i - 1] == text2[j - 1]) {
                      dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
                  }
              }
          }
  
          return dp.back().back();
      }
  };
  ```



- 滚动数组优化二维数组

- ```cpp
  class Solution {
  public:
      int longestCommonSubsequence(string text1, string text2) {
          int n = text1.length(), m = text2.length();
          vector<vector<int>> dp(2, vector<int> (m + 1, 0));
  
          for (int i = 1, now = 0, old = 0; i <= n; ++ i) {
              now = i % 2;
              old = 1 - now;
              for (int j = 1; j <= m; ++ j) {
                  dp[now][j] = max(dp[old][j], dp[now][j - 1]);
                  if (text1[i - 1] == text2[j - 1]) {
                      dp[now][j] = max(dp[now][j], dp[old][j - 1] + 1);
                  }
              }
          }
  
          return dp[n % 2][m];
      }
  };
  ```



- 滚动数组优化至一维数组

- ```cpp
  class Solution {
  public:
      int longestCommonSubsequence(string text1, string text2) {
          int n = text1.size(), m = text2.size();
          vector<int> dp(m + 1, 0);
  
          for (int i = 1; i <= n; ++ i) {
              int pre = 0;
              for (int j = 1; j <= m; ++ j) {
                  int temp = dp[j];
                  dp[j] = max(dp[j], dp[j - 1]);
                  if (text1[i - 1] == text2[j - 1]) {
                      dp[j] = max(pre + 1, dp[j]);
                  }
                  pre = temp;
              }
          }
  
          return dp[m];
      }
  };
  ```