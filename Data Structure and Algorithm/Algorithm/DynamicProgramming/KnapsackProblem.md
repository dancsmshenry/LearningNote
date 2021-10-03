## 01背包问题

- 题目：

  - 有`N`件物品和一个容量是`V`的背包。每件物品只能使用一次。

    第`i`件物品的体积是`vi`，价值是`wi`。

    求解将哪些物品装入背包，可使这些物品的总体积不超过背包容量，且总价值最大。

    输出最大价值。

- 做法：

  - **方法一**：二维数组

    - 这里用数组`f[i][j]`表示当前的状态，表示在背包的容量为`j`的时候选择前面`i`个物品时能够获得的最大价格

    ​       如果当前能够选择这个物品，则状态方程为`f[i][j] = max(f[i - 1][j], f[i - 1][j - a[i]] + b[i]);`

    ​       即要么就选当前的第`i`个物品，要么就不选第`i`个物品

    ​       否则`f[i][j] = f[i - 1][j];`

    - ```c++
      #include <iostream>
      
      using namespace std;
      
      const int N = 1e6 + 10;
      
      int n, m;
      int a[N], b[N], f[N][N];
      
      int main()
      {
          cin >> n >> m;//n是个数，m是背包容量
          for (int i = 1; i <= n; i ++ ) cin >> a[i] >> b[i];//a[i]是重量,b是价格
      
          for (int i = 1; i <= n; i ++ )
              for (int j = 1; j <= m; j ++ )
                  if (j >= a[i]) f[i][j] = max(f[i - 1][j], f[i - 1][j - a[i]] + b[i]);
                  else f[i][j] = f[i - 1][j];
          
          cout << f[n][m] << endl;
          return 0;
      }
      ```

  - **方法二**：一维数组

    - 动态规划中的一个常见的优化就是空间和时间的相互交换

      从二维数组的情况中可以看到需要用到数组`f[i][j]`这个二维数组，即空间范围开销非常大

      而与此同时也可以观察到，当`i`在不断增大的时候，每一次状态方程的迭代都只和前面一排数字有关，

      比如在算前三个物品的时候，只要看前两个物品的数组状态，前一个物品的数组状态就不再需要了

      所以可以将二维数组降维为一维数组来解决问题

      不过需要注意的是循环的方向需要改变，具体请看代码

    - ```c++
      #include <iostream>
      
      using namespace std;
      
      const int N = 1e6 + 10;
      
      int n, m;
      int a[N], b[N], f[N];
      
      int main()
      {
          cin >> n >> m;//n是个数，m是背包容量
          for (int i = 1; i <= n; i ++ ) cin >> a[i] >> b[i];//a[i]是重量,b是价格
      
          for (int i = 1; i <= n; i ++ )
              for (int j = m; j >= a[i]; j -- )
                  f[j] = max(f[j], f[j - a[i]] + b[i]);
          
          cout << f[m] << endl;
          return 0;
      }
      ```





## 完全背包问题

- 问题：

  - 有`N`种物品和一个容量是`V`的背包，每种物品都有无限件可用。

    第`i`种物品的体积是`vi`，价值是 wi。

    求解将哪些物品装入背包，可使这些物品的总体积不超过背包容量，且总价值最大。

    输出最大价值。

