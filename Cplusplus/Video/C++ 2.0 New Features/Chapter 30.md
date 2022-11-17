# Hash function

- gcc4.9

  - ```cpp
    //hash是一个仿函数对象，（1，2，3）的前面是构造出一个临时对象，（1，2，3）则是调用它重载的()函数
    cout << hash<int>()(1,2,3) << endl;//返回的是一个hash code
    ```

- 查看底层是如何实现hash code的（在g2.9？）

  - int等整数类型直接返回整数类型
  - char用特殊的hash算法实现
