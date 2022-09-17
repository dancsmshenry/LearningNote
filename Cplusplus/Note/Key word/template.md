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

- 