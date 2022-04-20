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





# 参考

- https://www.runoob.com/w3cnote/gcc-parameter-detail.html