- 做法：

  - **方法一**：二维数组

    - 可以看到这个和01背包问题的差别就是每一件物品都是可以无限次使用的，

      但仔细考察，发现只是在状态方程的地方多了一个表达式罢了

    - 对于每一个物品，我们的选择是拿或者不拿，如果不拿，那么当前的背包容量的状态下能够获得的最大价值就是前`i-1`个物体所能够拿到的最大价值

      如果拿，那么就是当前的物品的价值加上前`i-1`物体在当前容量减去当前物体的容量下能够获取的最大价值，或者是加上前`i`物体在当前容量减去当前物体的容量下能够获取的最大价值（这里就是多出来的一个表达式）

    - ```c++
      #include <iostream>
      
      using namespace std;
      
      const int N = 1e6 + 10;
      
      int n, m;
      int a[N], b[N], f[N][N];
      
      int main()
      {
          cin >> n >> m;//n是物品的数量，m是背包的容积
          for (int i = 1; i <= n; i ++ ) cin >> a[i] >> b[i];//a[i]是重量,b是价格
      
          for (int i = 1; i <= n; i ++ )
              for (int j = 0; j <= m; j ++ )
                  if (j >= a[i]) f[i][j] = max(max(f[i][j - a[i]] + b[i], f[i - 1][j - a[i]] + b[i]), f[i - 1][j]);
                  else f[i][j] = f[i - 1][j];
          
          cout << f[n][m] << endl;
          return 0;
      }
      ```

  - **方法二**：一维数组

    - 优化和01背包问题相似

    - ```c++
      #include <iostream>
      
      using namespace std;
      
      const int N = 1e6 + 10;
      
      int n, m;
      int a[N], b[N], f[N];
      
      int main()
      {
          cin >> n >> m;//n是物品的数量，m是背包的容积
          for (int i = 1; i <= n; i ++ ) cin >> a[i] >> b[i];//a[i]是重量,b[i]是价格
      
          for (int i = 1; i <= n; i ++ )           //从一开始的好处，不用预先初始化
              for (int j = 1; j <= m; j ++ )
                  if (j >= a[i]) f[j] = max(f[j], f[j - a[i]] + b[i]);
          
          cout << f[m] << endl;
          return 0;
      }
      ```





## 多重背包问题

- 问题：

  - 有`N`种物品和一个容量是`V`的背包。

    第`i`种物品最多有 `si` 件，每件体积是`vi`，价值是`wi`。

    求解将哪些物品装入背包，可使物品体积总和不超过背包容量，且价值总和最大。

    输出最大价值。

