- 从cpp11才开始有的

- 和c语言数组相比，优点就是不会退化为数组指针

- 相当于是支持算法以及迭代器的数组（但是不能自动扩容）

- https://zh.cppreference.com/w/cpp/container/array

- 是固定大小的容器

  ```cpp
  #define debug2(a,b) cout<<#a<<" = "<<a<<' '<<#b<<" = "<<b<<endl;
  #include<bits/stdc++.h>
  using namespace std;
  int main(){
      const int n = 5;
      // 定义方式
      //array<type, const int> name;
      // array<int, 5> arr = {1, 3, 4, 6, 9}; or array<int, 5> arr {1, 3, 4, 6, 9};
      array<int, n> arr {1, 3, 4, 6, 9};
  
      // arr.push_back(1); 错误 X
  
      //遍历方式
      for(int i : arr) cout << i << ' '; cout << '\n';
      for(int i = 0; i < n; i++) cout << arr[i] << " \n"[i == n - 1];
      for(auto i = arr.begin(); i != arr.end(); i++) cout << *i << ' '; cout << '\n';
      for(auto i = arr.rbegin(); i != arr.rend(); i++) cout << *i << ' '; cout << '\n';
      for(int i = 0; i < n; i++) cout << arr.at(i) << " \n"[i == n - 1];
  
      //可以使用front 和 back
      debug2(arr.front(), arr.back());
  
      //可以使用swap
      array<int, 2> x {2, 4}, y {20, 40};
      swap(x, y);
      for(int i : x) cout << i << ' '; cout << '\n';
  
      //empty, size, max_size
      array<int, 5> b5; array<int, 0> b0;
      debug2(b0.empty(), b5.empty());
      //因为array是固定大小的容器，所以size = max_size
      debug2(b5.size(), b5.max_size());
  
      return 0;
  }
  ```

<br/>

数据是存储在**栈**上的
