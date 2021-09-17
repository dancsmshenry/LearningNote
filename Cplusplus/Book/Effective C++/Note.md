- [条款01：视C++为一个语言联邦](#条款01视c为一个语言联邦)
- [条款02：尽量以const，enum，inline替换#define](#条款02尽量以constenuminline替换define)
- [条款03：尽可能使用const](#条款03尽可能使用const)
- [条款04：确定对象被使用前已先被初始化](#条款04确定对象被使用前已先被初始化)
- [条款05：了解C++默默编写并调用哪些函数](#条款05了解c默默编写并调用哪些函数)
- [条款06：若不想使用编译器自动生成的函数，就该明确拒绝](#条款06若不想使用编译器自动生成的函数就该明确拒绝)
- [条款07：为多态基类声明virtual析构函数](#条款07为多态基类声明virtual析构函数)
- [条款08：别让异常逃离析构函数](#条款08别让异常逃离析构函数)
- [条款09：绝不再构造和析构过程中调用virtual函数](#条款09绝不再构造和析构过程中调用virtual函数)
- [条款10：令operator= 返回一个reference to *this](#条款10令operator-返回一个reference-to-this)
- [条款11：在operator=中处理“自我赋值”](#条款11在operator中处理自我赋值)
- [条款12：复制对象时勿忘其每一个成分](#条款12复制对象时勿忘其每一个成分)
- [条款13：以对象管理资源](#条款13以对象管理资源)
- [条款14：在资源管理类中小心copying行为](#条款14在资源管理类中小心copying行为)
- [条款15：在资源管理类中提供对原始资源的访问](#条款15在资源管理类中提供对原始资源的访问)
- [条款16：成对使用new和delete时要采取相同形式](#条款16成对使用new和delete时要采取相同形式)
- [条款17：以独立语句将newed对象置入智能指针](#条款17以独立语句将newed对象置入智能指针)
- [条款18：让接口容易被正确使用，不易被误用](#条款18让接口容易被正确使用不易被误用)
- [条款19：设计class犹如设计type](#条款19设计class犹如设计type)
- [条款20：宁以 pass-by-reference-to-const 替换 pass-by-value](#条款20宁以-pass-by-reference-to-const-替换-pass-by-value)
- [条款21：必须返回对象时，别妄想返回其reference](#条款21必须返回对象时别妄想返回其reference)
- [条款22：将成员变量声明为private](#条款22将成员变量声明为private)
- [条款23：宁以non-member、non-friend替换member函数](#条款23宁以non-membernon-friend替换member函数)
- [条款24：若所有参数皆需类型转换，请为此采用non-member函数](#条款24若所有参数皆需类型转换请为此采用non-member函数)
- [条款25：考虑写出一个不抛出异常的swap函数](#条款25考虑写出一个不抛出异常的swap函数)
- [条款26：尽可能延后变量定义式的出现时间](#条款26尽可能延后变量定义式的出现时间)














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



###### 条款06：若不想使用编译器自动生成的函数，就该明确拒绝

- 如果不想对象被赋值或者赋值的话，有以下解决方案
  - 将这个copy函数和赋值运算符变为私有
    - 但是friend函数和member函数会调用的到这个函数
  - 将copy函数和赋值运算符变为私有且只有函数声明
    - 但是会在连接器的位置发生报错
  - 设计一个base类，其copy和赋值函数设为私有，然后把我们需要的类继承该类
    - 即设一个uncopyable类，把我们需要用到的类都继承该类
- 请记住：为驳回编译器自动（暗自）提供的机能，可将相应的成员函数声明为private并且不予实现。或使用向uncopyable这样的base class也是一种做法



###### 条款07：为多态基类声明virtual析构函数

- 前提：当一份derived class对象经由一个base class指针被删除，而该base class带着一个non-virtual析构函数，结果是：实际执行时通常发生的是对象的derived成分没被销毁（因为只是调用了base class的析构函数，没有调用到derived class的析构函数），从而造成资源泄漏

- 解决办法：给base class的析构函数变为虚函数

- 如果不是base class，最好不要给析构函数加上virtual

  - 因为virtual需要虚函数表和其指针，所以会是class变大

- 当对象调用某一virtual函数，实际被调用的函数取决于该对象的vptr所指的那个vtbl-编译器在其中寻找适当的函数指针

- 注意：stl中的容器，包括string都是不带virtual析构函数的class

- pure virtual 函数，使得class变得abstract，不能被实例化

- 希望有抽象函数的办法：给他的析构函数变为纯虚函数（在类外需要给其一个定义，如果不给定义的话，那么他的子类就无法调用父类的析构函数）

  - ```cpp
    class AWOV{
        public:
        	virutal ~AWOV() = 0;
    }
    
    AWOV::~AWOV() = 0;
    ```

- 请记住：

  - 带多态性质的base class应该声明一个virtual析构函数，如果class带有任何virtual函数，它就应该拥有virtual析构函数
  - classes的设计目的如果不是作为base classes使用，或不是为了具备多态性，就不因该声明析构函数



###### 条款08：别让异常逃离析构函数

- 不能让析构函数吐出异常，因为这可能会使程序过早结束或出现不明确行为

- 解决办法：

  - 在析构函数中运用try catch，即如果抛出了异常就结束程序，通常通过调用abort完成

    - ```cpp
      DBConn::~DBConn(){
          try{db.close();}
          catch(...){
              std::abort();
          }
      }
      ```

  - 或者不用abort，直接记录下此次异常

- 请记住：

  - 析构函数绝对不要吐出异常（即不要因此而退出结束程序），如果一个被析构函数调用的函数可能抛出异常，析构函数应该捕获异常，然后吞下它们（不传播）或结束程序
  - 如果客户需要对某个操作函数运行期间抛出的异常做出反应，那么classes应该提供一个普通函数执行该操作



###### 条款09：绝不再构造和析构过程中调用virtual函数

- 对于一个子类，如果其父类的构造函数中调用了一个虚函数，效果会和设计者所想的截然不同

  - 一个虚函数决定它到底调用的是谁的虚函数看的是当前的对象是谁，如果是在父类里面调用，那就是父类的虚函数
    - 理由：调用子类函数必须要初始化子类的属性和对象的，而此时是还在父类函数里面，所以不可能调用得到子类函数的
    - 还有，在base class的构造期间对象的类型还是base class类型
  - 而设计者肯定是一位调用的是子类的虚函数类型（毕竟是创建一个子类嘛），所以是错误的
  - 相同的道理也适用于析构函数

- 而如果想要达到说，根据子类的不同调用函数，可以这样写

  - ```cpp
    class A{
      public:
        explicit A(const string& logInfo){
            logTransaction(logInfo);
        }
        void logTransaction(const string& logInfo) const;
    };
    
    class B: public A{
        public:
        	B(parameters):A(createLogString(parameters)){
            /*B的构建顺序是：先走B的构造函数，然后发现有初始值列表，则先初始化一个A对象（其实可以认为他的父类也是他的一个成员属性）*/
        	}
        private:
        	static string createLogString(parameters);
    }
    ```

  - 虽然我们无法使用virtual函数从base class向下调用对象，但是可以借助初始值列表，在子类构造的时候传入我们想要传入的信息给父类，从而达到这一点

  - 同时，下面的private和static函数也就不可能以外指向B类中未被初始化的成员便来给你parameters

- 请记住：

  - 在构造和析构期间不要调用virtual函数，因为这类调用从不下降至derived class（比起当前执行构造函数和析构函数的那层）



###### 条款10：令operator= 返回一个reference to *this

- 该条款不仅适用于以上的标准赋值形式，也适用于所有赋值相关运算

- 当需要连锁形式（链式编程）的时候，最好写成这样

  - ```cpp
    Widget& operator=(const Widget& rhs){
        //参数的const表示不可以改变传进来的蚕食，&表示是以引用接收的，节省空间
        //而上面的返回类型中，可以是void，但为了链式编程，就要改为Widget；用&同理，节省空间
        
        //而在返回方面，直接返回当前的对象，也是为了链式编程
        return *this;
    }
    ```

- 但不是必须要这样写，看情况吧

- 请记住：

  - 令赋值操作符返回一个reference to *this



###### 条款11：在operator=中处理“自我赋值”

- 在设计等于号的时候，容易出现自己给自己赋值的情况，如：两个指针都是指向同一个对象，如果不稍加注意的话，就会导致错误

- 所以，有以下几种解决办法

  - 方法一：

    - ```cpp
      Widget& Widget::operator=(const Widget& rhs){
          if (this == &rhs) return *this;//先判断两者是否是指向同一个对象
          //证同测试，如果是自我赋值，就不做任何事情
          
          delete pb;
          pb = new Bitmap(*rhs.pb);
          return *this;
      }
      ```

    - 缺点，缺乏异常安全性：如果new的过程出现问题，widget会指向一个错误的空间

  - 方法二：

    - ```cpp
      Widget& Widget::operator=(cosnt Widget& rhs){
          Bitmap* pOrig = pb;
          pb = new Bitmap(*rhs.pb);
          delere pOrig;
          return *this;
      }
      ```

  - 方法三：自己编写一个swap函数

    - ```cpp
      Widfet& Widget::operator=(const Widget& rhs){
          Widget temp(rhs);
          swap(temp);
          return *this;
      }
      ```

- 请记住：

  - 确保当对象自我复制时operator=有良好行为。其中技术包括比较“来源对象”和“目标对象”的地址、精心周到的语句顺序、以及copy-and-swap
  - 确定任何函数如果操作一个以上的对象，二其中多个对象是同一个对象时，其行为仍然正确



###### 条款12：复制对象时勿忘其每一个成分

- 特别是对于子类的拷贝构造函数和赋值运算符，要从两方面注意
  - 复制该类的所有local成员变量
  - 调用所有base class 内的适当的copying函数
    - 这里最好直接在初始值列写出（有一个好处就是如果base类中多加了一个属性，那么子类也不需要做很大的改动）
- 请记住：
  - copying函数应该确保复制“对象内的所有成员变量”及“所有base class成分”
  - 不要尝试以某个copying函数实现另一个copying函数，应该将共同机能放进第三个函数中，并由两个coping函数共同调用



###### 条款13：以对象管理资源

- 如果是程序员手动创建对象释放对象，随着代码量的增加容易造成失误，所以最好使用只能指针来管理对象
- RAII：资源取得时机便是初始化时机（Resource Acquisition Is Initialization）
- 两个关键思想：
  - 获得资源后立刻放进管理对象
  - 管理对象运用析构函数确保资源被释放
- 引用智能指针：
  - auto_ptr（受到auto_ptr管理的资源必须绝对没有一个以上的auto_ptr同时指向它）
    - 即A指向x，我让B再指向x的话，那么A就会变为null
  - shared_ptr（引用计数型智慧指针，持续追踪共有多少对象指向某笔资源，并在没人指向它时自动删除该资源）
    - 可以多个指针同时指向同个资源
- 请记住：
  - 为防止资源泄漏，请使用RAII对象，它们再构造函数中获得资源并在析构函数中释放资源
  - 两个被常使用的RAII classes分别是trl:shared_ptr和auto_ptr。前者通常是较佳选择，因为其copy行为比较直观，若选择auto_ptr，复制动作会使它指向null



###### 条款14：在资源管理类中小心copying行为

- 发生复制行为的时候，有以下两种操作：
  - 禁止复制，把copy函数变为私有，并让目标对象继承uncopyable类
  - 对底层对象使用引用计数法（shared_ptr）
- shared_ptr的删除器
- 原生指针：raw pointer
- 涉及浅拷贝和深拷贝的情况
  - 浅拷贝，多个指针共同指向一个对象
  - 深拷贝，复制出来一个相同的对象

- 请记住：
  - 复制RAII对象必须一并复制它所管理的资源，所以资源的copying行为决定RAII对象的copying行为
  - 普遍而常见的RAII class copying 行为是：抑制copying、施行引用集数法。不过其他行为也都可能被实现



###### 条款15：在资源管理类中提供对原始资源的访问

- 对于一个封装好的对象，往往需要对其原始资源进行处理

- 对于智能指针，shared_ptr和auto_ptr可以调用成员函数get()，返回智能指针内部的原始指针

- 而对于已封装好的类，有以下两种方法：

  - 第一种，写一个get函数，用于显示转换

    - ```cpp
      class Font{
          public:
          	FontHandle get() cosnt{
                  return f;
              }
          private:
          	FontHandle f;
      }
      ```

  - 第二种是隐式转换

    - ```cpp
      class Font{
          public:
          	operator FontHandle() const{
                  return f;
              }
      }
      
      Font f1(getFont());
      FontHandle f2 = f1;
      //这里的问题很多，比如两者都是指向同一个对象，如果删除的话，都会被删除；或者说，原意是要拷贝一个Font对象的，现在变为FontHandle了
      ```

    - 但是这种方法容易导致误用

- 请记住：

  - APIs往往要求访问原始资源，所以每一个RAII class应该提供一个“取得其所管理之资源”的办法
  - 对原始资源可能经由显式转换或隐式转换，一般而言，显式转换比较安全，但隐式转换对客户比较方便



###### 条款16：成对使用new和delete时要采取相同形式

- 对于new的操作，分为两步：

  - 内存被分配出来，通过名为operator new的函数
  - 针对此内存会有一个或多个构造函数被调用

- 对于delete的操作，分为两步：

  - 针对此内存会有一个或多个析构函数被调用
  - 然后内存才被释放，通过名为operator delete函数

- ```cpp
  string* stringPtr1 = new string;
  string* stringPtr2 = new string[100];
  
  delete stringPtr1;//删除一个对象
  delete[] stringPtr2;//删除一个由对象组成的数组
  ```

- 不要随意的给delete后面添加[]，因为可能会导致程序多次执行析构函数（也不要忘了加[]）

- 注意，特别是遇到typedef的情况，一定要注意delete是否需要加[]

- 请记住：

  - 如果你在new表达式中使用[]，必须在相应的delete表达式中也使用[]、如果你在new表达式中不适用[]，一定不要在相应的delete表达式中使用[]



###### 条款17：以独立语句将newed对象置入智能指针

- 考虑到以下情况

  - ```cpp
    int priority();
    void processWidget(shared_ptr<Widget> pw, int priority);
    
    processWidget(new Widget, priority());
    ```

  - 首先，智能指针的构造函数是一个explicit构造函数，无法进行隐式转换

  - 所以应该编写为`processWidget(shared_ptr<Widget>(new Widget), priority());`

  - 但是这里也可能会出现内存泄漏

    - 注意，对于一个函数而言，传进来的参数不一定是按照它传进来的顺序进行操作的
    - 而此时的执行步骤分为：（以下是不分先后的）
      - 执行”new Widget“
      - 调用shared_ptr的构造函数
      - 调用priority()函数
    - 如果出现了调用priority时出现了异常，那么前面的”new Widget“就会造成内存泄漏

  - 所以最终的解决办法是

    - ```cpp
      shared_ptr<Widget> pw(new Widget);
      processWidget(pw, priority());
      ```

- 请记住：
  - 以独立语句将newed对象存储于智能指针内，如果不这样做，一旦异常被抛出，有可能导致难以察觉的资源泄漏



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




###### 条款26：尽可能延后变量定义式的出现时间

- 看完这一条款，也就明白了为什么leetcode中的有些代码非要在使用某个变量之前才定义该变量

  - 对于工程代码，如果说前面的代码不需要某个变量，只有后面一部分才需要，而我们把所有的变量都定义在最前面，那么如果前面的部分代码出现了bug，那我最开始构造这个后面才用得到的变量岂不是浪费资源吗？

  - 同时，还有以下情况

    - ```cpp
      string encrpyPassword(const string& password){
          string encrypted;//这里调用了默认构造函数
          encrypted = password;//又调用了赋值函数
          encrypt(encrypted);
          return encrypted;
          
          //不如一把梭了它
          string encrypted(password);
      }
      ```

- 你不止应该延后变量的定义，直到非得使用该变量的前一刻为止，甚至应该尝试延后这份定义直到能够给它初值实参为止

- 请记住：

  - 尽可能延后变量定义式的出现，这样做可增加程序的清晰度并改善程序效率

