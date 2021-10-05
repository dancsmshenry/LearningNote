#### Chapter01、导读

- 勿在浮沙筑高台
- 革命尚未成功，同志仍需努力
- cpp的两大技术主线：
  - 泛型编程（generic programming）
  - 面向对象编程（object-oriented programming）
- 探索虚函数表（vtbl），虚指针（vptr），虚机制（virtual mechanism），多态（polymorphism），虚函数（virtual function）
- 增添新的书籍：effective modern c++ 



#### Chapter02、conversion function

- ```cpp
  class Fraction{
    public:
      Fraction(int num, int den = 1):m_numerator(num), m_denominator(den){}
      
      operator double() const{
          return (double)(m_numerator / m_denominator);
      }//转换函数，conversion function，把Fraction类型转换为double类型
      
     private:
      int m_numerator;//分子
      int m_denominator;//分母
  };
  
  Fration f(3, 5);
  double d = 4 + f;//调用operator double()将f转换为0.5
  ```



#### Chapter03、non-explicit one argument ctor

- ```cpp
  class Fraction{
    public:
      Fraction(int num, int den = 1):m_numerator(num), m_denominator(den){}
      
      Fraction operator+(const Fraction& f){
          return Fraction(...);
      }
      
     private:
      int m_numerator;//分子
      int m_denominator;//分母
  };
  
  Fration f(3, 5);
  Fraction d2 = f + 4;//会首先调用Fraction的重载，,发现目标不是Ftaction，所以会首先调用non-explict-one-argument-ctor将4转换为Fraction，然后再调用Fraction的重载+
  ```

- 但是会出现一种情况，即对于编译器来说有多条路径需要走，此时会出现二义性

  - ```cpp
    class Fraction{
      public:
        explict Fraction(int num, int den = 1):m_numerator(num), m_denominator(den){}
        
        operator double() const{
            return (double)(m_numerator / m_denominator);
        }
        
        Fraction operator+(const Fraction& f){
            return Fraction(...);
        }
        
       private:
        int m_numerator;//分子
        int m_denominator;//分母
    };
    
    Fration f(3, 5);
    Fraction d2 = f + 4;//编译器到底是要把4变为Fraction来操作，还是说要把f变为double来操作（两条路都走得通）
    //所以为了规范使用，就在构造函数前面加上explict，表示这个函数必须显式调用，不能隐式调用
    //这样，代码就会直接报错，说不能把double隐式的转换为Fraction
    ```

- 关键字explicit：被该词修饰的函数只能被显式的调用，不能被隐式调用（大部分用在构造函数上面）



#### Chapter04、pointer-like classes

- 有关智能指针

  - 把对象放到智能指针里面，操控指针就像操控对象本身一样（因为智能指针的底层对操作符做了很多的重载）

- 有关迭代器

  - 感觉也有点像智能指针

- ```cpp
  template <class T>
  class shared_ptr{
      public:
      	T& operator*() const{
              return *px;
          }//智能指针模拟*的重载
      	
      	T* operator->() const{
              return px;
          }//智能指针模拟->的重载
      	
      	shared_ptr(T* p):px(p){}
      private:
      	T* px;
      	long* pn;
  }
  
  shared_ptr<Foo> sp(new Foo);
  Foo f(*sp);
  sp->method();
  ```

- 感觉，要让一个类像一个指针，主要就是重载好它的*运算符和->运算符



#### Chapter05、function-like classes

- 同上，要让一个类像一个函数，主要就是重载好它的()运算符
- 在cpp标准库里面，就用了很多的仿函数，其中仿函数都继承了很多的类（？原因在另一节课会讲）



#### Chatper06、namespace经验谈

- 把代码用namespace包起来，保护防止重名，解决冲突



#### Chapter07、class template

- 类模板：在设计一个class的时候，把其中的某一个属性给抽离出来，任意指定（就是重复太多，而且增加类的复用）



#### Chapter08、function template

- ```cpp
  template <class T>
  inline const T& min(const T& a, const T&b){
      return b < a ? b : a;
  }
  ```

