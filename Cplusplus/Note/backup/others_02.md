# 为什么stl的扩容没有用到移动构造

- 可以发现 `std::vector` 的move构造函数并没有采用 `std::move`，而是调用的copy构造函数
- 因为移动构造意味着所有权的变更，因此在移动构造的过程中，如果出现了异常，那么原始数据很有可能是无法恢复的
- 而拷贝构造就不一样了，即使产生了异常，原始数据还是存在的。这也是 STL 中的设计思路之一







# back()

- ```cpp
  typedef typename _Alloc_traits::reference		reference;
  reference
  back() _GLIBCXX_NOEXCEPT
  {
  __glibcxx_requires_nonempty();
  return *(end() - 1);
  }
  ```

- back返回的是对象元素的引用
- 如果被引用的对象析构或消失了，那么这就是一个空引用...







# stl容器不能用memset

- 不要用memset对容器进行清空初始化，因为容器的内部结构很复杂，必定codedump，从而后续造成内存泄漏
- 比如说，vector中有其自身的结构，不能单纯的按字节进行初始化。使用memset对vector进行初始化，会破坏vector中的结构，造成vector中的数据错误







# 不要继承stl容器

- 它们的析构函数都不是虚析构，多态的情况下会内存泄漏







# 萃取

- traits运用显式模板特殊化将代码中因为类型不同而发生变化的片段提取出来，用统一的接口来包装，并通过traits模板类公开的接口间接访问相应的类

- traits中文意思是特性，它通过提取不同类的共性，使得可以统一处理

- ```cpp
  #include <iostream>
  using namespace std;
  
  //①基本类写法
  class IntArray
  {
  public:
      IntArray()
      {
          a = new int[10];
          for (int i = 0; i < 10; ++i)
          {
              a[i] = i + 1;
          }
      }
      ~IntArray()
      {
          delete[] a;
      }
  
      int GetSum(int times)
      {
          int sum = 0;
          for (int i = 0; i < 10; ++i)
              sum += a[i];
          cout << "int sum=" << sum << endl;
          return sum * times;
      }
  
  private:
      int *a;
  };
  class FloatArray
  {
  public:
      FloatArray()
      {
          f = new float[10];
          for (int i = 1; i <= 10; ++i)
          {
              f[i - 1] = 1.0f / i;
          }
      }
      ~FloatArray()
      {
          delete[] f;
      }
      float GetSum(float times)
      {
          float sum = 0.0f;
          for (int i = 0; i < 10; i++)
              sum += f[i];
          cout << "float sum=" << sum << endl;
          return sum * times;
      }
  
  private:
      float *f;
  };
  //②模板写法
  template <class T>
  class Apply
  {
  public:
      float GetSum(T &t, float inarg)
      {
          return t.GetSum(inarg);
      }
  };
  
  //以上方法不能完全解决我们的问题(函数返回值固定，就会导致异常)
  //③采用萃取机制：模板特化
  template <class T>
  class NumTraits
  {
  };
  //模板特化的格式
  template <>
  class NumTraits<IntArray>
  {
  public:
      typedef int resulttype;
      typedef int inputargtype;
  };
  template <>
  class NumTraits<FloatArray>
  {
  public:
      typedef float resulttype;
      typedef float inputargtype;
  };
  template <class T>
  class Apply2
  {
  public:
      NumTraits<T>::resulttype GetSum(T &obj, NumTraits<T>::inputargtype inputarg)
      {
          return obj.GetSum(inputarg);
      }
  };
  int main()
  {
      IntArray intary;
      FloatArray floatary;
      Apply<IntArray> ai;   //采用模板
      Apply<FloatArray> af; //采用模板
      cout << "1整型数组的和3倍：" << ai.GetSum(intary, 3) << endl;
      cout << "1浮点数组的和3.2倍：" << af.GetSum(floatary, 3.2f) << endl;
      cout << endl;
      cout << endl;
      Apply2<IntArray> ai2;   //采用萃取
      Apply2<FloatArray> af2; //采用萃取
      cout << "2整型数组的和3倍：" << ai2.GetSum(intary, 3) << endl;
      cout << "2浮点数组的和3.2倍：" << af2.GetSum(floatary, 3.2f) << endl;
      return 0;
  }
  ```

- 即利用模板把数据特化出来，并提供统一名称类型的接口，方便用户使用

- https://zhuanlan.zhihu.com/p/358113531



- 由此引申出的有关typename的问题：如果要引用别的类里面的类型（因为类是一个作用域，就相当于要用A::value_type的话），就必须在其前面加上一个typename，因为编译器不能判断你说的这个到底是什么类型，所以要加上一个关键词告诉编译器这是一个型别，如此才能顺利通过编译





- 利用typedef和模板的偏特化，实现对类型的提取

- ```cpp
  template<class T>
  struct iterator_traits{
      typedef typename T::value_type value_type;
  }
  
  template<class I>
  typename iterator_traits<I>::value_type test() {}
  //	利用模板和内嵌型别就把当前I中的value_type给提取出来，作为返回值了
  
  template<class T>
  struct iterator_traits<T*>{ // 模板的偏特化
      typedef T value_type; // 这里可能会萃取出const
  } // 可以方便的提取原生指针的类型
  
  template<class T>
  struct iterator_traits<const T*> {
      typedef T value_type; // 这里就不会萃取出const，直接得到T
  }
  ```



