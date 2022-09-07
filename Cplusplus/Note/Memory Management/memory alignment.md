# 背景

- 平台原因（移植原因）：
  - 不是所有的硬件平台都能访问任意地址上的任意数据的；某些硬件平台只能在某些地址处取某些特定类型的数据，否则抛出硬件异常
  - 所以一些跨端的代码中，必须要取消相应的字节对齐
- 性能原因：
  - 原因在于：为了访问未对齐的内存，处理器需要作两次内存访问（比如说一个未对齐的int分别占据了数据位置的3456的位置，那么取数据的时候就必须先取0-3之间的数据，把012的数据丢弃，然后再取4-7之间的数据，然后把7位置的给丢弃）；而对齐的内存访问仅需要一次访问
  - 所以内存对齐的本质就是牺牲一些内存空间，换取**高效的读取速度**







# 定义

- 内存存取粒度：处理器以双字节,四字节,8字节,16字节甚至32字节为单位来存取内存

- 内存对齐：现代计算机中内存空间都是按照 byte 划分的，从理论上讲似乎对任何类型的变量的访问可以从任何地址开始，但是实际的计算机系统对基本类型数据在内存中存放的位置有限制，它们会要求这些数据的首地址的值是某个数n（通常它为4或8）的倍数







# 规则

- 规则一：在32位编译环境下默认**4字节对齐**，在64位编译环境下默认**8字节对齐**

- 规则二：**结构体的总大小**为**有效对齐值**的**整数倍**，如有需要编译器会在最末一个成员之后加上填充字节

- 规则三：结构体第一个成员的**偏移量（offset）**为0，以后每个成员相对于结构体首地址的 offset 都是**该成员大小与有效对齐值中较小**那个的整数倍，如有需要编译器会在成员之间加上填充字节

- ```cpp
  #include <iostream>
  // #pragma pack(1) // 17个字节 
  //	l1 8个字节 l2 1个字节 i1,i2共8个字节
  
  // #pragma pack(2) // 18个字节 
  //	l1 8个字节 l2 1个字节（因为i1要对齐，所以加上1个字节的padding） i1,i2共8个字节
  
  // #pragma pack(4) // 20个字节 
  //	l1 8个字节 l2 1个字节（因为i1要对齐，所以加上3个字节的padding） i1,i2共8个字节
  
  // #pragma pack(8) // 24个字节
  //	l1 8个字节 l2 1个字节 （因为i1要对齐，所以加上3个字节的padding）
  //	i1 4个字节 i2 4个字节（最后补上padding 4个字节，使得整个结构体的大小为对齐值的整数倍）
  
  // #pragma pack(16) // 24个字节
  //	l1 8个字节 l2 1个字节 （因为i1要对齐，所以加上3个字节的padding）
  //	i1 4个字节 i2 4个字节（最后补上padding 4个字节，使得整个结构体的大小为对齐值的整数倍）
  
  struct s1 {
      long long l1;
      char l2;
      int i1, i2;
  };
  
  int main() {
      std::cout << "sizeof(s1) = " << sizeof(s1) << " " << std::endl;
  }
  ```

- 一个二级结论：如果pack的对齐数n大于所有的数据，那么这个n会被退化为相应的字节对齐数（比如说上面的8字节对齐和16字节对齐的结果完全是一样的）







# 语法

### 获得结构成员的字节偏移量

- ```cpp
  #include <iostream>
  #include <stddef.h>
  using namespace std;
  struct S {
   int x;
   char y;
   int z;
   double a;
  };
  
  int main() {
   //	使用头文件中的，offsetof宏
   cout << offsetof(S, x) << endl; // 0
   cout << offsetof(S, y) << endl; // 4
   cout << offsetof(S, z) << endl; // 8
   cout << offsetof(S, a) << endl; // 12
   return 0;
  }
  ```





### 重置字节对齐

- ```cpp
  #pragma  pack(n)  // 编译器将按照n个字节对齐
  #pragma  pack(push)
  #pragma  pack()   // 恢复先前的pack设置,取消设置的字节对齐方式
  #pragma  pack(pop)// 恢复先前的pack设置,取消设置的字节对齐方式
  #pragma  pack(1)  // 按1字节进行对齐
  //	只能取值为1 2 4 8 16
  //	偏移量要是n和当前变量大小中较小值的整数倍
  //	整体大小要是n和最大变量大小中较小值的整数倍
  ```





### 取消结构体字节对齐

- ```cpp
  typedef struct
  {
      double x;
      double y;
  } __attribute__((packed)) position_t;
  
  //	在结构体定义的最后或者前面加上这一串，可以避免结构体发生字节对齐的情况
  struct __attribute__((__packed__)) sdshdr8
  {
      uint8_t len;         /* 数据⻓度 */
      uint8_t alloc;       /* 去掉头和null结束符，有效⻓度+数据⻓度*/
      unsigned char flags; /* 3 lsb of type, 5 unused bits，⼩端*/
      //变⻓数据
      char buf[];
  };
  ```





# 更底层的

- https://yangwang.hk/?p=773





# reference

- https://zhuanlan.zhihu.com/p/83449008
- https://zhuanlan.zhihu.com/p/30007037