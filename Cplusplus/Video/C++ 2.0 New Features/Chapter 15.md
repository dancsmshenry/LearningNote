# Variadic templates I

- 变化的是：

  - 参数个数（利用参数个数逐一逐减的特性，实现递归函数调用，使用function template完成）
  - 参数类型（利用参数个数逐一逐减导致参数类型也逐一逐减的特性，以class template完成）

- 代码一

  - ```cpp
    void printX{}
    
    template<typename T, typename... Types>
    void printX(const T& firstArg, const Types&... args){
        cout << firstAeg << endl;
        printX(args);
    }
    
    template<typename... Types>
    void printX(const Types&... args){
        ...
    }
    
    /**
    对于模板函数的重载，是谁更特化就用谁，这里的话，认为是第一个版本更加的特化（可能是第一个版本有第一个参数吗？）
    **/
    ```