- 对于萃取的理解
  - 提取一个类中我们想要的类型
  - 概念很简单，但是运用起来很复杂，参考stl的关于traits的讲述



使用 accumulate 可以计算求和， max_element 求最大值

```C++
#include "numeric"

std::vector<int> vec(10, 10);
auto sum = std::accumulate(vec.begin(), vec.end(), 0);

auto itmax = std::max_element(vec.begin(), vec.end()); // return iterator
```



# 运算符计算顺序

- 运算符的优先级，记忆口决：“单算移关与，异或逻条赋” 

  单：单目运算符，自增（++）、自减（--）、逻辑非（！）、按位反（~）、取地址（&）、取值（*） 

  算：算术运算符，乘(*)、除(/)、求余(%)级别高于加(+)、减(-) 

  移：移位运算符，按位左移(<<)、按位右移(>>) （7 >> 1得到的结果是3，所以就等价于是除二）

  关：关系运算符，小于(<)、大于(>)、大于等于(>=)、小于等于(<=) 高于 等于(==)、不等于(!=) 

  与：按位与运算符(&) 

  异：按位异或运算符(^) 

  或：按位或运算符(|) 

  逻：逻辑运算符，逻辑与(&&)高于逻辑或(&&) 

  条：条件运算符(?:) 

  赋：赋值运算符(*=、/=、%=、+=、-=、<<=、>>=、&=、^=、|=、!=、=)

- ```cpp
  	int b = 10, a = 3;
  	b += b *= b %= a ++ ;
  	std::cout << "b = " << b << " a = " << a << std::endl; 
  // b = 2 a = 4
  ```

- &的作用是将两个数字进行逐位逐位的进行&运算

- 不能重载的运算符：

  - 1、条件运算符“?:”；

  - 2、成员访问运算符“.”；

  - ```cpp
    class Y{
       public:
          void fun();
    };
    class X{
       public:
          Y* p;
          Y& operator.(){
              return *p;
          }
          void fun();
    }
    void g(X& x){
          x.fun(); // 这里就不清楚到底调用的是哪一个fun函数了....
    }
    ```

  - 3、域运算符“::”；

  - 4、长度运算符“sizeof”；（不能被重载的原因主要是内部许多指针都依赖sizeof）

  - 5、成员指针访问运算符“->*”和“.*”










# 语言之间的区别

## C++和Python

- Python是一种脚本语言，是解释执行的，而C++是编译语言，是需要编译后在特定平台运行的。 
- python可以很方便的跨平台，但是效率没有C++高。 
- Python使用缩进来区分不同的代码块，C++使用花括号来区分 
- C++中需要事先定义变量的类型，而Python不需要，Python的基本数据类型只有数字，布尔值，字符 串，列表，元组等等 
- Python的库函数比C++的多，调用起来很方便



## C++和C

- C++中new和delete是对内存分配的运算符，取代了C中的malloc和free。 
- 标准C++中的字符串类取代了标准C函数库头文件中的字符数组处理函数（C中没有字符串类型）。 
- C++中用来做控制态输入输出的iostream类库替代了标准C中的stdio函数库。 
- C++中的try/catch/throw异常处理机制取代了标准C中的setjmp()和longjmp()函数。 
- 在C++中，允许有相同的函数名，不过它们的参数类型不能完全相同，这样这些函数就可以相互区别 开来。而这在C语言中是不允许的。也就是**C++可以重载，C语言不允许**。 
- C++语言中，允许变量定义语句在程序中的任何地方，只要在是使用它之前就可以；而C语言中，必 须要在函数开头部分。而且C++允许重复定义变量，C语言也是做不到这一点的 
- 在C++中，除了值和指针之外，新增了引用。引用型变量是其他变量的一个别名，我们可以认为他们 只是名字不相同，其他都是相同的。 
- C++相对与C增加了一些关键字，如：bool、using、dynamic_cast、namespace等等
- C不支持函数重载



## C++和Java

语言特性 

Java语言给开发人员提供了更为简洁的语法；完全面向对象，由于JVM可以安装到任何的操作系统 上，所以说它的可移植性强 Java语言中没有指针的概念，引入了真正的数组。不同于C++中利用指针实现的“伪数组”，Java引入 了真正的数组，同时将容易造成麻烦的指针从语言中去掉，这将有利于防止在C++程序中常见的因为 数组操作越界等指针操作而对系统数据进行非法读写带来的不安全问题 C++也可以在其他系统运行，但是需要不同的编码（这一点不如Java，只编写一次代码，到处运 行），例如对一个数字，在windows下是大端存储，在unix中则为小端存储。Java程序一般都是生成 字节码，在JVM里面运行得到结果 Java用接口(Interface)技术取代C++程序中的抽象类。接口与抽象类有同样的功能，但是省却了在实现 和维护上的复杂性 

垃圾回收 

C++用析构函数回收垃圾，写C和C++程序时一定要注意内存的申请和释放 Java语言不使用指针，内存的分配和回收都是自动进行的，程序员无须考虑内存碎片的问题 

