# 三大函数：拷贝构造，拷贝赋值，析构

Big Three：拷贝构造，拷贝赋值，析构函数

- 注意在析构函数中，要被对象本身含有的其他对象也一并清零

- ```cpp
  String *p = new String("Hello");//这样也会调用拷贝构造函数
  ```

- 注意拷贝函数（拷贝赋值）中，如果有指针类的对象，要注意深拷贝和浅拷贝（否则编译器提供的就是浅拷贝）

- 注意拷贝赋值函数，先要进行自我赋值检测（而后的操作是：先删掉自己的数据，然后创建空间，接着把数据放入创建好的空间中。最后返回引用对象）

  - 如果不进行自我赋值检测，会造成说直接就把原来的数据给删掉了的情况