- 做法：

  - **方法一**：二维数组

    - 对于题目可以这样理解：其实问题的本质还是01背包问题，但是有一个特殊的情况就是每一个物体可以有`si`件（那就在开一个循环就行了）

    - ```c++
      #include <iostream>
      
      using namespace std;
      
      const int N = 1e4 + 10;
      
      int n, m;
      int a[N], b[N], num[N], f[N][N];
      
      int main()
      {
          cin >> n >> m;//n是物品的数量，m是背包的容积
          for (int i = 1; i <= n; i ++ ) cin >> a[i] >> b[i] >> num[i];
          //num[i]是数量,a[i]是重量,b是价格
      
          for (int i = 1; i <= n; i ++ )
              for (int j = 1; j <= m; j ++ )
                  for (int l = 0; l * a[i] <= j && l <= num[i]; l ++ )
                      f[i][j] = max(f[i][j], f[i - 1][j - l * a[i]] + l * b[i]);
          
          cout << f[n][m] << endl;
          return 0;
      }
      ```

  - **方法二**：一维数组

    - 同样用01背包问题的优化

    - ```c++
      #include <iostream>
      
      using namespace std;
      
      const int N = 1e6 + 10;
      
      int n, m;
      int a[N], b[N], num[N], f[N];
      
      int main()
      {
          cin >> n >> m;
          //n是物品的数量，m是背包的容积
          for (int i = 1; i <= n; i ++ ) cin >> a[i] >> b[i] >> num[i];
          //num[i]是数量,a[i]是重量,b是价格
      
          for (int i = 1; i <= n; i ++ )
              for (int j = m; j >= 0; j ++ )
                  for (int l = 0; l <= num[i]; l += a[i])
                      f[j] = max(f[j], f[j - l * a[i]] + l * b[i]);
          
          cout << f[m] << endl;
          return 0;
      }
      ```

  - **方法三**：二进制

    - 既然多重背包的本质还是01背包问题，那么可不可以对于当前的`si`个`i`物品，将其变成数个不同的物品，但是所有的情况都能用这些个物品来表示呢？

      这里就可以引进二进制来优化问题，就是把这`si`个`i`物品分解为数个二的次方组成，而所有的情况也都可以用二进制来表示

    - ```c++
      #include <algorithm>
      #include <iostream>
      #include <vector>
      
      using namespace std;
      
      const int N = 1e6 + 10;
      
      int f[N], n, m;
      struct good
      {
          int w, v;
      };//这里的w存放新物品的重量，v存放新物品的价格
      
      int main()
      {
          vector<good> Good;
      
          cin >> n >> m;
          //n是物品的数量，m是背包的容积
          for (int i = 1; i <= n; i ++ )
          {
              int v, w, s;
              cin >> v >> w >> s;
              //v是价值，w是重量，s是数量
      
              for (int k = 1; k <= s; k *= 2)
              {
                  s -= k;
                  Good.push_back({k * w, k * v});
                  //创建的新数组Good用于存放已被二进制转化的背包
              }
              if (s > 0) Good.push_back({s * w, s * v});
          }
      	
          //问题变成01背包问题
          for (auto t : Good)
              for (int j = m; j >= t.v; j--)
                  f[j] = max(f[j], f[j - t.v] + t.w);
      
          cout << f[m] << endl;
          return 0;
      }
      ```

  - **方法四**：单调队列优化

    - 既然可以用数组的方法来优化，那么也可以用一个单调队列的方法将时间复杂度优化至`O(nv)`

    - 令 dp[j] 表示容量为j的情况下，获得的最大价值
      那么，针对每一类物品 i ，我们都更新一下 dp[m] --> dp[0] 的值，最后 dp[m] 就是一个全局最优值
    
      dp[m] = max(dp[m], dp[m-v] + w, dp[m-2*v] + 2*w, dp[m-3*v] + 3*w, ...)
    
      接下来，我们把 dp[0] --> dp[m] 写成下面这种形式
      dp[0], dp[v],   dp[2*v],   dp[3*v],   ... , dp[k*v]
      dp[1], dp[v+1], dp[2*v+1], dp[3*v+1], ... , dp[k*v+1]
      dp[2], dp[v+2], dp[2*v+2], dp[3*v+2], ... , dp[k*v+2]
      ...
      dp[j], dp[v+j], dp[2*v+j], dp[3*v+j], ... , dp[k*v+j]
      显而易见，m 一定等于 k*v + j，其中  0 <= j < v
      所以，我们可以把 dp 数组分成 j 个类，每一类中的值，都是在同类之间转换得到的
      也就是说，dp[k*v+j] 只依赖于 { dp[j], dp[v+j], dp[2*v+j], dp[3*v+j], ... , dp[k*v+j] }
    
      因为我们需要的是{ dp[j], dp[v+j], dp[2*v+j], dp[3*v+j], ... , dp[k*v+j] } 中的最大值，
      可以通过维护一个单调队列来得到结果。这样的话，问题就变成了 j 个单调队列的问题
    
    - ```c++
      #include <cstring>
      #include <iostream>
      
      using namespace std;
      
      const int N = 1e6 + 10;
      
      int dp[N], pre[N], q[N];
      int n, m;
      
      int main()
      {
          cin >> n >> m;
          for (int i = 0; i < n; ++i)
          {
              memcpy(pre, dp, sizeof(dp));
              int v, w, s;
              cin >> v >> w >> s;
              for (int j = 0; j < v; ++j)
              {
                  int head = 0, tail = -1;
                  for (int k = j; k <= m; k += v)
                  {
                      if (head <= tail && k - s * v > q[head])
                          ++head;
                      while (head <= tail && pre[q[tail]] - (q[tail] - j) / v * w <= pre[k] - (k - j) / v * w)
                          --tail;
                      if (head <= tail) dp[k] = max(dp[k], pre[q[head]] + (k - q[head]) / v * w);
                      q[++tail] = k;
                  }
              }
          }
          cout << dp[m] << endl;
          return 0;
      }
      ```





## 混合背包问题

