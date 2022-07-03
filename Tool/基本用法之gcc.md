# 编译链接全过程

原料：源文件.cpp，.h文件

源文件.cpp，.h文件经过了**预编译**，得到.i文件

.i文件经过了**编译**，得到了.s文件

.s文件经过了**汇编**，得到了.o文件

.o文件经过了**链接**，得到了.exe文件





# Gcc命令

##### 源文件->预编译

- ```shell
  g++ -E test.cpp -o test.i // 将源代码cpp预编译为.i文件（这里必须要是-E）
  ```



##### 预编译文件->编译

- ```shell
  g++ -S -o  test.s test.i // 预编译文件编译后得到.s文件
  ```



##### 编译后的代码->汇编

- ```shell
  g++ -c -o test.o test.s // 编译后的代码汇编后得到.o文件
  ```



##### 汇编后的代码->链接

- ```shell
  gcc -o test test.o // 生成可执行文件hello.exe
  g++ test.o -o test // 或者这样
  ```



##### 执行程序

- ```shell
  ./test
  ```



##### 编译链接一条龙

- ```shell
  gcc -o hello.out hello.c
  gcc test.c -o test // 或者这样，生成名为test.exe的可执行文件
  gcc test.c // 默认生成名为a.exe的可执行文件
  ```



##### 编译时添加linux线程库

- ```shell
  g++ test.cpp -o test -pthread
  ```



##### 查询gcc编译器版本

- ```shell
  g++ --version
  ```



##### 指定版本编译

- ```shell
  g++ test.cpp -o test -std=c++17
  ```



##### gcc和g++的区别

- 编译器本身是什么就编译什么
  - 例如.c文件给g++，那就当作c++编译
  - 例如.cpp文件给gcc，那就当作c编译（但默认不能链接cpp的库）
- 对于.cpp的程序，编译可以用gcc/g++，而链接可以用g++或者gcc -lstdc++



`gdb test`对test文件进行gdb调试

- `q`，退出调试
- `r`，运行程序





# 参考

- https://www.runoob.com/w3cnote/gcc-parameter-detail.html