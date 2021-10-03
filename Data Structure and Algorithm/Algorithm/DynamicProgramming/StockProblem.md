## 买卖股票的最佳时机

- 题目：给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。

  你只能选择某一天买入这只股票，并选择在未来的某一个不同的日子卖出该股票。设计一个算法来计算你所能获取的最大利润。

  返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 

- 思路：因为已知所有天数的股票价格，所以只要记录枚举当前天数之前的最小股票价格与当天股票价格的差价，每次记录后并比较取最大值即可

- ```c++
  int maxProfit(int* prices, int pricesSize)
  {
      int i, min, sum = 0;
      min = INT_MAX;
  
      for (i = 0; i < pricesSize; i++)
      {
          min = min < prices[i] ? min : prices[i];
          sum = sum > prices[i] - min ? sum : prices[i] - min;
      }
      return sum;
  }
  ```





## 买卖股票的最佳时机II

- 题目：给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

  设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。

  注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

- 思路：与前面不同的是这次可以多次的购入与卖出，所以只要当天的股票比昨天的股票价格高，就立即卖出（有点类似贪心思想）

- ```c++
  int maxProfit(int* prices, int pricesSize)
  {
      int i, sum = 0;
      
      for (i = 1; i < pricesSize; i++)
          if (prices[i] > prices[i - 1]) sum = sum + prices[i] - prices[i - 1];
  
      return sum;
  }
  ```





## 买卖股票的最佳时机III

- 题目：给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。 

  设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。 

  注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。 

- 思路：这里注意到最多可以完成两笔交易，那么就可以这样认为，如果要获取到最大的利益，那么肯定是由两笔交易实现的，那么就可以从后往前和从前往后两个方向实现状态方程，从前往后的是指第一笔交易能够获得到的最大利益；从后往前的是指第二笔交易的

- ```c++
  #include <algorithm>
  #include <cstdio>
  #include <cstring>
  #include <iostream>
  
  using namespace std;
  
  const int N = 100010;
  
  int n;
  int p[N], g[N], f[N]; // 股票价格p[N]，第一次交易最大收益g[N], 第二次交易最大收益f[N]
  
  int main()
  {
      scanf("%d", &n);
      for (int i = 1; i <= n; i++)
          scanf("%d", &p[i]);
  
      for (int i = 2, minv = p[1]; i <= n; i++)//这里是从前往后的
      {
          g[i] = max(g[i - 1], p[i] - minv);
          minv = min(minv, p[i]);
      }
      for (int i = n - 1, maxv = p[n]; i >= 1; i--)//这里是从后往前的
      {
          f[i] = max(f[i + 1], maxv - p[i]);
          maxv = max(maxv, p[i]);
      }
  
      int res = 0;
      for (int i = 2; i <= n; i++)//最后在对每一天进行比较，取最大值
          res = max(res, g[i] + f[i + 1]);
      printf("%d\n", res);
  
      return 0;
  }
  ```





## 买卖股票的最佳时机IV

- 题目：给定一个整数数组 prices ，它的第 i 个元素 prices[i] 是一支给定的股票在第 i 天的价格。 

  设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。 

  注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。 

- 思路：这里主要是先分析在交易的进行中出现了什么状态

  首先是目前是第几次进行交易，目前手上是否有股票，目前是第几天，

  有了这几个状态栏就可以写出状态方程了	

  f [ i ] [ j ] [0/1]
  表示第i天，
  已经完成了j笔交易，
  现在手中有/没有票

  ```c++
  #include<bits/stdc++.h>
  
  using namespace std;
  
  const int INF = 0x3f3f3f3f;
  
  int n,k,a[100005],f[100005][103][2],ans;
  
  int main(){
      scanf("%d",&n);
      scanf("%d",&k);
      for(int i=1; i<=n; i++) scanf("%d",&a[i])
  
      memset(f,-0x3f,sizeof(f)); 
      for(int i=0; i<=n; i++) f[i][0][0] = 0;
  
      for(int i=1; i<=n; i++) 
          for(int j=1; j<=k; j++) 
          {
              f[i][j][0] = max(f[i-1][j][0],f[i-1][j][1]+a[i]);
              f[i][j][1] = max(f[i-1][j][1],f[i-1][j-1][0]-a[i]);
          }
      
      for(int i=0; i<=k; i++) ans = max(ans,f[n][i][0]);
      printf("%d\n",ans);
      return 0;
  }
  ```

  