- 在具体使用到模板的时候会再编译一次（所以可能第一次编译写好的模板代码的时候，是可以通过的，但是后续把T放入的时候，可能就无法通过了）



#### Chapter09、member template

- ```cpp
  template <class T1, class T2>
  struct Pair
  {
      typedef T1 fritd_type;
      typedef T2 seconde_type;
  
      T1 first;
      T2 second;
  
      Pair() : first(T1()), second(T2()) {}
  
      Pair(const T1 &a, const T2 &b) : first(a), second(b) {}
  
      template <class U1, class U2>
      Pair(const Pair<U1, U2> &p) : first(p.first), second(p.second) {}
  };
  
  int main(){
      Pair<int, int> p1(1, 2.0);//这里初始化一个Pair对象，T1T2分别是int，int
      Pair<int, int> p2(p1);//这里设计好pairT1T2的初始值，然后再用p1去把它初始化
  }
  ```

- 初一看好像没什么用途，但是看了解析才发现，用到父类和子类上是真的好用

  - ```cpp
    class Base1{};
    class Derived1:public Base1{};
    
    class Base2{};
    class Derived2:public Base2{};
    
    pair<Derived1, Derived2> p1;
    pair<Base1, Base2> p2(p1);
    //上述代码变为
    pair<Base1, Base2> p2(pair<Derived1, Derived2>());
    ```

  - 理解

    - U2一定可以转换为T2的
    - 相当于后面给的范围会大于原有的范围，以便装下更多的类型（后面给的是父类吗，父类和子类是相通的）
    - 把一个鲫鱼和麻雀构成的pair，放到一个由鱼类和鸟类构成的pair中，是可以的（反之则不行）

- ```cpp
  template<typename _Tp>
  class shared_ptr:public __shared_ptr<_Tp>
  {
      template<typename _Tp1>
      explict shared_ptr(_Tp1* _p):__shared_ptr<_Tp>(__p){}
  };
  
  Base1* ptr = new Derived;//up-cast
  shared_ptr<Base1> sptr(new Derived1);//模拟up-cast
  ```



#### Chapter10、specialization

- 模板特化

  - 泛化：模板有一个类型，要用的时候再去指定它即可
  - 特化：针对一个特殊的类型，进行特别的处理

- ```cpp
  template<class Key>//一般的泛化
  
  template<>//针对某种特定类型的特化，即如果类型是char类型的话，那么就会指定用这一串代码
  struct hash<char>{
      size_t operator()(char x) const{return x;}
  };
  ```

- 特化可以有任意版本

- 泛化又叫做全泛化，特化就又有偏特化



#### Chapter11、模板偏特化

- partial specialization，模板偏特化-个数的偏/范围上的偏

- 个数上的偏

  - ```cpp
    template<typename T, typename Alloc = ...>
    class vector{};
    
    template<typename Alloc = ...>
    class vector<bool, Alloc>{};//模板的偏特化，这里表示如果T是bool类型的话，那么就会调用下面的代码
    ```

- 范围上的偏

  - ```cpp
    template<typename T>
    class C{};//一般的泛化
    
    template<typename U>//这里也可以写T，不过上面和下面不是同一样东西
    class C<U*>{};//模板偏特化，即表示如果传进来的是一个指针，那么就会调用下面的代码
    //即范围上的偏特化，原来是任意类型，现在指定是指针类型或其他类型
    ```



#### Chapter12、模板模板参数

- template template parameter

- 只有在模板上的默认参数的位置上class和typename等变量才能共通

- ```cpp
  template<typename T, template<typename T> class Container>
  class XCls{
  private:
  	Container<T> c;
  public:
  	...
  };
  
  //ps：这里的typename在gcc中有一个bug，就是如果两个都写的是T的话是无法通过的，要把后面的T改为其他的变量才行
  //还是因为说，这里写成T会使得编译器认为是同时同一个变量，导致错误呢？
  
  template<typename T>
  using Lst = list<T, allocator<T>>
  //这里需要注意的是，list其实是不止一个参数的，它有一个参数是默认了的，所以要上述操作
  XCls<string, Lst> mylst2;
  ```

