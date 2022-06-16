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





# strcpy和memcpy的区别

- 内容上：
  - strcpy只能复制字符串，而memcpy可以复制任意内容，例如字符数组、整型、结 构体、类等。
- 方法上：
  - strcpy不需要指定长度，它遇到被复制字符的串结束符"\0"才结束，所以容易溢 出。memcpy则是根据其第3个参数决定复制的长度
- 用途上
  - 通常在复制字符串时用strcpy，而需要复制其他类型数据时则一般用memcpy





# 函数原型 strcpy，strncpy

- ```cpp
  char* strcpy(char* strDest, const char* strSrc)
  char* strncpy(char* strDest, const char* strSrc, int pos)
  ```

- strcpy函数: 如果参数 dest 所指的内存空间不够大，可能会造成缓冲溢出(buffer Overflow)的错误情 况，在编写程序时请特别留意，或者用strncpy()来取代。 

- strncpy函数：用来复制源字符串的前n个字符，src 和 dest 所指的内存区域不能重叠，且 dest 必须有足 够的空间放置n个字符

- 如果目标长>指定长>源长，则将源长全部拷贝到目标长，自动加上’\0’  

- 如果指定长<源长，则将源长中按指定长度拷贝到目标字符串，不包括’\0’  

- 如果指定长>目标长，运行时错误





# 使用memcmp判断结构体是否相等的隐患

- memcmp是将两个变量在底层按字节进行比较，相等返回0，不等返回非0
- memcmp函数是逐个字节进行比较的，而struct存在字节对齐，字节对齐时补的字节内容是随机的，会产生垃圾值，所以无法比较