###### 条款01：视C++为一个语言联邦

- C++语言可以分为四个子语言
  - C。C++是以C为基础的（区块，语句，预处理器，内置数据类型，数组，指针）
  - Object-Oriented C++。class的构造和析构函数，封装，继承，多态，虚函数，动态绑定
  - Template C++。泛型编程
  - Stl。容器，迭代器，算法，函数对象



###### 条款02：尽量以const，enum，inline替换#define

- 对于单纯常量，最好以const对象或enums替换`#defines`
- 对于形似函数的宏，最好改用`inline`函数替换`#defines`



###### 条款03：尽可能使用const

- 拓展：mutable
  - 对于一个类来说，加入在其成员函数后面添加const，那么该函数就不可以修改函数的变量了
  - 而如果对于其中的一个属性，将其设为mutable的话，就可以在函数后面有const的情况下修改带有mutable标识的变量了
- 将某些东西声明为const可帮助编译器侦测出错误用法，const可被施加于任何作用域内的对象，函数参数，函数返回类型，成员函数本体
- 编辑器强制实施bitwise constness，但你编写程序时应该使用“概念上的常量性”
- 当const和non-const成员函数有着实质等价的实现时，令non-const版本调用const版本可避免代码重复



###### 条款04：确定对象被使用前已先被初始化

- 类的构造函数最好使用初始化列表（成员初值列）
  - 1、因为如果是自己逐个赋值，那么实际上编译器会调用这些属性的default构造函数，然后再为其赋值
    - 而使用了初始化列表的话，就直接调用copy函数，提高了效率
  - 2、而对于const或引用类型的属性来说，它们一定需要初值，不能被赋值；所以一定要用到成员初值列
- 成员初始化次序
  - base class早于derived classes的初始化；class成员变量总是以其声明次序被初始化（即使它们在初值列以不同的次序出现）
- 为内置型对象进行手工初始化，因为cpp不保证初始化它们
- 构造函数最好使用成员初值列，而不要在构造函数本体内使用赋值操作。初值列列出的成员变量，其排列次序应该和它们在class中的声明次序相同
- 为避免跨编译单元之初始化次序问题，请以local static 对象替换non-local static 对象



###### 条款05：了解C++默默编写并调用哪些函数

- 对于一个空类，编辑器会为其写下这些代码：
  - default构造函数
  - copy构造函数和copy assignment操作符
    - 单纯地将来源对象的每一个non-static成员变量拷贝到目标对象
  - 析构函数
    - 是non-virtual的
  - 以上函数都是public且inline的
- 如果声明了一个构造函数，编辑器是不会创建default函数了的
- 引用是不可以被修改绑定的
  - 所以，如果一个类里面的成员包含引用的话，必须重写copy assignment操作符
  - 如果有string的话感觉也是同理
- 编辑器可以暗自为class创建default构造函数，copy构造函数，copy assignment操作符以及析构函数



###### 条款18：让接口容易被正确使用，不易被误用

- 好的接口很容易被正确使用，不容易被误用，你应该在你的所有接口中努力达成这些性质
- “促进正确使用”的办法包括接口的一致性，以及与内置类型的行为兼容
- “阻止误用”的办法包括建立新类型、限制类型上的操作，束缚对象值，以及消除客户的资源管理责任
- `trl::shared_ptr`支持定制型删除器（`custom deleter`）。这可防范DLL问题，可被用来自动解除互斥锁等等



###### 条款19：设计class犹如设计type

- 即需要考虑到以下几点：
  - 这个类的构造函数和析构函数，以及内存分配函数和释放函数
  - 对象的初始化和赋值的区别（构造函数和赋值操作符的行为）
  - 如果被passed by value的话（copy函数的设计）
  - type的合法值（属性的约束条件）
  - 类与类之间的关系（与父类的关系，继承）
  - 是否需要转换（类型转换函数）
  - 需要设计那些函数和重载哪些操作符
  - 成员（属性和函数）的私有，公有还是保护
  - 是否需要模板



###### 条款20：宁以 pass-by-reference-to-const 替换 pass-by-value

- 引用的本质就是传指针，如果是直接传数值的话（特别是对象包含对象的情况），会导致多次的调用构造和析构函数，造成空间和时间上的浪费

  - 所以需要传递的是引用而不是数值
  - 当然如果当前要传的对象的大小小于指针，就可以传本体

- 加上const的原因：因为传进来的是指针，是可以直接操作其本体的，所以为了防止函数修改本体的数据，所以要加上const防止其修改数据

- 同时，pass-by-reference-to-const也可以避免对象切割（slicing）的问题

  - ```cpp
    #include<iostream>
    
    using namespace std;
    
    class Window{
        public:
            int a;
            virtual void test(){
                cout << "test in Window." << endl;
            }
    };
    
    class Window1 : public Window{
        public:
            virtual void test(){
                cout << "test in Window1." << endl;
            }
    };
    
    void tesst(Window &a1){
        /*
        如果这里是直接传入值进来的话，就会导致a1调用的就是Window的test函数（但此时传进来的是Window1类型的变量）
        而是传引用的话，就可以调用到Window1的test函数
        */
        a1.test();
    }
    
    int main(){
        Window1 window;
        tesst(window);
    }
    ```

- 但不是小的types不一定都是用引用传递的，如stl中的容器

