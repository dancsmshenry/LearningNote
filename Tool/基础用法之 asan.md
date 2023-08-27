使用 asan 对内存泄漏进行排查（只有运行了内存泄漏的代码，才会报错）

```Shell
g++ main.cc -o main -lasan # 编译的时候链接库
```