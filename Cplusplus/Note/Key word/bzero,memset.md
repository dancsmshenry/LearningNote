bzero

- bzero() 能够将内存块（字符串）的前n个字节清零
- 在"string.h"头文件中
- 原型为： void bzero(void *s, int n);，没有返回值
- 是posix标准中的函数，windows下用不了...
- bzero(void *s, int n) 与 memset((void * )s, 0,size_tn)是等价的，都是用来将内存块的前 n 个字节清零，但是 s 参数为指针，又很奇怪的位于 string.h 文件中，也可以用来清零字符串



- bcopy、bzero和bcmp是传统BSD的函数，属于POSIX标准

  memcpy、memset、memcmp是C90(以及C99)标准的C函数。

  区别在于，如果你打算把程序弄到一个符合C90/C99，但是不符合POSIX标准的平台时，mem*比较有优势。



memset

- ```cpp
  void *memset(void *s, int c, size_t n);  //返回指向s的指针。,也可以不用这个返回的指针
  //	将s开头的长度为n的z
  ```



- 相同点：都是将一块内存进行归一化
- 不同点：bzero只能用在linux下，并且只能全部归零；而memset可以变成其他的数据