- 问题：

  - 有`N`种物品和一个容量是`V`的背包。

    物品一共有三类：

    - 第一类物品只能用1次（01背包）；
    - 第二类物品可以用无限次（完全背包）；
    - 第三类物品最多只能用`si`次（多重背包）；

    每种体积是`vi`，价值是`wi`。

    求解将哪些物品装入背包，可使物品体积总和不超过背包容量，且价值总和最大。
    输出最大价值。

- 做法：

  - 本质还是01背包问题，但是要注意完全背包和多重背包问题的转换，同时使用二进制优化

  - ```c++
    #include <bits/stdc++.h>
    
    using namespace std;
    
    const int N = 1e6 + 10;
    
    int n, m, v[N], w[N], f[N];
    
    int main()
    {
        cin >> n >> m;
        int cnt = 1;
        for (int i = 1; i <= n; i++)
        {
            int a, b, s, k = 1;
            cin >> a >> b >> s;
            //a为价值，b为重量，s为数量
            //这里规定s=-1的时候为01背包，s=0为完全背包，s>0为多重背包
            if (s < 0) s = 1;
            //即为01背包问题
            else if (s == 0) s = m / a;
            //把完全背包先转化成多重背包，则在最优情况下，只能取总体积/该物品体积向下取整（因为最多只能拿这么多）
            //接下来就是二进制优化
            while (k <= s)
            {
                v[cnt] = a * k;
                w[cnt] = b * k;
                s -= k;
                k *= 2;
                cnt++;
            }
            //如果是多重背包问题，除了二进制优化，还要注意一种情况，就是该种物品能拿到该种物品的数量上的极限
            if (s > 0)
            {
                v[cnt] = s * a;
                w[cnt] = s * b;
                cnt++;
            }
        } 
        //将多重背包进行二进制优化，变成01背包
        for (int i = 1; i <= cnt; i++)
            for (int j = m; j >= v[i]; j--)
                f[j] = max(f[j], f[j - v[i]] + w[i]);
    
        cout << f[m] << endl;
        return 0;
    }
    ```





## 二维费用背包问题

- 问题：

  - 有`N`件物品和一个容量是`V`的背包，背包能承受的最大重量是`M`。

    每件物品只能用一次。体积是`vi`，重量是`mi`，价值是`wi`。

    求解将哪些物品装入背包，可使物品总体积不超过背包容量，总重量不超过背包可承受的最大重量，且价值总和最大。
    输出最大价值。

- 做法：

  - **方法一**：二维数组

    - 做法和01背包问题相似，即对于前面`i`件物品，在体积为`j`和的情况和承受重量为`k`的情况下，能够拿到的最大价值

    - ```c++
      #include <bits/stdc++.h>
      
      using namespace std;
      
      const int N = 1e4 + 5;
      
      int n, V, M;
      int v[N], m[N], w[N], f[N][N];
      
      int main () 
      {
          cin >> n >> V >> M;//数量，体积，最大承受重量
          for (int i = 1; i <= n; i ++) 
              cin >> v[i] >> m[i] >> w[i]; //体积，重量，价值
      
          for (int i = 1; i <= n; i ++)
              for (int j = V; j >= v[i]; j --)
                  for (int k = M; k >= m[i]; k --)
                      f[j][k] = max (f[j - v[i]][k - m[i]] + w[i], f[j][k]);
      
          cout << f[V][M] << endl;
          return 0;
      } 
      ```





## 分组背包问题

- 问题：

  - 有`N`组物品和一个容量是`V`的背包。

    每组物品有若干个，同一组内的物品最多只能选一个。
    每件物品的体积是`vij`，价值是`wij`，其中`i`是组号，`j`是组内编号。

    求解将哪些物品装入背包，可使物品总体积不超过背包容量，且总价值最大。

    输出最大价值。

