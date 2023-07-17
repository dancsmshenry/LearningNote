```cpp
#include <iostream>
#include <memory>

template<typename T>
T sub(T& a, T& b) {
    return a - b;
}

const int (*pfun1)(const int& a, const int& b);
const int (*pfun2)(int& a, int& b);
int (*pfun3)(const int& a, const int& b);
int (*pfun4)(int& a, int& b);

int main () {
    // pfun1 = sub<int>;// error
    // pfun2 = sub<int>;// error
    // pfun3 = sub<int>;// error
    pfun4 = sub<int>;   
}
```

<br/>

说明了一点，函数模板必须每个数据都要对的上才可以（比如说const等）

<br/>

**函数模板的重载**受一些条件局限

```c++
template<typename T>
T v1(T t1, T t2) {}

template<typename T>
T v1(T t1, T t2, T t3) {}

//	只能这样的方式实现重载..
//	而原来的重载，是可以通过函数类型的不同来实现的（模板就会有点局限..）

template<typename T>
void v1(T t1, T t2, int t3) {std::cout << "int" << std::endl;}

template<typename T>
void v1(T t1, T t2, T t3) {std::cout << "T" << std::endl;}
// 比如说这种重载，遇到v1(1,2,3);就会出问题.
```

<br/>

https://blog.csdn.net/ThinPikachu/article/details/107427257

<br/>

模板的一个缺点：会导致代码膨胀

<br/>

```c++
templete<typename T>
using t1 = typename shape<T>::t1;
// 这里的 typename 主要是为了强调 t1 是一个类型（因为不强调的话，可能编译器会认为它是一个函数）

std::decay<R>::type;;
// 用于将 R 类型的 const，引用等属性给删除掉
```

