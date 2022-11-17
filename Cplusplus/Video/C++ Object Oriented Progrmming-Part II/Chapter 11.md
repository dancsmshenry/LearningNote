# 模板偏特化

- partial specialization，模板偏特化-个数的偏/范围上的偏

- 个数上的偏

  - ```cpp
    template<typename T, typename Alloc = ...>
    class vector{};
    
    template<typename Alloc = ...>
    class vector<bool, Alloc>{};//模板的偏特化，这里表示如果T是bool类型的话，那么就会调用下面的代码
    ```

- 范围上的偏

  - ```cpp
    template<typename T>
    class C{};//一般的泛化
    
    template<typename U>//这里也可以写T，不过上面和下面不是同一样东西
    class C<U*>{};//模板偏特化，即表示如果传进来的是一个指针，那么就会调用下面的代码
    //即范围上的偏特化，原来是任意类型，现在指定是指针类型或其他类型
    ```
