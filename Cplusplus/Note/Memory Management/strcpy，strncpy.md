# 函数原型

- ```cpp
  char* strcpy(char* strDest, const char* strSrc)
  char* strncpy(char* strDest, const char* strSrc, int pos)
  ```

- strcpy函数: 如果参数 dest 所指的内存空间不够大，可能会造成缓冲溢出(buffer Overflow)的错误情 况，在编写程序时请特别留意，或者用strncpy()来取代。 

- strncpy函数：用来复制源字符串的前n个字符，src 和 dest 所指的内存区域不能重叠，且 dest 必须有足 够的空间放置n个字符

- 如果目标长>指定长>源长，则将源长全部拷贝到目标长，自动加上’\0’  

- 如果指定长<源长，则将源长中按指定长度拷贝到目标字符串，不包括’\0’  

- 如果指定长>目标长，运行时错误