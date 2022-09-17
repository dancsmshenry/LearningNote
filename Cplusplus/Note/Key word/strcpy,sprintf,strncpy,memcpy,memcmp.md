# strcpy

- 只用于字符串的复制，将const char*的内容拷贝到char *中（不仅复制字符串内容之外，还会复制字符串的结束符）

- 如果参数 dst 所指的内存空间不够大，可能会造成缓冲溢出的错误情况，在编写程序时请特别留意，或者用strncpy()来取代

- ```cpp
  #include <cstdio>
  char *strcpy(char *dst, const char *src);// 把src的内容拷贝到dst中
  
  // 源码
  char * strcpy(char *dst,const char *src) {
      if((dst==NULL)||(src==NULL)) return NULL; 
   
      char *ret = dst; //[1]
   
      while ((*dst++=*src++)!='\0'); //[2]
   
      return ret;//[3]
  }
  ```







# strncpy   

- 用来复制源字符串的前n个字符，src 和 dest 所指的内存区域不能重叠，且 dest 必须有足够的空间放置n个字符

- 如果目标长 > 指定长 > 源长，则将源长全部拷贝到目标长，自动加上’\0’  

- 如果指定长 < 源长，则将源长中按指定长度拷贝到目标字符串，不包括’\0’  

- 如果指定长 > 目标长，运行时错误

- ```cpp
  char *strncpy(char *dest, const char *src, size_t n);
  // 把src的前n个字符复制到dest中，dest不够的用空字符填充
  ```







# sprintf

- 把format数据拷贝到string的后面（后面数据的形式可以格式化的）

- ```cpp
  int sprintf(char *string, char *format [,argument,...]);
  ```







# memcmp

- 把存储区 str1 和存储区 str2 的前 n 个字节进行比较。该函数是按字节比较的

- ```cpp
  #include <cstring>
  int memcmp(const void *str1, const void *str2, size_t n));
  // 相等返回0，不相等返回非零
  ```



为什么不能用memcmp对结构体或对象进行比较？

- memcmp函数是逐个字节进行比较的，而struct存在字节对齐，字节对齐时补的字节内容是随机的，会产生垃圾值，所以无法比较







# memcpy

- 内存拷贝函数，按字节把数据拷贝到目标地址中

- ```cpp
  #include <cstring>
  void *memcpy(void *destin, void *source, unsigned n);
  // 从源内存地址的起始位置开始拷贝若干个字节到目标内存地址中，即从源source中拷贝n个字节到目标destin中
  ```







# 总结

strcpy,sprintf,memcpy的比较

操作对象不同

- strcpy的两个操作对象均为字符串
- sprintf的操作源对象可以是多种数据类型，目的操作对象是字符串
- memcpy的两个对象就是两个任意可操作的内存地址，并不限于何种数据类型。



执行效率

- memcpy最高，strcpy次之，sprintf的效率最低



实现功能

- strcpy主要实现字符串变量间的拷贝
- sprintf主要实现其他数据类型格式到字符串的转化
- memcpy主要是内存块间的拷贝



strcpy和memcpy的比较

内容上
- strcpy只能复制字符串，而memcpy可以复制任意内容，例如字符数组、整型、结 构体、类等。



方法上

- strcpy不需要指定长度，它遇到被复制字符的串结束符"\0"才结束，所以容易溢 出。memcpy则是根据其第3个参数决定复制的长度



用途上

- 通常在复制字符串时用strcpy，而需要复制其他类型数据时则一般用memcpy