# priority_queue

### 用法

- ```cpp
  priority_queue<int, vector<int>, greater<int>> q;//堆顶是最小的元素，堆底是最大的元素（小顶堆），升序队列，这里升序队列是指从左到右，数据依次递增；而本质还是队列，所以每次出去都是最小的元素出去
  greater<int>;//也是仿函数
  
  priority_queue<int, vector<int>, less<int>> p;//降序队列（大顶堆）
  
  q.top();//堆顶的元素
  q.pop();//踢出堆顶的元素
  q.push();//放入元素
  q.empty();//查看是否为空
  
  priority_queue<pair<int, int>> q;//pair的比较是先比较第一个元素，第一个相等就比较第二个元素
  ```

- 队列，但是他和queue不同的就在于我们可以自定义其中数据的优先级，让优先级高的排列在队列前面，优先出队

- ```cpp
  //自定义数据
  struct tmp1 {//数据本身，运算符重载
      int x;
      tmp1(int a) {
          x = a;
      }
      bool operator<(const tmp1& a) const {
          return x < a.x;
      }
  }
  
  struct tmp2 {
      bool operator() (const tmp1& a, const tmp1& b) {
          return a.x < b.x;//大根堆
      }
  }
  
  priority_queue<tmp1, vector<tmp1>, tmp
  ```





