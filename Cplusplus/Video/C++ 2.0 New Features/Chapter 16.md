# Variadic templates II

代码二

- ```cpp
  template<typename T, typename... Args>
  void printf(const char* s, T value, Args... args){
      while (*s){//一直循环
          if (*s == '%' && *(++s) != '%'){
              cout << value;//如果是符号，并且后面一项不是符号，就把后面的值，即value给输出
              printf(++s, args...);
              return ;
          }
          cout << *s ++ ;//不是符号的话就直接输出
      }
      throw logic_erroe("extra argtements provided to printf");
  }
  
  void printf(const char* s){
      while (*s){
          if (*s == '%' && *(++s) != '%'){
              throw logic_erroe("extra argtements provided to printf");
          }
          cout << *s ++ ;
      }
  }
  ```

