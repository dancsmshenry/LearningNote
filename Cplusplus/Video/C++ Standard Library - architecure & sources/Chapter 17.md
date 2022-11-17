# 深度探索array

- ```cpp
  //没有构造和析构函数，是模拟cpp原本的数组
  //这时gcc2.9的版本
  template<typename _Tp, std::size_t _Nm>
  struct array {
      typedef _Tp value_type;
      typedef _Tp* pointer;
      typedef value_type* iterator;
  
      value_type _M_instance[_Nm ? _Nm : 1];
  
      iterator begin() {
          return iterator(&_M_instance[0]);
      }
  
      iterator end() {
          return iterator(&_M_instance[_Nm]);
      }
  };
  ```

- 有关typedef的一些技巧

  - ```cpp
    int a[100];//ok
    int[100] b;//fail
    typedef int T[100];
    T c;//ok
    ```

- 深度探索forward_list（参考课件）