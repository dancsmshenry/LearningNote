# 第14章 重载运算与类型转换

## 14.1 基本概念

- 重载的运算符是具有特殊名字的函数：它们的名字由关键字operator和其后要定义的运算符号共同组成

- 当一个重载的运算符是成员函数时，this绑定到左侧运算对象上，成员运算符函数的显式参数数量比运算对象的数量少一个

- 重载运算符函数：或者是类的成员，或者至少含有一个类类型的参数（不能重定义内置的运算符）

- 一个非成员运算符函数的等价调用

  - ```cpp
    data1 + data2;//普通表达式
    operator+(data1, data2);//等价的函数调用
    ```

- 像调用其他成员函数一样显式地调用成员运算符函数

  - ```cpp
    data1 += data2;//基于“调用”的表达式
    data1.operator+=(data2);//对成员运算符函数的等价调用
    ```

- 通常情况下不重载逗号，取地址符，逻辑与和逻辑或运算符（在逻辑与前面如果是假的话就不会检测后面的了，而重载后的必然是两个都计算出来的）

- 选择作为成员或者非成员

  - 赋值（=）、下标（[]）、调用（()）和成员访问箭头运算符（->）必然是成员
  - 复合赋值运算符一般来说应该是成员，但并非必须
  - 递增和递减和解引用都应该是成员
  - 具有对称属性的运算符可能转换任意一端的运算对象，通常应该是普通的非成员函数（参考：s+"s"和"s" + s的区别）

<br/>

<br/>

## 14.2 输入和输出运算符

- 重载输出运算符

  - 第一个形参是一个非常量ostream对象的引用（ostream是非常量是因为向流写入内容会改变其状态）
  - 输出运算符尽量减少格式化操作
  - 通常，输出运算符应该主要负责打印对象的内容而非控制格式，输出运算符不应该打印换行符

- 为了方便使用，输入输出符必须是非成员函数

  - ```c++
    Sales_data data;
    data << cout;//用起来不方便
    ```

  - 如果涉及到对象的私有数据的话，就要变为友元函数

- 重载输入运算符

  - 第一个形参是运算符将要读取的流的引用（不能为const，理由同上），第二个形参是将要读入到的对象的引用
  - 需要判断是否输入成功，即输入运算符必须处理可能失败的情况，而输出运算符不需要

<br/>

<br/>

## 14.3 算术和关系运算符

- 算数运算符通常回计算它的两个运算对象并得到一个新值，这个值有别于任意一个运算对象，常常位于一个局部变量之内，操作完成后返回该局部变量的副本作为其结果
- 如果类同时定义了算数运算符和相关的复合赋值运算符，则通常情况下应该使用复合赋值来实现算术运算符
- 相等运算符的规则：
  - 如果一个类含有判断两个对象是否相等的操作，则它显然应该把函数定义成operator==而非一个普通的命名函数
  - 如果类定义了operator==，则该运算符应该能判断一组给定的对象中是否含有重复数据
  - 相等性运算符应该具有传递性
  - 如果类定义了operator==，则这个类也应该定义了operator!=
  - 相等运算符和不相等运算符中的一个应该把工作委托给另一个
  - 如果某个类再逻辑上有相等性的含义，则该类应该定义operator==，这样做可以使得用户更容易使用标注库算法来处理这个类
- 关系运算符
  - 定义顺序关系，令其与关联容器中对关键字的要求一致
  - 如果类同时也含有==运算符的话，则定义一种关系令其与 == 保持一致
  - 如果存在唯一一种逻辑可靠的<定义，则应该考虑为这个类定义<运算符，如果类同时还包含==，则当且仅当<的定义和 ==产生的结果一致时才定义 < 运算符

<br/>

<br/>

## 14.4 赋值运算符

- ```cpp
  //参考下面用{}初始值的
  vector<string> v;
  v = {"a", "an", "the"};
  
  class StrVec{
      public:
      	StrVec &operator=(std::initializer_list<std::string>);
  };
  
  //为了和内置的运算符一样，返回的也要是引用
  StrVec &StrVec::operator=(initializer_list<string> i1){
      auto data = allov_n_copy(i1.begin(), i1.end());
      free();
      elements = data.first;
      first_free = cap = data.second;
      return *this;
  }
  ```

