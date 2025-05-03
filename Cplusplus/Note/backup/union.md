union数据结构中的数据是共用内存地址的

```c++
#include <cstdio>
#include <iostream>

union myun {
  struct {
    int x;
    int y;
    int z;
  } u;
  int k;
} a;

union t1 {
  int a1;
  double a2;
  char a3;
};

int main() {
  a.u.x = 4;
  a.u.y = 5;
  a.u.z = 6;
  a.k = 0;
  printf("%d %d %d\n", a.u.x, a.u.y, a.u.z); // 0 5 6
  // 首先，union会按照最大的结构对象来确立地址空间
  // 其次，后面给k赋值的时候，会把k的值赋到原来x的位置
  // 所以就是0 5 6

  std::cout << sizeof(t1) << std::endl; // 8
  return 0;
}
```

<br/>

<br/>

<br/>

# 特点

- 不能具有定义了构造函数、析构函数或赋值操作符的类类型的成员
- 不能具有静态数据成员或引用成员
- 不能作为基类使用，所以成员函数不能为虚函数
- 共用体占用的内存等于最长的成员占用的内存

  - 共用体使用了内存覆盖技术，同一时刻只能保存一个成员的值，如果对新的成员赋值，就会把原来成员的值覆盖掉