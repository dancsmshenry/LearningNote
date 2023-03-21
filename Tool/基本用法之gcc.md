# 编译链接全过程

源文件.cpp，.h文件

- 源文件.cpp，.h文件经过了**预编译**，得到.i文件

- .i文件经过了**编译**，得到了.s文件

- .s文件经过了**汇编**，得到了.o文件

- .o文件经过了**链接**，得到了.exe文件

<br/>

<br/>

<br/>

# Gcc/G++命令

## 源文件 -> 预编译

- ```shell
  g++ -E test.cpp -o test.i // 将源代码cpp预编译为.i文件（这里必须要是-E）
  ```

<br/>

## 预编译文件 -> 编译

- ```shell
  g++ -S -o  test.s test.i // 预编译文件编译后得到.s文件
  ```

<br/>

## 编译后的代码 -> 汇编

- ```shell
  g++ -c -o test.o test.s // 编译后的代码汇编后得到.o文件
  gcc -c main.c // 直接编译为.ow
  ```

<br/>

## 汇编代码 -> 链接

- ```shell
  gcc -o test test.o // 生成可执行文件hello.exe
  g++ test.o -o test // 或者这样
  ```

<br/>

## 执行程序

- ```shell
  ./test
  ```

<br/>

## 编译链接一条龙

- ```shell
  gcc -o hello.out hello.c
  gcc test.c -o test // 或者这样，生成名为test.exe的可执行文件
  gcc test.c // 默认生成名为a.exe的可执行文件
  ```

<br/>

## 编译时添加linux线程库

- ```shell
  g++ test.cpp -o test -pthread
  ```

<br/>

## 查询gcc编译器版本

- ```shell
  g++ --version
  ```

<br/>

## 指定版本编译

- ```shell
  g++ test.cpp -o test -std=c++17
  ```

<br/>

## gcc编译c++文件

- ```shell
  gcc test.cpp -o test -lstdc++
  ```

- gcc可以编译c++文件，也可以编译c文件，但默认是编译c文件的

- 加-lstdc++表示编译c++文件，即链接c++库

- 加-lc表示链接c库，默认情况下就是链接c库，所以如果编译c文件可以不加-lc

<br/>

## gcc和g++的区别

- 编译器本身是什么就编译什么
  - 例如.c文件给g++，那就当作c++编译
  - 例如.cpp文件给gcc，那就当作c编译（但默认不能链接cpp的库）
- 对于.cpp的程序，编译可以用gcc/g++，而链接可以用g++或者gcc -lstdc++

<br/>

## `gdb test`对test文件进行gdb调试

- `q`，退出调试
- `r`，运行程序

<br/>

## 指定系统位数编译

- ```shell
  g++ test.cpp -o test -m32// 强制32位b
  ```

<br/>

<br/>

<br/>

# 参考

- https://www.runoob.com/w3cnote/gcc-parameter-detail.html
- https://blog.csdn.net/sdc20102010/article/details/90549113
- https://www.nowcoder.com/discuss/690899