## 买卖股票的最佳时机含手续费

- 题目：给定一个整数数组 prices，其中第 i 个元素代表了第 i 天的股票价格 ；非负整数 fee 代表了交易股票的手续费用。

  你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。

  返回获得利润的最大值。

  注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。

- 思路：一看到题目，可以想到这道题和上面一道题感觉上是差不多的，所以先写出一种解法

- ```c
  int maxProfit(int* prices, int pricesSize, int fee)
  {
      int i, j, ans, max = 0;
      int dp[100000];
      if (pricesSize == 1) return 0;
      dp[0] = 0;
      
      for (i = 1; i < pricesSize; i++)
      {
          dp[i] = 0;
          for (j = 0; j < i; j++)
          {
              ans = prices[i] - prices[j] - fee;
              dp[i] = dp[i] > dp[j] ? dp[i] : dp[j];
              if (ans > 0 && j >= 1) dp[i] = dp[i] > (ans + dp[j - 1]) ? dp[i] : (ans + dp[j - 1]);
              else if (ans > 0) dp[i] = dp[i] > ans ? dp[i] : ans;
          }
          max = max > dp[i] ? max : dp[i];
      }
  
      return max;
  }
  ```

- 但是不幸的是，第一，这种做法是一种嫉妒贪婪的做法，很可能会因为多次的购买卖出造成的手续费导致利润下降；第二，这种做法的复杂度极高，所以在测评中会有不少数据中出现了超时的现象

  因此按照`DP`一贯的套路，这个时候就要用空间去换时间重新思考问题

  先找一下问题的状态方程，对于每一天来说，要么就是持有股票的，要么就是没有持有股票这两种情况

  注意到如果当天没有股票，那么要么就是前面一天也没有持有股票的最大收益，要么就是前一天持有股票但是今天把股票卖出的最大收益，这两者的最大值

  如果当天有股票，那么要么就是前一天持有股票的最大收益，要么就是前一天没有股票但是今天购买了股票时的最大收益，这两者的最大值

- 因此代码是：

- ```c
  class Solution {
  public:
      int maxProfit(vector<int>& prices, int fee) {
          int maxn = 0, n = prices.size();
          int f[n][3];
          f[0][0] = 0;
          f[0][1] = - prices[0];
  
          for (int i = 1; i < n; ++ i){
              f[i][0] = max(f[i - 1][0], f[i - 1][1] + prices[i] - fee);
              f[i][1] = max(f[i - 1][0] - prices[i], f[i - 1][1]);
              maxn = max(f[i][0], maxn);
          }
  
          return maxn;
      }
  };
  ```





## 最佳买卖股票时机含冷冻期

- 题目：给定一个整数数组，其中第 i 个元素代表了第 i 天的股票价格 。

  设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

  你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

  卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。

- 思路：当前的每天只有以下几种状态，

  - 第一种是没有股票尚在冷冻期，那么这种状态是由前面一天有股票并在今天卖出这种状态继承的
  - 第二种是有股票在手，那么这种状态是由前一天也有股票在手，或者前一天没有股票，今天买了股票的这两种状态继承的
  - 第三种是没有股票也不在冷冻期，那么这种状态是由前一天没有股票尚在冷冻期的状态，或是前一天没有股票也不在冷冻期的两种状态继承的

- ```c++
  
  ```

- 