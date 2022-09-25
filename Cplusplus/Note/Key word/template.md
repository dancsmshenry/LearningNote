- ```cpp
  #include <iostream>
  #include <memory>
  
  template<typename T>
  T sub(T& a, T& b) {
      return a - b;
  }
  
  const int (*pfun1)(const int& a, const int& b);
  const int (*pfun2)(int& a, int& b);
  int (*pfun3)(const int& a, const int& b);
  int (*pfun4)(int& a, int& b);
  
  int main () {
      // pfun1 = sub<int>;// error
      // pfun2 = sub<int>;// error
      // pfun3 = sub<int>;// error
      pfun4 = sub<int>;   
  }
  ```

- 说明了一点，函数模板必须每个数据都要对的上才可以（比如说const等）



- 函数模板的重载受一些条件局限

- ```cpp
  template<typename T>
  T v1(T t1, T t2) {}
  
  template<typename T>
  T v1(T t1, T t2, T t3) {}
  
  //	只能这样的方式实现重载..
  //	而原来的重载，是可以通过函数类型的不同来实现的（模板就会有点局限..）
  
  template<typename T>
  void v1(T t1, T t2, int t3) {std::cout << "int" << std::endl;}
  
  template<typename T>
  void v1(T t1, T t2, T t3) {std::cout << "T" << std::endl;}
  // 比如说这种重载，遇到v1(1,2,3);就会出问题.
  ```

- 