- 但，以上的规则并不适用于内置类型，以及stl的迭代器和函数对象，对它们而言，pass-by-value往往比较适当



###### 条款21：必须返回对象时，别妄想返回其reference

- 不要返回pointer或reference指向一个local stack对象

  - local stack只是局部对象，超出作用域就会被释放掉

- 不要返回reference指向一个heap-allocated对象

  - 返回了以后，不知道如何释放heap，容易导致内存泄漏

- 也不要返回pointer或reference指向一个local static对象（可能同时需要多个这样的对象的时候）

  - 注意到static是一个静态的对象，始终是只有一个的（所以每次函数都是对其操作的）

  - ```cpp
    const Rational& operator*(const Rational& lhs, const Rational& rhs){
        static Rational result;
        result = ...;
        return result;
    }
    
    Rational a, b, c, d;
    if ((a * b) == (c * d)){
        
    }else{
        
    }//因为是static，所以这两者一定是一样的，无论如何都是true
    ```



###### 条款22：将成员变量声明为private

- 如果取消了一个public变量，那么对于所有使用public的变量来说，很多代码都会被破坏；protected也是同理
  - 而如果只是取消掉一个private，那么只需要修改一下封装好了这个数据的相关接口即可
  - 因为对于private变量，只有成员函数（几个）才可以影响到他们
  - 而且public的变量可以随便被修改
- 同时，如果设置为private，就可以实现只读访问，不准访问，读写访问等相关权限了



###### 条款23：宁以non-member、non-friend替换member函数

- 宁可拿non-member non-friend 函数替换 member函数，这样做可以增加封装性、包裹弹性和机能扩充性



###### 条款24：若所有参数皆需类型转换，请为此采用non-member函数

- 参考有理数的乘法

  - ```cpp
    Rational one(1, 8);
    Rational two(1, 2);
    Rational result = one * two;//此时没有问题；有理数的乘法的重载写入为Rational的一个成员函数里面了
    Rational resule = one * 2;//也没有问题，因为这里的2可以隐式转换为有理数rational
    Rational result = 2 * one;//出问题了，因为这里的2是整型，不能把one转换为整型，或者说2也变不了rational
    ```

- 所以，为了更加友好的使用有理数，就要把他的需要类型转换的函数变为non-member

  - 但是也不需要把他变为friend函数，因为这类函数都是调用其public接口的

- 如果你需要为某个函数的所有参数进行类型转换，那么这个函数必须是non-member



###### 条款25：考虑写出一个不抛出异常的swap函数

- 本章的偏特化我还没有理解，所以..

- 当`std::swap`对你的类型效率不高时，提供一个swap成员函数，并确定这个函数不会抛出异常

- 如果你提供一个`member swap`，也提供一个`non-member swap`用来调用前者。对于classes（而非templates），也请特化`std::swap`

- 调用`swap`应针对`std::swap`使用`using`声明式，然后调用`swap`并且不带任何“命名空间资格修饰”

- 为“用户定义类型”进行全特化是好的，但千万不要尝试在`std`内加入某些对`std`而言全新的东西

- 科普

  - pimpl意思为“具体实现的指针”（Pointer to Implementation）

    - 通过一个私有的成员指针，将指针所指向的类的内部实现数据进行隐藏
    - 减少依赖项（降低耦合性）：其一减少原类不必要的头文件的依赖，加速编译；其二对Impl类进行修改，无需重新编译原类。
    - 接口和实现的分离（隐藏了类的实现）：私有成员完全可以隐藏在共有接口之外，给用户一个间接明了的使用接口，尤其适合闭源API设计。
    - 可使用惰性分配技术：类的某部分实现可以写成按需分配或者实际使用时再分配，从而节省资源

  - 类模板，全特化，偏特化

    - ```cpp
      #include <iostream>
      using namespace std;
      
      template <class T1, class T2>
      class Test
      {
      public:
          Test(T1 i, T2 j) : a(i), b(j) { cout << "类模板" << endl; }
      
      private:
          T1 a;
          T2 b;
      };
      
      template <>
      class Test<int, char>
      {
      public:
          Test(int i, char j) : a(i), b(j) { cout << "全特化" << endl; }
      
      private:
          int a;
          char b;
      };
      
      template <class T2>
      class Test<char, T2>
      {
      public:
          Test(char i, T2 j) : a(i), b(j) { cout << "偏特化" << endl; }
      
      private:
          char a;
          T2 b;
      };
      
      int main()
      {
          Test<double, double> t1(1.4, 2.3); //这是类模板
          Test<int, char> t2(5, 'A');        //这是全特化
          Test<char, float> t3('B', 3.1);    //这是偏特化
      }
      ```

    - 现有类模板，后才有全特化和偏特化

    - 特化分为全特化与偏特化。全特化就是限定死模板实现的具体类型，偏特化就是如果这个模板有多个类型，那么只限定其中的一部分

    - 特化的原因：有时需要对某些类型进行特殊处理，不然会出错

  - 函数模板，全特化，没有偏特化

    - ```cpp
      //模板函数
      template<class T1, class T2>
      void fun(T1 a, T2 b){
          cout << "mobanhanshu" << endl;
      }
      
      //全特化
      template<>
      void fun<int ,char>(int a, char b){
          cout << "quantehua" << endl;
      }
      ```

    - 

