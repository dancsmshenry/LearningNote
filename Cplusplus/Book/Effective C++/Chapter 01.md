# 条款01：视C++为一个语言联邦

C++可以分为四个子语言：

- C，C++是以C为基础的（区块，语句，预处理器，内置数据类型，数组，指针）
- Object-Oriented C++（class的构造和析构函数，封装，继承，多态，虚函数，动态绑定）
- Template C++（泛型编程）
- STL（容器，迭代器，算法，函数对象）

<br/>

<br/>

# 条款02：尽量以const，enum，inline替换#define

- 对于单纯常量，最好以const对象或enums替换`#define`
- 对于形似函数的宏，最好改用`inline`函数替换`#define`

<br/>

<br/>

# 条款03：尽可能使用const

mutable

- 对于一个类来说，加入在其成员函数后面添加const，那么该函数就不可以修改函数的变量
- 而如果类的一个属性被设为mutable了，就可以在函数后面有const的情况下修改带有mutable标识的变量了



- 将某些东西声明为const可帮助编译器侦测出错误用法，const可被施加于任何作用域内的对象，函数参数，函数返回类型，成员函数本体
- 编辑器强制实施bitwise constness，但你编写程序时应该使用“概念上的常量性”
- 当const和non-const成员函数有着实质等价的实现时，令non-const版本调用const版本可避免代码重复

<br/>

<br/>

# 条款04：确定对象被使用前已先被初始化

- 类的构造函数最好使用初始化列表（成员初值列）
  - 因为如果是自己逐个赋值，那么实际上编译器会调用这些属性的default构造函数，然后再为其赋值（而使用了初始化列表的话，就直接调用copy函数，提高了效率）
  - 而对于const或引用类型的属性来说，它们一定需要初值，不能被赋值；所以一定要用到成员初值列
- 成员初始化次序
  - base class早于derived classes的初始化；class成员变量总是以其声明次序被初始化（即使它们在初值列以不同的次序出现）
- 为内置型对象进行手工初始化，因为cpp不保证初始化它们
- 构造函数最好使用成员初值列，而不要在构造函数本体内使用赋值操作。初值列列出的成员变量，其排列次序应该和它们在class中的声明次序相同
- 为避免跨编译单元之初始化次序问题，请以local static 对象替换non-local static 对象