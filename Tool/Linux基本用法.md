# Linux下调试cpp程序

- `vi test.cpp`写入一段cpp程序
- `g++ --version`查询gcc编译器的版本
- `g++ test.cpp -o test`将源程序编译为`test`文件，这里的-o表示要输出一个文件
- `./test`执行编译好的文件
- `gdb test`对test文件进行gdb调试
  - `q`，退出调试
  - `r`，运行程序
- g++和gcc的区别
  - 对于c文件，只能用g++，而cpp两个都可以用
- 进入文件夹：`cd 文件夹名`
- 删除文件
  - `rm -f 文件名`，删除单个文件
  - `rm -r 文件名`，递归删除，不管有多少个文件，全部删除

- 重复上一次命令：!!