应用场景

 Java在桌面程序上不如C++实用，C++可以直接编译成exe文件，指针是c++的优势，可以直接对内存 的操作，但同时具有危险性 。（操作内存的确是一项非常危险的事情，一旦指针指向的位置发生错 误，或者误删除了内存中某个地址单元存放的重要数据，后果是可想而知的） Java在Web 应用上具有C++ 无可比拟的优势，具有丰富多样的框架 对于底层程序的编程以及控制方面的编程，C++很灵活，因为有句柄的存在







# Cpp为什么没有垃圾回收机制

- 实现一个垃圾回收器会带来额外的空间和事件的开销
  - 需要空间保存指针的引用计数和对他们进行标记mark，还需要开一个线程在空闲的时候进行free
- 使得cpp不能进行很多底层的操作





# CPP标准库有哪些

- 标准函数库： 这个库是由通用的、独立的、不属于任何类的函数组成的。函数库继承自 C 语言
- 面向对象类库： 这个库是类及其相关函数的集合
- 输入/输出 I/O、字符串和字符处理、数学、时间、日期和本地化、动态分配、其他、宽字符函数
- 标准的 C++ I/O 类、String 类、数值类、STL 容器类、STL 算法、STL 函数对象、STL 迭代器、STL  分配器、本地化库、异常处理类、杂项支持库







# c与cpp接口间互相调用

- https://blog.csdn.net/lincoln_2012/article/details/50801080

- `int (&b)[10] = a;`是什么？`int a[10];`又是什么？（mark:https://blog.csdn.net/qq_34988341/article/details/106452518）

- 在群里面看到的代码：

  - ```cpp
    static char_type* copy(char_type* dst, const char_type* src, size_t n){//拷贝的过程要注意内存重叠的问题
        assert(src + n <= dst || dst + n <= src);
        char_type* r = dst;
        for (; n != 0; -- n, ++ dst, ++ src){
            *dst = *src;
        }
        
        return r;
    }
    ```

  - 内存拷贝的四种情况：

  - 第一种：dst  空格空格  src

  - 第二种：src 空格空格 dst

  - 第三种：dst src（src的有一部分是和dst重合的），那么，此时从前往后复制的时候，也不会影响

  - 第四种：src dst（dst的有一部分是和src重合的），那么，此时从前往后复制，就会把src后面的一部分给覆盖掉，导致两个内存的内容不同

  - 参考c的库函数memmove()





# 大小写转换

- tolower，toupper





# 重载运算符

- 只能重载已有的运算符；对于一个重载的运算符，其优先级和结合律与内置类型一致才可以；不能改变运算符操作数个数

- 两种重载方式：

  - 成员运算符和非成员运算符，成员运算符比非成员运算符少一个参数（this）
  - 下标运算符、箭头运算符必须是成员运算符

- 当重载的运算符是成员函数时，this绑定到左侧运算符对象；成员运算符函数的参数数量比运算符对象的数量少一个

- 下标运算符必须是成员函数，下标运算符通常以所访问元素的引用作为返回值，同时最好定义下标 运算符的常量版本和非常量版本

- 箭头运算符必须是类的成员，解引用通常也是类的成员；重载的箭头运算符必须返回类的指针

- 重载+号

  - ```cpp
    class Person
    {
    public:
    	int m_a;
    	int m_b;
     
    	//成员函数的加号重载；
    	Person operator+(Person& p)
    	{
    		Person pt;
    		pt.m_a = m_a + p.m_a;
    		pt.m_b = m_b + p.m_b;
    		return pt;
            //	等价于p3 = p1.operator+(p2);
    	}
    };
    
    int operator+(Person& p1, Person& p2) {
        //	全局函数实现+号的重载
        //	等价于p3 = operator+(p1 ,p2);
    }
    
    class point
    {
    public:
        point(int a, int b):x(a), y(b){}
        point& operator++()   // 前置++
        {
            x++;
            y++;
            return *this;
        }
        point operator++(int) //后置++ 
        {
            point a = *this;
            // 或者++a;
            a.x++;
            a.y++;
            return a;
        }
    
    private:
        int x;
        int y;
    };
    
    Person p1, p2, p3 = p1 + p2;
    ```








# switch 的底层实现

 C++ 代码到可执行文件的过程。可执行文件执行的过程





# 头文件<>和""的区别

- #include<>：编译器直接从系统类库目录里查找头文件： 
- \#include""：默认从项目当前目录查找头文件，所谓项目当前目录，就是项目工程文件（.vcxproj）所在的目录。如果在项目当前目录下查找失败，再从**项目配置的头文件引用目录**查找头文件，所谓项目配置的引用目录，就是我们在项目工程中设置的头文件引用目录。如果项目配置的头文件引用目录中仍然查找失败，再从**系统类库目录**里查找头文件



# 如何防止头文件被重复引用

- ```cpp
  #ifndef __INCvxWorksh  /*防止该头文件被重复引用*/
  #define __INCvxWorksh
  
  #ifdef __cplusplus    //__cplusplus是cpp中自定义的一个宏
  extern "C" {          //告诉编译器，这部分代码按C语言的格式进行编译，而不是C++的
  #endif
  
      /**** some declaration or so *****/  
  
  #ifdef __cplusplus
  }
  #endif
  
  #endif /* __INCvxWorksh */
  ```



