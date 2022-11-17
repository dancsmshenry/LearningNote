# reference

- 对于一个引用，从使用者的角度来看，引用就是对象的一个别名；但是从编译器的角度来看，引用的本质其实是一个指向其对象的指针

- ```cpp
  sizeof(r) == sizeof(x);
  &x = &r;//object和其reference的大小相同，地址也相同（全都是假象）
  ```

- java里面所有变量都是reference

- 引用必须要有初始值，并且不能改变指向

- ps：指针（4个字节，在32位电脑上）

- reference被认为是一种漂亮的pointer

- reference通常不用于声明变量，而用于参数类型和返回类型的描述

- ```cpp
  double imag(const double& im){}
  double imag(const double im){}//这两个函数被视为同一个函数，不能共存
  ```

- 注意传入和接收的写法（比如我传入的是一个对象的引用，接收端却是以指针的方式接收的，不好）

- const可以作为函数签名的一部分

  - ```cpp
    double imag(const double& im){}
    double imag(const double im) const{}//这两个函数被视为同一个函数，不能共存；但是加上了const，两个函数不同，可以并存
    ```
