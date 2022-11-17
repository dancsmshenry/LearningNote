# Initializer_list I

- 用初始化列表初始化变量，会为变量设定初值

  - ```cpp
    int i;//i has undefined value
    int j{};//j is initialized by 0;
    int* p;//p has undefined value;
    int* q{};//q is initialized by nullptr
    ```

- 不能做很强硬的类型转换（比如整型和浮点的转换，），可以做char和int类型的转换

  - 但是在一些编译器上，是会提示警告，不会报错