# 模板类为什么都放在h文件中

- 原因1：
  - 模板定义很特殊。由template<…>处理的任何东西都意味着编译器在当时不为它分配存储空间，它一 直处于等待状态直到被一个模板实例告知。在编译器和连接器的某一处，有一机制能去掉指定模板的多 重定义
  - 所以为了容易使用，几乎总是在头文件中放置全部的模板声明和定义
- 原因2：
  - 在分离式编译的环境下，编译器编译某一个.cpp文件时并不知道另一个.cpp文件的存在，也不会去查 找（当遇到未决符号时它会寄希望于连接器）。这种模式在没有模板的情况下运行良好，但遇到模板时 就傻眼了，因为模板仅在需要的时候才会实例化出来。
  - 所以，当编译器只看到模板的声明时，它不能实例化该模板，只能创建一个具有外部连接的符号并期待 连接器能够将符号的地址决议出来 
  - 然而当实现该模板的.cpp文件中没有用到模板的实例时，编译器懒得去实例化，所以，整个工程的.obj中 就找不到一行模板实例的二进制代码，于是连接器也黔驴技穷了



# 其他

- java里面没有全局变量，好像是过程式语言中才有吗？？但是python也有啊
- 理解了.h文件的真正含义了，就是在预编译的时候把.h文件的内容全部加到源文件里面，生成一个名为.i的文件
  - 所以，很多接口（函数的定义）都是放到.h文件里面





# 组合与继承

继承

- 优点：
  - 子类可以重写父类的方法来方便地实现对父类的拓展
- 缺点：
  - 父类内部细节对子类是可见的
  - 子类从父类继承的方法在编译时就确定下来了，所以无法在运行期间改变从父类继承的方法的行为
  - 如果对父类的方法做了修改，则子类的方法必须做出相应的修改
  - 父子类高度耦合



组合

- 优点：
  - 当前对象只能通过所包含的那个对象去调用其方法，所以所包含的对象的内部细节对当前对象时不 可见的
  - 当前对象与包含的对象是一个低耦合关系，如果修改包含对象的类中代码不需要修改当前对象类的代码
  - 当前对象可以在运行时动态的绑定所包含的对象。可以通过set方法给所包含对象赋值
- 缺点：
  - 容易产生过多的对象
  - 为了能组合多个对象，必须仔细对接口进行定义





## 数组的访问

- ```cpp
      float a[2][2] = {{1.0, 2.0}, {3.0, 4.0}};
      std::cout << *(a[0] + 1) << std::endl; // ok，2
      std::cout << *(*(a + 1) + 1) << std::endl; // ok，4
      std::cout << *(a + 1 * 2 + 1) << std::endl; // error，输出的是地址
  ```





## 数组的传参

- ```cpp
  void foo1(int arr[][]) {} // error
  
  void foo2(int arr[4][]) {} // error
  
  void foo3(int arr[][4]) {} // ok
  
  void foo4(int arr[3][4]) {} // ok
  ```





## 字符串数组的读取

```c++
void ff() {
    char *say[] = {"ai", "bello", "cey"};
    char **  p = say;
    std::cout << *p + 1 << std::endl; // 读到第一个字符串的第二个字母
    std::cout << *(p[1]  + 1)<< std::endl; // 读到第二个字符串的第二个字母
    std::cout << *(p + 1) << std::endl; // 读到第二个字符串
    std::cout << ** ++ p << std::endl; // 读到第二个字符串的第一个字母
    float a[2][2] = {{1.0, 2.0}, {3.0, 4.0}};
  	std::cout << *(a[0] + 1) << std::endl;      // ok，2
  	std::cout << *(*(a + 1) + 1) << std::endl;  // ok，4
  	std::cout << *(a + 1 * 2 + 1) << std::endl; // 输出的是地址
}


```







# strncpy

将src的开头的n个字符，复制到dest的位置

```cpp
//	dest为目标数组，src为源数组，n为要复制字符的个数
char* strncpy_t(char* dest, const char* src, int n) {
	assert(dest != NULL);	//	保证dest非空
	assert(src != NULL);	//	保证src非空
	char* ret = dest;	//	将dest首地址储存在ret中，在之后dest++运算中，可以方便找到
	while (n) {	//	一次复制一个字符，要复制n次
		*dest = *src;	//	复制
		++ src;    //	源地址往后+1
		++ dest;   //	目标地址往后+1
		-- n;      //	跳出循环条件
	}
	return ret;	//	返回目的数组的首地址
}
```

<br/>

<br/>

<br/>

# split

将字符串按照分割符spacer分隔开

```cpp
//	str为原字符串，v为结果，spacer为分隔符
void split(string str, vector<string> &v, string spacer) {
    int pos1, pos2;
    int len = spacer.length();     //记录分隔符的长度
    pos1 = 0;
    pos2 = str.find(spacer);
    while(pos2 != string::npos) {
        v.push_back(str.substr(pos1, pos2 -pos1));
        pos1 = pos2 + len;
        pos2 = str.find(spacer, pos1);    // 从str的pos1位置开始搜寻spacer
    }
    if(pos1 != str.length()) {//分割最后一个部分
    	v.push_back(str.substr(pos1));
    }
}

```