- 可以重载赋值运算符，不论形参的类型是什么，赋值运算符都必须定义为成员函数

- 复合赋值运算符

  - ```cpp
    Sales_data& Sales_data::operator+=(const Sales_data &rhs){
        units_sole += rhs.units_sold;
        revence += rhs.revence;
        return *this;
    }
    ```

- 赋值运算符必须定义成类的成员，复合赋值运算符通常情况下也应该这样做，这两类运算符都应该返回左侧对象的引用

<br/>

<br/>

## 14.5 下标运算符

- 下标运算符必须是成员函数
- 总结：如果一个类包含小标运算符，则它通常会定义两个版本：一个返回普通引用，另一个是类的常量成员并且返回常量引用
  - 这点非常重要，因为如果没有返回常量引用的，那么const对象的内容也会被随意的更改，这是不对的

<br/>

<br/>

## 14.6 递增和递减运算符

- 定义递增和递减运算符的类应该同时定义前置版本和后置版本，这些运算符通常应该被定义成类的成员

- ```cpp
  class StrBlobPtr{
      public:
      	StrBlobPtr& operator++();//为了与内置版本保持一致，前置运算符应该返回递增或递减后的对象的引用
      	StrBlobPtr& operator--();//前置运算符，前置运算符，前置运算符
  };
  
  StrBlobPtr& StrBlobPtr::operator++(){
      ++ curr;
      return *this;//返回的是一个引用
  }
  ```

- 以上是前置运算符

- ```cpp
  class StrBlobPtr{
      public:
      	StrBlobPtr operator++(int);
      	StrBlobPtr operator--(int);
      //为了解决后置版本的问题，后置版本接受一个额外的（不被使用）int类型的形参，当我们使用后置运算符时，编译器为这个形参提供一个值为0的实参
  };
  
  StrBlobPtr StrBlobPtr::operator++(int){//因为不会用到int形参，所以无须为其命名
      StrBlobPtr ret = *this;
      ++ *this;
      return set;//为了与内置版本保持一致，后置运算符应该返回对象的原值（递增或递减之前的值），返回的形式是一个值而非引用
  }
  ```

- 显式地调用后置运算符

  - ```cpp
    StrBlobPtr p(a1);//p指向a1中的vector
    p.operator++(0);//调用后置版本的operator++
    p.operator++();//调用前置版本的operator++
    ```

<br/>

<br/>


## 14.7 成员访问运算符

- 箭头运算符必须是类的成员，解引用运算符通常也是类的成员，尽管并非必须如此
- 也要加上const（->和*都不会修改对象的属性）
- 重载的箭头运算符必须返回类的指针（因为是指针就可以无限的递归调用下去）或者自定义了箭头运算符的某个类的对象（最后都会循环返回到一个对象）

<br/>

<br/>

## 14.8 函数调用运算符

- ```cpp
  struct abdInt{
      int operator() (int val) const{
          return val < 0 ? -val : val;
      }
  }
  ```

- 函数调用运算符必须是成员函数，一个类可以定义多个不同版本的调用运算符，相互之间应该再参数数量或类型上有所区别

- 如果类定义了调用符，则该类的对象称作函数对象

- 函数调用符也有参数可以传入

- lambda（lambda其实就相当于函数调用运算符）

  - ```cpp
    stable_sort(words.brgin(), words.end(),[](const string &a, const string &b){return a.size() < s2.size();})
    ```

  - ```cpp
    class ShorterString{
        public:
        	bool operator() (const string &s1, const string &s2) const{
                return s1.size() < s2.size();
            }
    };
    ```

- 标准库定义的函数对象

<br/>

<br/>


## 14.9 重载、类型转换与运算符

- 类型转换运算符：负责将一个类类型的值转换成其他类型

  - 形式：operator type() const;
  - 可以转换成指针或引用类型，但是不能转换为数组或函数类型
  - 类型转换运算符没有显式的返回类型，也没有形参，而且必须定义为类的成员函数
  - 总结：一个类型转换函数必须是类的成员函数；它不能声明返回类型，形参列表也必须为空，类型转换函数通常为const

