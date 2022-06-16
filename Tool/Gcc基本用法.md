- ```shell
  gcc -c hello.c//只激活预处理，编译，和汇编，也就是他只把程序做成obj文件
  ```

- 这一步只是生成了.o的obj文件



- ```shell
  gcc -s hello.c//只激活预处理和编译，就是指把文件编译成为汇编代码
  ```

- 这一步是生成.s的汇编代码



- ```shell
  gcc -o hello.out hello.c//把文件编译为可执行文件
  ```

- 如果不指定输出的话，默认输出的是a.out文件



- 注意，gcc会将cpp和c的代码都当作c的代码执行

- 如果要用到linux下的pthread的话，就需要加上--ipthread

  - ```shell
    gcc h.c -o thread -lpthread
    ```



- `g++ --version`查询gcc编译器的版本
- `g++ test.cpp -o test`将源程序编译为`test`文件，这里的-o表示要输出一个文件
- `./test`执行编译好的文件
- `gdb test`对test文件进行gdb调试
  - `q`，退出调试
  - `r`，运行程序
- g++和gcc的区别
  - 对于c文件，只能用g++，而cpp两个都可以用



注意一下gcc和g++的用法上的差别

- gcc和g++都是GNU(组织)的一个编译器。
- 后缀名为.c的程序和.cpp的程序g++都会当成是c++的源程序来处理。而gcc不然，gcc会把.c的程序处理成c程序。
- 对于.cpp的程序，编译可以用gcc/g++，而链接可以用g++或者gcc -lstdc++。（个人觉得这条是最重要的）



在语句的最后面加上-std=c++17



# 参考

- https://www.runoob.com/w3cnote/gcc-parameter-detail.html