<br/>

<br/>

<br/>

# strcpy

将src的所有字符，copy到dest上

```cpp
char* my_strcpy(char* dest, const char* src) {
    assert(dest && src);

    char *res = dest;
    while (*src != '\0') {
        *dest = *src;
        ++ dest;
        ++ src;
    }

    return res;
}
```

<br/>

<br/>

<br/>

# memcpy

```cpp
void* memcpy(void *dest, const void *src, size_t count) {
    if (dest == NULL || src == NULL || dest <= src + count) {
        return NULL;
    }

    char *tmp_dest = dest;
    const char *tmp_src = src;

	//	while (count--) *tmp_dest++ = *tmp_src++;
    while (count) {
        -- count;
        *tmp_dest = *tmp_src;
        tmp_dest = (char*)tmp_dest + 1;
        tmp_src = (char*)tmp_src + 1;
    }

    return dest;
}
```



# 大小端转换

```cpp
#include <stdio.h>
 
int main()
{
    int a = 1, result;
    result = ((a & 0x000000ff) << 24) |
             ((a & 0x0000ff00) << 8)|
             ((a & 0x00ff0000) >> 8)|
             ((a & 0xff000000) >> 24);
    printf("%d\n", result);
 
    return 0;
}
```





# 字典树

```cpp
class TrieNode{
    public:
        TrieNode* next[26];
        bool isval;
        TrieNode(){
            for (int i = 0; i < 26; i ++ ){
                next[i] = nullptr;
            }
            isval = false;
        }
};

class Trie {
public:
    TrieNode* root;

    Trie():root(new TrieNode) {}
    
    void insert(string word) {
        TrieNode* p = root;
        for (const char& i: word){
            if (p -> next[i - 'a'] == nullptr){
                p -> next[i - 'a'] = new TrieNode();
            }
            p = p -> next[i - 'a'];
        }
        p -> isval = true;
    }
    
    bool search(string word) {
        TrieNode* p = root;
        for (const char& i: word){
            if (p -> next[i - 'a']){
                p = p -> next[i - 'a'];
            }else{
                return false;
            }
        }

        return p -> isval;
    }
    
    bool startsWith(string prefix) {
        TrieNode* p = root;
        for (const char& i: prefix){
            if (p -> next[i - 'a']){
                p = p -> next[i - 'a'];
            }else{
                return false;
            }
        }
        return true;
    }
};
```



# string类的实现





# LRU

```cpp
struct Node {
    int key;
    int value;
    Node *prev;
    Node *next;
    Node(): key(0), value(0), prev(nullptr), next(nullptr) {}
    Node(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    unordered_map<int, Node*> cache;
    Node *head;
    Node *tail;
    int size;
    int capacity;

public:
    LRUCache(int _capacity): capacity(_capacity), size(0) {
        head = new Node();
        tail = new Node();
        head -> next = tail;
        tail -> prev = head;
    }

    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }

        Node *node = cache[key];
        move_to_head(node);
        
        return node -> value;
    }

    void put(int key, int value) {
        if (!cache.count(key)) {
            Node *node = new Node(key, value);
            cache[key] = node;
            add_to_head(node);
            ++ size;
            if (size > capacity) {
                Node *removed = remove_tail();
                cache.erase(removed -> key);
                delete removed;
                -- size;
            }
        } else {
            Node *node = cache[key];
            node -> value = value;
            move_to_head(node);
        }
    }
    
    void add_to_head(Node *node) {
        node -> next = head -> next;
        node -> prev = head;
        head -> next -> prev = node;
        head -> next = node;
    }

    void remove_node(Node *node) {
        node -> prev -> next = node -> next;
        node -> next -> prev = node -> prev;
    }

    void move_to_head(Node *node) {
        remove_node(node);
        add_to_head(node);
    }

    Node* remove_tail() {
        Node* node = tail -> prev;
        remove_node(node);
        return node;
    }
};
```





# 字符串相乘

```cpp
class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }
        if (num2.length() > num1.length()) {
            return multiply(num2, num1);
        }

        vector<int> res(num1.size() + num2.size(), 0);
        string result = "";
        for (int i = num2.size() - 1; i >= 0; -- i) {
            int count{};
            for (int j = num1.size() - 1; j >= 0; -- j) {
                int index = num2.size() - i + num1.size() - j - 2;
                res[index] = res[index] + count + (num1[j] - '0') * (num2[i] - '0');
                count = res[index] / 10;
                res[index] %= 10;
            }
            res[num2.size() - i - 1 + num1.size()] += count;
        }

        while (res.back() == 0) res.pop_back();
        for (int i = res.size() - 1; i >= 0; -- i) {
            result += to_string(res[i]);
        }

        return result;        
    }
};
```

<br/>

<br/>

# 代码结构

今天在代码上看到这样的文件结构：

假设有接口类（纯虚函数类）interfaceA，其具体的实现类 interfaceAimpl