- 这里有一个问题：如果都是T的话，会不会就限制了Container的参数类型（即我不想要T这种类型，我想要其他类型，但是现在只能是T）？

- 就是在模板参数里面再加一个模板

- 注意：这里绑定了就不是模板了

  - ```cpp
    template<class T, class Sequence = deque<T>>
    class stack{};
    
    stack<int> s1;
    stack<int, list<int>> s2;//这里被绑定了，所以就不能叫做模板（参考上面，上面的T是没绑定的，好像有点牵强）
    stack<int, list<double>> s3;//要明白上面的=deque<T>只是提供了一个默认的参数罢了
    ```



#### Chapter13、关于C++标准库

- 容器，算法，迭代器，仿函数
- 输出``____cplusplus`来查看是否支持cpp11
- 算法+数据结构=程序



#### Chapter14、三个主题

- variadic templates（since cpp11）

  - 数量不定的模板参数

  - ```cpp
    void print(){}
    
    template <typename T,typename... Types>
    void print(const T& firstArg, const Types&... args){
        cout << firstArg << endl;
        print(args...);
    }
    /**
    可以理解上述的函数时递归调用的，即每次都取出前面一个数进行输出，把后面的数继续递归会这个函数操作
    不过注意，args总会出现空的时候，这样就不会调用到这个模板函数，所以为了防止bug，就再写一个空的函数返回即可
    **/
    
    cout << sizeof(args) << endl;//查询args有多少个
    ```

- auto(since cpp11)

  - ```cpp
    list<string> c;
    list<string>::iterator ite;
    ite = find(c.begin(), c.end(), target);
    
    //现在可以写为
    list<string> c1;
    auto ite = find(c.begin(), c.end(), target);//自动推导类型，用于一些类型非常难写或难找的类型的一种便捷式的写法
    //同时，auto必须要有具体的值，通过值才能推导出具体的对象
    ```

- ranged-base for(since cpp11)

  - ```cpp
    for(decl:coll){
        statement;
    }
    /**
    左边是一个变量，右边是一个容器，遍历一遍容器，把容器里的元素逐个放到这个变量当中
    **/
    
    for (auto elem:vec){
        cout << elem << endl;
    }//这个返回的是值，即类似值传递，不能修改到它本身（pass by value）
    
    for (auto& elem:vec){
        elem *= 3;
    }//这个返回的是值的引用，修改它就是修改本身（pass by reference）
    ```



#### Chapter15、reference

- 对于一个引用，从使用者的角度来看，引用就是对象的一个别名；但是从编译器的角度来看，引用的本质其实是一个指向其对象的指针

- ```cpp
  sizeof(r) == sizeof(x);
  &x = &r;//object和其reference的大小相同，地址也相同（全都是假象）
  ```

- java里面所有变量都是reference

- 引用必须要有初始值，并且不能改变指向

- ps：指针（4个字节，在32位电脑上）

- reference被认为是一种漂亮的pointer

- reference通常不用于声明变量，而用于参数类型和返回类型的描述

- ```cpp
  double imag(const double& im){}
  double imag(const double im){}//这两个函数被视为同一个函数，不能共存
  ```

- 注意传入和接收的写法（比如我传入的是一个对象的引用，接收端却是以指针的方式接收的，不好）

- const可以作为函数签名的一部分

  - ```cpp
    double imag(const double& im){}
    double imag(const double im) const{}//这两个函数被视为同一个函数，不能共存；但是加上了const，两个函数不同，可以并存
    ```



#### Chapter16、复合&继承关系下的构造和析构

- 参考I的chapter12



#### Chapter17、关于vptr和vtbl

- 带有虚函数就会有虚指针

- 有关继承：继承只会继承下数据，继承下函数的调用权

- 有虚函数的类会有一个虚指针（virtual point），该指针指向一个虚函数表（virtual table），虚函数表上记录着虚函数的地址

- 这个指针一般会放到对象空间的第一位，一般占用4个字节

- 静态绑定：根据代码，把它编译成指定的命令，然后执行

- 动态绑定：通过指向对象的指针或对象本身，找到虚函数指针，再通过指针指向的虚函数表，找到确定要用到的那个函数的地址，最后根据地址去调用函数

  - ```cpp
    //其中p是一个指向对象的指针，vptr是对象内部的虚函数指针，n是要找的函数的位置
    //也要看p最后指到的是谁，正是因为指到的不同才导致了多态
    (*(p->vptr)[n])(p);
    ```

  - 三个条件：指针调用，向上转型，调用虚函数

- 多态的造成



#### Chapter18、关于this

- this point：通过一个对象调用一个函数，该对象的地址就是this point
- 背景：通过子类调用父类的一个函数，而父类的这个函数里面调用了一个虚函数
  - 但本次调用时是子类开的头，所以调用的就是这个子类的对应的虚函数
  - 所以，再调用函数的时候，就会传入一个该子类的一个指针，这就是this指针
  - 传入this指针以后，里面函数的调用动作都会由`Serialize();`变为`this->Serialize();`，再变为`(*(this->vptr)[n])(this)`



#### Chapter19、关于Dynamic Binding I

- 通过对象直接调用都不是多态！
- 通过汇编语言发现多态是如何实现的



#### Chapter19、关于Dynamic Binding II

- 浅谈const
  - 当成员函数的const和non-const版本同时存在时
  
    - const object只会（只能）调用const版本
    - non-const object 只会（只能）调用non-const 版本
  
  - |                                               | const object(数据不得变动) | non-const object(数据可变动) |
    | --------------------------------------------- | -------------------------- | ---------------------------- |
    | const member functions(保证不修改成员数据)    | ok（可以调用）             | ok（可以调用）               |
    | non-const member function(不保证成员数据不变) | no（不可以调用）           | ok（可以调用）               |
  
  - 再次强掉：const是可以作为函数的关键字的，用于区分函数
  
  - 所以应该培养大气正确的编程习惯，即如果函数不会修改对象的数据的话，就一定要加上const



#### Chapter20、关于new、delete

- 参考 I 的chapter08
  - new：先分配memory，再调用ctor
  - delete：先调用dtor，再分配memory
  - 动态分配所得的内存块
  - array new一定要搭配array delete
- class可以重载new和delete，用来设计内存池



#### Chapter21、Operator new，Operator delete

- 重载operator new（用来分配内存空间，效果上应该等价于malloc），重载operator delete（用来删除掉空间，效果上应该等价于free）
  - 重载全局的这个函数
  - 重载成员的这个函数
  - 为什么要接管这些函数：做内存池



#### Chapter22、示例

- ```cpp
  Foo* pf = new Foo;
  delete pf;//如果没有members重载，就用全局的
  
  Foo* pf = ::new Foo;
  ::delete pf;//用：：表示要使用全局的
  ```

- ```cpp
  void* Foo::operator new(size_t size){
      Foo* p = (Foo*)malloc(size);
      cout << ...;
      return p;//这是重载后的operator new(这是函数的全名)
  }
  
  void Foo::operator delete(void* pdead, size_t size){
      cout << ...;
      free(pdead);//这是重载后的operator delete(这是函数的全名)
  }
  ```

- 回归对象模型

  - 发现，如果一个对象的大小是12，那么五个对象的大小理应是60，但是实际操作的时候发现，却是64，因为这里还要多用一个变量来储存数组的大小



#### Chapter23、重载new()，delete()示例

- 重载class member operator new()时
  - 第一参数必须是size_t，其余的参数以new所指定的placement arguments为初值
  - 前提是每一个版本声明都必须有独特的参数列
- 重载class member operator delete()时
  - 可以重载多个版本，但是都不会被delete给调用
  - 只有当new所调用的ctor抛出exception时，才会调用这些版本的operator delete()，它只可能这样被调用，主要用来归还未能完全创建成功的object所占用的memory



#### Chapter24、Basic_String 使用 new(extra) 扩充申请量

- 揭秘string
  - string的最前面几个单位是用来计数（自己被引用了多少次），长度是多少