- 隐式的用户定义类型转换（即后面写的类型转换运算符）可以置于标准（内置）类型转换之前或之后（即int->double）

- 尽量不要把类型转换为bool

- 显式的类型转换运算符：

  - ```cpp
    class SmallInt{
        public:
        	//编译器不会自动执行这一类型转换
        	explict operator int() const {return val;}
    };
    
    SmallInt si = 3;//ok,是显式调用
    si + 3;//error,是隐式调用
    ```

  - 当表达式出现在下列位置时，显式的类型转换将被隐式地执行：

    - if、while及do语句的条件部分
    - for语句头的条件表达式
    - 逻辑非表达式，逻辑或运算符，逻辑与运算符的运算对象
    - 条件运算符的条件表达式

- 向bool的类型转换通常用在条件部分，因此operator bool一般定义成explicit的

- 避免有二义性的类型转换

  - 总结：通常情况下，不要为类定义相同的类型转换，也不要在类中定义两个及两个以上转换源或转换目标是算数类型的转换

  - 实参匹配和相同的类型转换（在A中定义了把B转换为A的转换函数，在B中定义了转换为A的转换符）

  - ```cpp
    struct B;
    struct A{
        A() = default;
        A(const B&);//也是把B转换为A
    };
    
    struct B{
        operator A() const;//把B转换为A
    };
    
    A f(const A&);//定义了一个函数
    B b;
    A a = f(b);//发生了二义性
    
    //解决办法
    A a1 = f(b.operator A());
    A a2 = f(A(b));
    ```

- 二义性与转换目标为内置类型的多重类型转换

  - 有类型转换符和带有默认参数的类型转换

  - ```cpp
    struct A{
        A(int = 0);
        A(double);//最好不要创建两个转换源都是算术类型的类型转换
        operator int() const;
        operator double() const;//最好不要创建两个转换对象都是算术类型的类型转换
    };
    
    void f2(long double);
    A a;
    f2(a);//这里是调用double转long double，还是调用int转long double？
    
    long lg;
    A a2(lg);//这里调用的是A(int)还是A(double)
    ```

  - 产生的原因：它们所需的标注那类型转换级别一致

  - 总结：当我们使用两个用户定义的类型转换时，如果转换函数之前或之后存在类型转换，则标准类型转换将决定最佳匹配到底是哪个

- 重载函数与转换构造函数

  - ```cpp
    struct C{
        C(int);
    };
    
    struct D{
        D(int);
    };
    
    void manip(const C&);
    void manip(const D&);
    manip(10);//不知道调用的是manip(C(10))，还是mainp(D())
    ```

  - 如果在调用重载函数时我们需要使用构造函数或者强制类型转换来改变实参的类型，则通常意味着程序的设计存在不足

- 重载函数与用户定义的类型转换

  - ```cpp
    struct C{
        C(int);
    };
    
    struct E(){
        E(double);
    };
    
    void manip2(const C&);
    void manip2(const E&);
    
    manip(10);//这里调用的是manip2(C(10))还是manip2(E(double(10)))
    ```

  - 在调用重载函数时，如果需要额外的标准类型转换，则该转换的级别只有当所有可行函数都请求同一个用户定义的类型转换时才有用，如果所需的用户定义的类型转换不止一个，则该调用具有二义性

- 函数匹配与重载运算符

  - 当我们调用一个命名的函数时，具有该名字的成员函数和非成员函数不会彼此重载

  - ```cpp
    class SmallInt{
        friend SmallInt operator+(const SamllInt&, const SmallInt&);
        public:
        	SmallInt(int = 0);
        	operator int() const{return val;}
        private:
        	std::size_t val;
    };
    
    SmallInt s1, s2;
    SmallInt s3 = s1 + s2;
    int i = s3 + 0;//发生二义性错误，可以把0转换为smallint，再调用smllptr的+；或者把s3转换成int，然后再相加
    ```

  - 如果我们对同一个类既提供了转换目标是算数类型的转换，也提供了重载的符号的运算符，则将会遇到重载运算符与内置运算符的二义性问题