## 7、NULL 和 nullptr 的区别

- 在 c 语言中只有 NULL ，用来表示空指针

  - ```c
    #define NULL ((void*)0)
    ```

- 而在 cpp 中，因为 cpp 是强类型语言， void* 是不能隐式转换成其他类型

  - 所以，cpp引入0来表示空指针

  - ```cpp
    #ifdef __cplusplus
    #define NULL 0
    #else
    #define NULL ((void *)0)
    #endif
    ```

- 但是null会造成二义性（参考https://blog.csdn.net/qq_18108083/article/details/84346655）

- 所以cpp11中引入nullptr，来代表空指针

- 总结：

  - NULL在C++中就是0，这是因为在C++中void* 类型是不允许隐式转换成其他类型的，所以之前C++中用0来代表空指针，但是在重载整形的情况下，会出现上述的问题。所以，C++11加入了nullptr，可以保证在任何情况下都代表空指针，而不会出现上述的情况，因此，建议以后还是都用nullptr替代NULL吧，而NULL就当做0使用

- 