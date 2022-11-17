# Variadic templates IV

- 若参数type相同，比较的是同一种数据，则无需改动

- 代码四

  - ```cpp
    int maximum(int n){return n;}
    
    template<typename... Args>
    int maximum(int n, Args... args){
        return std::max(n, maximum(args...));
    }
    ```

- 在标准库中，max已经可以接收任意数量的参数值了，不过要这样写

  - ```cpp
    #include<algorithm>
    cout << max({1,2,3,4,5,6,7,8,9,10}) << endl;
    ```