- 做法：

  - **方法一**：二维数组

    - 还是把问题看成01背包问题，但是要注意的是这里是把每个组都看成一个物品

      然后解决。不过需要注意的是既然虽然看成一个物品，但是每次还是要循环组内的物品进行比较容量的大小

      即状态方程为当前能拿物品的时候`f[i][j] = max(f[i][j], f[i - 1][j - v[i][k]] + w[i][k]);`

      不能拿物品的时候`f[i][j] = f[i - 1][j];`

    - ```c++
      #include <bits/stdc++.h>
      using namespace std;
      
      const int N = 1e3 + 10;
      int f[N][N], v[N][N], w[N][N], s[N];
      int n, m, k;
      
      int main()
      {
          cin >> n >> m;
          //n是物品的组数，m是背包的容量
          for (int i = 1; i <= n; i ++ )
          {
              cin >> s[i];
              //s[i]表示该组有多少个物品
              for (int j = 0; j < s[i]; j ++ )
                  cin >> v[i][j] >> w[i][j]; 
          }
      
          for (int i = 1; i <= n; i ++ )
              //循环每一个组
              for (int j = 0; j <= m; j ++ )
                  //循环每一个容量
              {
                  f[i][j] = f[i - 1][j];
                  //假设当前不拿，则最优的情况就是前i-1个组的情况在容量为j的情况
                  for (int k = 0; k < s[i]; k ++ )
                      //循环组内的每一个物品，先看是否能拿，再看是否价值是否比原来的大
                      if (j >= v[i][k])
                          f[i][j] = max(f[i][j], f[i - 1][j - v[i][k]] + w[i][k]);
              }
      
          cout << f[n][m] << endl;
          return 0;
      }
      ```

  - **方法二**：一维数组

    - 优化方法同理，一维滚动数组

    - ```c++
      #include <bits/stdc++.h>
      
      using namespace std;
      
      const int N = 1e4 + 10;
      
      int v[N][N], w[N][N], s[N], f[N];
      int n, m, k;
      
      int main()
      {
          cin >> n >> m;
          for (int i = 0; i < n; i ++ )
          {
              cin >> s[i];
              for (int j = 0; j < s[i]; j ++ )
              {
                  cin >> v[i][j] >> w[i][j];
              }
          }
      
          for (int i = 0; i < n; i ++ )
              for (int j = m; j >= 0; j -- )
                  for (int k = 0; k < s[i]; k ++ )
                      if (j >= v[i][k])
                          f[j] = max(f[j], f[j - v[i][k]] + w[i][k]);
      
          cout << f[m] << endl;
          return 0;
      }
      ```





## 背包问题求方法数

- 问题：

  - 有`N`件物品和一个容量是`V`的背包。每件物品只能使用一次。

    第`i`件物品的体积是`vi`，价值是`wi`。

    求解将哪些物品装入背包，可使这些物品的总体积不超过背包容量，且总价值最大。

    输出 **最优选法的方案数**。注意答案可能很大，请输出答案模`1e9+7` 的结果。

- 做法：

  - 同样是01背包问题，但是问的是背包方案的数量，这里可以先用一维数组优化，然后再开一个数组记录再当前的重量下能够达到的最大价值的方案数，最后再输出

```c++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e6 + 10;

int n, m, maxn = 0;
int a[N], b[N], f[N], q[N];
//q[]数组记录数量，

int main()
{
    cin >> n >> m;//n是个数，m是背包容量
    for (int i = 1; i <= n; i ++ ) cin >> a[i] >> b[i];//a[i]是体积,b[i]是价值
    memset(q, 1, N - 1);//这里什么也不装也是一种方案

    for (int i = 1; i <= n; i ++ )
        for (int j = m; j >= a[i]; j -- )
            if (f[j - a[i]] + b[i] > f[j])
                //当前如果能够拿到比之间大的价值的话就拿，同时更新数量
            {
                f[j] = f[j - a[i]] + b[i];
                q[j] = q[j - a[i]];
            }
    //但如果价值相同的话，那么就只更新数量
            else if (f[j - a[i]] + b[i] == f[j]) q[j] += q[j - a[i]];

    cout << q[m] << endl;
    return 0;
}
```



