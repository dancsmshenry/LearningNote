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
