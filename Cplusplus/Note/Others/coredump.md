# 背景

- coredump是程序由于异常或者bug在运行时异常退出或者终止，在一定的条件下生成的一个叫做core的文件，这个core文件会记录程序在运行时的内存，寄存器状态，内存指针和函数堆栈信息等等。对这个文件进行分析可以定位到程序异常的时候对应的堆栈调用信息

- ```cpp
  g++ test.cpp -g -o test//当程序coredump后，会生成coredumpw
  ```

- 