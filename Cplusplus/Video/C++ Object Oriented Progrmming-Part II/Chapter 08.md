# function template

- ```cpp
  template <class T>
  inline const T& min(const T& a, const T&b){
      return b < a ? b : a;
  }
  ```

- 在具体使用到模板的时候会再编译一次（所以可能第一次编译写好的模板代码的时候，是可以通过的，但是后续把T放入的时候，可能就无法通过了）