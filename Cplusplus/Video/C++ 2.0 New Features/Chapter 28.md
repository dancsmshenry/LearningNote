# 容器 array

- 相当于一个包装好的数组

- gcc2.9版本

  - 没有ctor，也没有dtor

- cpp2.0后的array

  - ```cpp
    int a[1000];
    int[1000] b;//error
    typedef int T[100];
    T b;//yes
    ```
