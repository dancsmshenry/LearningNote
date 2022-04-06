```cpp
typedef int INTINT;//将int定义为INTINT
typedef unsigned int UINT;//同上

typedef void (*voidfunc)(int a, int b)//定义一个函数指针，用于回调函数
    
typedef decltype(func) Func2  // Func2是函数类型；
typedef decltype(func) *Func2P // Func2是函数指针类型；
```



```cpp
#define pstr2 char*;//将代码中的pstr2变为char*，但是会有很大的问题
pstr2 c1, c2;
char *c1, c2;//上面一句话就等价于这个了.....

typedef char* pstr3;
pstr3 c1, c2;
char *c1, *c2;//上面一句话等价于这个
```

https://blog.csdn.net/liitdar/article/details/80069638



```cpp
typedef void (* FUN_) (int, int);//有点模糊
using FUN_ = void(*)(int, int);//简洁明了

using namespace std;

template<typename T, int C>
class A {
    T i;
    int a = C;
};

template<typename T>
using B = A<T, 6>;
B<int> a1;

using F = int(int*, int);
using PF = int(*)(int*,int);
F  f1(int);    //错误： F是函数类型
PF  f1(int);   //正确： PF是函数指针类型
```

https://www.jianshu.com/p/6ecfd541ec04





## 3、宏定义、函数、typedef和const的区别

- 宏定义属于在结构中插入代码，没有返回值；函数调用具有返回值

- 宏定义的参数没有类型，不进行类型检查；函数参数具有类型，需要检查类型

- 宏是在预处理时完成替换的，等价于直接插入代码，执行较快；函数调用在运行时需要跳转到具体调用的函数

- 宏用于定义常量以及书写复杂的内容， typedef 主要用于定义类型别名

- 宏发生在预处理阶段， typedef 是编译的一部分

- 宏不检查类型，typedef会检查数据类型

- 宏不是语句，不在最后加分号， typedef 是语句，要加分号标识结束

- 宏没有作用域的限制， typedef 有自己的作用域

- 巨坑：

  - ```cpp
    #define INTPTR1 int*
    
    typedef int* INTPTR2;
    
    INTPTR1 p1, p2;//声明一个指针变量p1和一个整型变量p2
    
    INTPTR2 p3, p4;//声明两个指针变量p3、p4
    ```

- 宏定义是在编译的预处理阶段起作用，const 是在编译、运行的时候起作用

- 宏定义只做替换，不做类型检查和计算，const 常量有数据类型，编译器可以对其进行类型安全检查

- 宏定义不需要分配内存空间，只是替换掉，const 定义的变量只是值不能改变，但要分配内存空间

- 宏定义是将宏名称进行替换，在内存中会产生多分相同的备份，const 在程序运行中只有一份备份， 且可以执行常量折叠，能将复杂的的表达式计算出结果放入常量表



宏在编译时完成替换，之后被替换的文本参与编译，相当于直接插入了代码，运行时不存在函数调 用，执行起来更快；函数调用在运行时需要跳转到具体调用函数。 宏定义属于在结构中插入代码，没有返回值；函数调用具有返回值。 宏定义参数没有类型，不进行类型检查；函数参数具有类型，需要检查类型。 宏定义不要在最后加分号





宏主要用于定义常量及书写复杂的内容；typedef主要用于定义类型别名。 宏替换发生在编译阶段之前，属于文本插入替换；typedef是编译的一部分。 宏不检查类型；typedef会检查数据类型。 宏不是语句，不在在最后加分号；typedef是语句，要加分号标识结束。 注意对指针的操作，typedef char * p_char和#define p_char char *区别巨大。



# define

与函数相比





# using



# typedef



# using