对于二者的头文件，interfaceA 的头文件被设置为了 public 属性

而 interfaceAimpl 被设为了 private 属性

对于上述编译得到的库，用户需要必然是引入头文件和编译代码库

用户引入的头文件为 interfaceA，而对于代码库提供的其他接口函数

该接口函数规定的返回值类型为 interfaceA，而实际返回的值却是 interfaceAimpl

一开始看感觉就很像 pimpl，但是又不是，以下是我的理解：

如果具体的实现类对象以及其实现可能会经常改动（但提供的接口功能，函数签名和入参必然是不会变的），那么就可以将具体的实现隐藏起来，用户只需引入接口类，接着编译的代码库再返回具体的实现类（多态）

从而避免因实现类的频繁修改导致编译时间变长

<br/>

一个需要验证的问题：一个 .cc 文件的匿名空间的对象，在和其他的 .cc 文件一起编译为一个编译单元时，这个匿名对象是否可以被看见（按理说是看不见的）

<br/>

<br/>

# 关于回调函数的认识

对于回调函数的部分理解：

在网络编程中的 IO 一般都是用 非阻塞 IO 加上 epoll，所以如果在使用者的角度

我们希望的是读到了数据，就去执行相对应的逻辑，

一开始的想法是，网络编程的逻辑是 socket bind listen accept，最后读数据

但是现在使用了非阻塞 IO ，那么最后读到数据的时机就由不得用户控制（比如 epoll 监控了 1000ms，都没有发现有数据，那么此时用户就不应该读数据；或者 epoll 监控了 1s，就有数据可读了）

因此库的设计者，需要一种方式，将使用者给定的逻辑嵌入到网络库中，这种方式就是回调函数

所以说是有些地方是用户层面不可控的，所以要设置为回调？

看 dds 的网络绑定层的代码，对于接收数据的函数逻辑，都是注册回调来实现的

但有个问题就是为什么 startfindservice 这里也要注册一个回调函数？

我这里理解，是因为用户同时可以部署多个 instance，而需要在回调中决定使用哪一个 instance



# 如何实现只能静态分配和只能动态分配

- 背景：
  - 静态创建：静态建立一个类对象，就是由编译器为对象在栈空间中分配内存
  - 动态创建：A *p = new A();动态建立一个类对象，就是使用new运算符为对象在堆空间中分配内存。 这个过程分为两步，第一步执行operator new()函数，在堆中搜索一块内存并进行分配；第二步调用类构造函数构造对象
- 只能静态分配：把new和delete运算符重载为privated属性（只有使用new运算符，对象才会被创建在堆上，因此只要限制new运算符就可以实现类对象只能建立在栈上，即把new运算符设为私有）
- 只能动态分配：把构造、析构函数设为protected属性，再用子类动态创建







# 继承下对象的转换

- 向上类型转换
  - 将派生类指针或引用转换为基类的指针或引用被称为向上类型转换
  - 向上类型转换会自动进行，**向上类型转换是安全的**
- 向下类型转换
  - 将基类指针或引用转换为派生类指针或引用被称为向下类型转换
  - 向下类型转换不会自动进行，因为一个基类对应几个派生类，所以向下类型转换时不知道对应哪个派生类，所以在向下类型转换时必须加动态类型识别技术（RTTI技术，用dynamic_cast进行向下类型转换）
  - 因为父子类的结构不一样，可能子类有多个虚函数指针，强转导致数据出错，**向下类型转换是不安全的**







# 空类默认提供的函数

- ```cpp
  A(); //默认构造函数
  ~A(); //默认析构函数
  A（const A&); //默认拷贝构造函数
  A& operator=(const A &); //默认赋值函数。
  ```

- 析构函数

- 拷贝构造函数

  - 如果是A a1(b1)这种，而类里面都是一般属性（比如int，long等，或是没有定义拷贝函数的class），那就不会构造拷贝函数，而是直接值拷贝过去
  - 而如果有string之类的成员，那么就会调用拷贝构造，去调用对应的拷贝构造函数

- 缺省构造函数

- 赋值运算符







# 如何阻止类被拷贝

- 本质上就是组织用户调用copy构造函数和=运算符
- 可以将copy构造函数和=运算符设为private，防止被调用（但缺点就是friend函数对象，或是类的成员函数可以调用）
  - 而如果只声明不定义，就会有链接错误
- 因此最佳解是定义一个base类，在base类中将拷贝构造函数和拷贝赋值函数设置成private，那么派生类中编译器将不会自动生成这两个函数

- 当然也可以用cpp11的关键字delete，直接=delete即可







# 如何阻止类被实例化

- 将类定义为抽象基类或者将构造函数声明为private







# 如何阻止类被继承

## 方法一

- ```cpp
  class B;
  //设计一个不能被继承的类
  class A
  {
         friend B;
  private:
         A() {}
  };
  class B :virtual public A
  {
  public:
         B() {}
  };
  ```

- 我们可以声明一个辅助的类A，把类A的构造函数声明为私有的，并使得B是A的友元类，且B虚继承A。让B是A的友元类的目的在于能够让B访问A的私有构造函数，这样继承自A的B才可以被实例化

- 假设现在有一个类D继承B，在D初始化的时候会先调用B类的构造函数，但是由于B虚继承A，所以为了防止产生二义性，D必须先调用A的构造函数，由于A的构造函数是私有的不可访问，所以会产生错误，继承会失败



## 方法二

- ```cpp
  class CParent
  {
  private:
      CParent(int v){m_v = v;}
      ~CParent(){}
  
      int m_v;
      static CParent * m_instance;
  public:
      static CParent * getInstance(int v);
  };
  
  CParent *CParent::getInstance(int v)
  {
      return new CParent(v);
  }
  ```

- 相当于写一个单例模式吧



## 方法三

- cpp11中的final修饰符







# 如何统计一个类生成的个数

- 为类设计一个static静态变量count作为计数器
- 类定义结束后初始化count
- 对于默认构造函数，拷贝构造函数，复制构造函数，移动拷贝构造函数，在进行上述函数时进行count+1操作
- 在析构函数中对count进行-1







# 成员函数的调用过程

- ```cpp
  #include <iostream>
  
  class A {
  public:
      void test() {
          std::cout << "hello" << std::endl;
          //std::cout << i << " " << std::endl;
      }
      int i{};
  };
  
  int main() {
      A *a1 = nullptr;
      a1 -> test();
  }
  ```

- 如果注释掉了i的那一行，代码可以运行吗，可以的

- 先了解一下成员函数是如何调用的，成员函数的调用本质上会加上一个对象的指针进去的，即this指针

- 换句话说，如果函数里面没有触及这个this指针，那么即使this为nullpr，也是可以运行的







# trivial函数，standard-layout和POD

https://zhuanlan.zhihu.com/p/479755982

背景

- ```cpp
  class A
  {
  public:
      // ...
      A() {}          // 定义一个空的默认构造函数
      A() = default;  // 主动让编译器生成默认构造函数
      // ...
  };
  ```

- 这两种构造函数有何区别



trivial type的定义

- 没有虚函数或虚基类
- 由编译器生成默认的特殊成员函数，包括默认构造函数、拷贝构造函数、移动构造函数、赋值运算符、移动赋值运算符和析构函数
- 数据成员同样需要满足上述两个条件



Standard Layout的定义

- 没有虚函数或虚基类

- 所有非静态数据成员都具有相同的访问说明符（`public` / `protected` / `private`）

- 在继承体系中最多只有一个类中有非静态数据成员。

- 子类中的第一个非静态成员的类型与其基类不同（具体的原因可以参考下面的博文）

  - 因为在cpp的标准里面，如果基类没有任何数据成员，基类应不占用空间，所以允许派生类的第一个成员与基类共享同一地址空间

  - 如果派生类的第一个成员和基类的类型相同，而cpp标准要求相同的类型不同的对象的地址必须有所区分，所以编译器就会为基类分派一个字节的地址空间

  - ```cpp
    #include <iostream>
    #pragma  pack(1)
    
    struct A
    {
    };
    
    struct B : A
    {
    	// A a; // 这样写大小为6
    	int i;
    	A a; // 这样写大小为5
    };
    
    struct C
    {
    };
    
    struct D : A
    {
    	C c;
    	int i;
    };
    
    int main()
    {
    	B b;
    	A &a1 = b;
    	// &b == &a1 == &b.a - 1
    	std::cout << &b << std::endl;
    	std::cout << &a1 << std::endl;
    	std::cout << &b.a << std::endl;
    	std::cout << sizeof(B) << std::endl;
    	std::cout << "-------------" << std::endl;
    
    	D d;
    	A &a2 = d;
    	// &d == &a2 == &d.c
    	std::cout << &d << std::endl;
    	std::cout << &a2 << std::endl;
    	std::cout << &d.c << std::endl;
    	std::cout << sizeof(D) << std::endl;
    }
    ```

  - 这就直接导致的结果是，同样是一个空类加上一个int，不同的排列方法会导致大小的不同

  - 探讨对象B的内存布局

  - 如果是先A a;，再int i;，那么编译器为了区分B和A，对象布局就是第一层用一个字节表示对象B，第二层用一个字节来区分表示对象A，第三层用四个字节表示对象int i，这样一共就用了6个字节

  - 而如果是先int i;，再A a;，那么编译器就不需要去区分B和A了，则对象布局时第一层用四个字节表示int i；，这里顺带也会用来表示对象B，然后第二层用一个字节表示对象A a，这样一共就用了5个字节

  - 而这里为什么对象D同样是把空类放到最前面，但是大小却依然是5，是因为对象C和对象D没有父子关系，即使再同一个地址编译器也能够区分

- 总结：一切都是因为cpp的标准说，相同类型的不同对象的地址必须不同，编译器为了实现，就为那个不同的对象分配一个字节的地址空间



plain old data的定义

- 代表一个对象是一个普通类型；Old 代表一个对象可以与 C 语言兼容
- 可以使用字节赋值，比如用 `memset`、`memcpy` 对 POD 类型对象进行赋值操作。
- 与 C 语言内存布局兼容，POD 类型的数据可以使用 C 函数进行操作且是安全的。
- 保证了静态初始化的安全有效







# 对面向对象的理解





# 父类调用子类函数

```c++
#include <iostream>

template <typename T>
class Base {
public:
  virtual ~Base() = default;
  virtual void fun() { std::cout << "Base::fun()" << std::endl; }

  void callChildMethod() { static_cast<T &>(*this).show(); }
};

class Sub : public Base<Sub> {
public:
  void fun() override { std::cout << "Sub::fun()" << std::endl; }

  virtual void show() { std::cout << "Sub::show()" << std::endl; }
};

int main() {
  Sub s1;
  std::cout << "s1.fun()--------------" << std::endl;
  s1.fun();
  std::cout << "s1.callChildMethod()----------" << std::endl;
  s1.callChildMethod();
}
```





# to do list

A继承自父类B和C，如果使用B的指针ptr1和C的指针ptr2同时指向一个A对象，则ptr1和ptr2的地址是否一致？（经过测试，是不一样的，但是有个问题就是如果A，B，C都是空类的话，那地址是不是一样的，答是不一样的，为啥？？）





# 关于多继承中函数调用的顺序

A

B->C（C 继承于 B）

C,A ->D（D 继承于 C A）

构造的调用顺序：先构造 B，再构造 C ，接着构造 A，最后构造 D

析构的调用顺序：先析构 D，再析构 A，接着析构 C，最后析构 B

构造和析构的顺序完全相反

```c++
class A {
public:
  A() { std::cout << "A()" << std::endl; }
  ~A() { std::cout << "~A()" << std::endl; }
};

class B {
public:
  B() { std::cout << "B()" << std::endl; }
  ~B() { std::cout << "~B()" << std::endl; }
};

class C : public B {
public:
  C() { std::cout << "C()" << std::endl; }
  ~C() { std::cout << "~C()" << std::endl; }
};

class D : public C, public A {
public:
  D() { std::cout << "D()" << std::endl; }
  ~D() { std::cout << "~D()" << std::endl; }
};

void test() {
  D d1;
}
// B()
// C()
// A()
// D()
// ~D()
// ~A()
// ~C()
// ~B()
```

有个问题：既然要隐藏实现，那为什么不直接写一个 .h 文件，然后把具体的一些实现函数放到 .cc 文件中，这样也可以实现只暴露规范提供的接口。问题一：外部实现函数无法访问 private 变量

在构造函数中，不要把 this 指针传递给别的函数，可以理解为不要注册回调（不是安全的），即使是在函数的最后一行

因为当前类可能会被其他类继承，而此时的 this 并没有构造完成

一个比较好的方式就是，构造函数+initialize 两段式构造

[muduo网络库:01---线程安全的对象生命期管理之(多线程中对象的构造与析构)_mb6128aabee41d4的技术博客_51CTO博客](https://blog.51cto.com/u_15346415/5223440)



<br/>

<br/>

如何分析类的大小以及内存对齐

题外话：当前 vscode 的跳转有问题，我编译的 g++ 是 tdm-gcc-64 的，但是跳转的却是 llvm 里面的

```c++
class c2 {
public:
  char s[17]; // 17 (+3)
  int i1; // 4
  double d1; // 8
  int i2; // 4 (+4)
};

  std::cout << sizeof(c2) << std::endl;
  std::cout << offsetof(c2, i1) << " " << offsetof(c2, i2) << std::endl;
```

<br/>

<br/>

子类调用父类的虚函数（除了 static_cast ，还有其他方法吗）

```c++
// 子类调用父类的虚函数（除了 static_cast，还有其他方法吗）
class a1 {
public:
    virtual void func() {std::cout << "a1" << std::endl;}
};

class b1 {
public:
    virtual void func() override {std::cout << "b1" << std::endl;}
};
b1 bb;
(static_cast<a1>(bb)).func();
```

<br/>

<br/>

```c++
// 浅拷贝的问题
class Animal {
public:
    int *name;
    Animal() {
        name = new int(1);
        std::cout << "Animal()" << std::endl;
    }
    // 如果不写这个拷贝构造函数，使用编译器默认提供的，那么就会出现问题
    Animal(const Animal& other) {
        name = new int(*other.name);
    }
    ~Animal() {
        std::cout << "~Animal()" << std::endl;
        delete name;
        name = nullptr;
        // 崩溃的原因是，同一个指针多次 delete 不会有问题，但是多个指向同一个对象的指针进行 delete ，就会 oom
    }
}

// 结论是，使用深拷贝和浅拷贝都没有问题，但要注意浅拷贝可能会造成对一个对象的多次析构，从而造成 oom
```

而这里如果把 int 替换为了 string，那么即使不重写拷贝构造函数，也不会有问题（此时把 delete 操作给删除了）

<br/>

<br/>

```c++
#include <iostream>
using namespace std;
class Animal {
public:
    virtual void speak() {
        cout << "Animal is speaking" << endl;
    }
};

class Bird: public Animal {
public:
    virtual void speak() {
        cout << "Bird is speaking" << endl;
    }
};

void DoBussiness(Animal& animal) {
    animal.speak(); // 这里是多态
}

int main() {
    Animal a1;
    Bird b1;
    Animal *p = &a1;
    p->speak();
    p = &b1;
    p->speak();
    
}
```

