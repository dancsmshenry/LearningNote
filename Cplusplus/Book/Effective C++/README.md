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
- [条款37：绝不重新定义继承而来的缺省参数值](#条款37绝不重新定义继承而来的缺省参数值)
- [条款38、通过复合塑模出has-a或“根据某物实现出”](#条款38通过复合塑模出has-a或根据某物实现出)
- [条款39：明智而审慎地使用private继承](#条款39明智而审慎地使用private继承)
- [条款40：明智而审慎地使用多重继承](#条款40明智而审慎地使用多重继承)
- [条款41：了解隐式接口和编译期多态](#条款41了解隐式接口和编译期多态)
- [条款42：了解typename的双重意义](#条款42了解typename的双重意义)
- [条款43：学习处理模板化基类内的名称](#条款43学习处理模板化基类内的名称)
- [条款44：将与参数无关的代码抽离templates](#条款44将与参数无关的代码抽离templates)
- [条款45：运用成员函数模板接受所有兼容类型](#条款45运用成员函数模板接受所有兼容类型)
- [条款46：需要类型转换时请为模板定义非成员函数](#条款46需要类型转换时请为模板定义非成员函数)
- [条款48：认识template元编程](#条款48认识template元编程)
- [条款53：不要轻忽编译器的警告](#条款53不要轻忽编译器的警告)
- [条款54：让自己熟悉包括TR1在内的标准程序库](#条款54让自己熟悉包括tr1在内的标准程序库)
- [条款55：让自己熟悉Boost](#条款55让自己熟悉boost)








###### 条款01：视C++为一个语言联邦

- C++语言可以分为四个子语言
  - C。C++是以C为基础的（区块，语句，预处理器，内置数据类型，数组，指针）
  - Object-Oriented C++（class的构造和析构函数，封装，继承，多态，虚函数，动态绑定）
  - Template C++（泛型编程）
  - Stl（容器，迭代器，算法，函数对象）



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



###### 条款27：尽量少做转型动作

- cpp兼容c中的转型操作
  - （类型）expression

- cpp中四种新式类型转换

  - const_cast：通常被用来将对象的常量性转除（去掉const）
  - dynamic_cast：安全向下转型，用来决定某对象是否归属继承体系中的某个类型，是唯一无法由旧式语法执行的动作，也是唯一可能耗费重大运行成本的转型动作
  - reinterpret_cast：低级转型，实际动作以及结果可能取决于编译器，是不可移植的
  - static_cast：强迫隐式转换（什么都可以强转，维度不可以转const）

- 新转型的好处：

  - 容易在代码中被辨认出来；各转型动作的目标愈窄化，编译器愈可能诊断出错误的运用

- 参考以下代码

  - ```cpp
    class Window{
        public:
        	virtual void onResize();
    }
    
    class Special: public Window{
        virutal void onResize(){
            static_cast<Window>(*this).onResize();
            /*
            这段代码的想法是说，想要在子类使用父类的onResize函数（然后以为是调用的是Special类型去使用父类函数）
            
            但实际上，是通过this新建了一个Window对象，从而调用onResize函数
            这里就会有多余的开销，浪费时间和空间
            
            同时，如果是想要通过Window的onResize来修改当前对象的属性，是不可以做到的
            因为这是新建出来的一个副本，这样就不符合设计者的想法了
            而Special的onResize就可以修改当前的对象
            */
        }
    }
    
    //解决办法
    class Special: public Window{
        virtual void onResize(){
            Window::onResize();
        }
    }
    ```

- dynamic_cast速度比较慢

- 避免父类指针指向子类的问题：

  - 第一， 使用容器并在其中存储直接指向derived class的指针（使用类型安全容器）
  - 第二，利用多态，在base class内提供virtual函数做你想对各个window派生类做的事，这样就不会发生父类指针指向子类对象的情况（将virtual函数往继承体系上方移动）

- 请记住：

  - 如果可以，尽量避免转型，特别是在注重效率的代码中避免dynamic_cast，如果有个涉及需要转型动作，试着发展无需转型的替代设计
  - 如果转型是必要的，试着将它隐藏于某个函数背后，客户随后可以调用函数，而不需要将转型放进它们自己的代码内
  - 宁可使用cpp-style转型，不要使用旧式转型，前者很容易辨认，而且也有着比较分门别类的职掌



###### 条款28：避免返回handles指向对象内部成分

- 参考以下代码

  - ```cpp
    #include <iostream>
    #include <memory>
    
    using namespace std;
    
    class Point{
        public:
            Point(int x, int y) : x(x), y(y) {}
    
            void setX(int newx){x = newx;}
    
            void setY(int newy){y = newy;}
    
            int getX() const { return x; }
    
            int getY() const { return y; }
    
        private:
            int x;
            int y;
    };
    
    struct RectangleData{
        RectangleData(Point x, Point y) : ulhc(x), lrhcl(y) {}
        Point ulhc;
        Point lrhcl;
    };
    
    class Rectangle{
        public:
            RectangleData* r1;
    
            Rectangle(RectangleData* z):r1(z) { }
    
            Point& upperLeft() const{
                return r1->ulhc;
            }
    };
    
    int main(){
        Point p1(10, 20);
        Point p2(20, 30);
        RectangleData r11(p1, p2);
        const Rectangle r1(&r11);
    
        cout << "r1.upperleft().getX() = " << r1.upperLeft().getX() << endl;
        r1.upperLeft().setX(10000);
        cout << "r1.upperleft().getX() = " << r1.upperLeft().getX() << endl;
    }
    ```

  - 题外话：对于const的一个理解

    - 如果一个成员函数后面加上了一个const，就表示该函数不能对对象的属性做出变化

      - 这里有一个问题，什么是对象的属性？int，double，float都算是对象的属性吧，那如果是自己编写的对象呢？自己编写的对象的属性呢？
      - 经过测试，发现如果是以自己编写的对象作为实体的话，那么该对象如果作为一个大的对象的属性的话，该对象的属性也是不可变化的
      - 但，如果是把一个指向该对象的指针作为对象的属性的话，我感觉哈，应该是指针不可变，但是指针所指的该对象的属性是可以变的（即可以通过指针来修改对象属性的属性），那这样的话封装性就是不存在的了

    - 测试1：当函数为const的时候，是否可以修改对象的属性（包括基本类型和指针），发现是不可以的

      - ```cpp
        Point p3(10, 10);
        Point p4(100,100);
        
        class Rectangle{
            public:
                RectangleData* r1;
        
                Rectangle(RectangleData* z):r1(z) { }
        
                Point& upperLeft() const{
                    RectangleData* r2 = new RectangleData(p3, p4);
                    r1 = r2;//这里就会报错，因为const是保证对象的属性不发生变化，但是r1的指向，即r1所存储的地址发生了变化，不符合const，所以报错
                    return r1->ulhc;
                }
        };
        ```

    - 测试2：当函数为const的时候，是否可以修改对象的属性的属性（第一个属性为一个对象，第二个属性为前一个对象的属性），发现也是不可以的

      - ```cpp
        struct RectangleData{
            RectangleData(Point x, Point y) : ulhc(x), lrhcl(y) {}
            Point ulhc;
            Point lrhcl;
        };
        
        class Rectangle{
            public:
                RectangleData r1;
        
                Rectangle(RectangleData z):r1(z) { }
        
                Point& upperLeft() const{
                    return r1.ulhc;
                    /*
                    这里会报错：
                    首先，因为返回的是引用，本质是指针，可以借此来修改RectanglaData的ulhc
                    而被const修饰的函数是不可以修改对象的值的，所以会报错
                    */
                }
        };
        ```

  - ok，说完了题外话，这种方式就表明，即使是用const来修饰了变量，但是如果最终返回的是一个引用，还是有可能修改变更对象内部的值的，致使const变得无用。同样的，如果返回的是指针，或是迭代器，也是会间接修改对象的值的

    - 因为reference、point和迭代器都是handles（号码牌，用来取得某个对象）
    - 返回handles会使得对象的封装性减低，造成“虽然调用const成员函数却造成对象状态被更改”

  - 函数前面加上const表示函数的返回值不可被修改

  - 而如何解决上述问题呢？

    - ```cpp
      class Rectangle{
          public:
          	const Point& upperLeft() const{
                  return pData->ulhc;
              }
          
          	const Point& lowerRight() const{
                  return pData->lrhc;
              }//即在函数的前面加上const，防止返回的引用或指针或迭代器被修改
      }
      ```

- 另一个问题：

  - 如果让函数返回的是一个对象的话，并且还用指针来接收这个对象，就会导致在这条语句结束后，对象会被销毁，指针指向空值

- 请记住：

  - 避免返回handles（包括引用，指针，迭代器）指向对象内部。遵守这个条款可增加封装性，帮助const成员函数的行为像个const，并将发生“虚吊号码”的可能性降至最低



###### 条款29、为“异常安全”而努力是值得的

- 当异常被抛出时，带有异常安全性的函数会：
  - 不泄露任何资源（用对象来管理资源）
  - 不允许数据败坏
- 异常安全函数提供以下三个保证之一：
  - 基本承诺：如果异常被抛出，程序内的任何事物仍然保持在有效状态下，没有任何对象或数据结构会因此而败坏
  - 强烈保证：如果异常被抛出，程序状态不改变，如果成功，就完全成功，如果失败，程序会恢复到“调用函数之前”的状态
  - 不抛掷保证：承诺绝不抛出异常，因为它们总是能够完成它们原先承诺的功能
- 请记住
  - 异常安全函数即使发生异常也不会泄漏资源或允许任何数据类型结构败坏，这样的函数区分三种可能的保证：基本型，强烈型，不抛异常型、
  - “强烈保证”往往能够以“copy and swap”实现出来，但“强烈保证”并非对所有函数都可实现或具备现实意义
  - 函数提供的“异常安全保证”通常最高只等于其所调用之各个函数的“异常安全保证”中的弱者



###### 条款30：透彻了解inlining的里里外外

- 调用inline不需要蒙受函数调用所招致的额外开销

- inline可能增加你的目标码（过度使用）

- 如果inline函数的本体很小，编译器针对“函数本体”所产出的码可能比针对“函数调用”所产出的码更小（编译器会对inline函数进行优化）

- inline只是对编译器的一个申请

- 在类里面定义实现的成员函数都是inline

- 大部分编译器拒绝将太过复杂的函数inling，而所有的virtual都不会是inlining

- 总结：一个表面上看似inline的函数是否真实inline，取决于你的建置环境，主要取决于编译器

- 构造函数和析构函数往往都不是inline函数（它的底层非常精细复杂）

  - ```cpp
    Derived::Derived(){
        Base::Base();
        try{dm1.std::string::string()}
        catch(...){
            Base::~Base();
            throw;
        }
        ....
    }
    ```

- inline函数无法随着程序库的升级而升级，一旦程序设计者决定改变f，所有用到f的客户端程序都必须重新编译

  - 所以inline适合哪些比较小的，使用的多的，不会频繁更改的函数

- 请记住

  - 将大多数inlining限制在小型、被频繁调用的函数身上，这可使日后的调试过程和二进制升级更容易，也可使潜在的代码膨胀问题最小化，使程序的速度提升机会最大化
  - 不要只因为function templates出现在头文件，就将它们声明为inline



###### 条款31：将文件间的编译依存关系降至最低

- 背景：如果这些头文件中又任何一个被改变，或这些头文件所以来的其他头文件有任何改变，那么每一个函数Person class的文件就得重新编译，任何使用Person class的文件也必须重新编译
- 解决办法：
  - 接口和实现分离，一个头文件写实现（实现），另一个头文件写接口（接口）
  - 设计纯虚函数，后面写的类都调用这个接口
- 一些设计策略
  - 如果使用object references或object pointers可以完成任务，就不要使用objects
  - 如果能够，尽量以class声明式替换class定义式
  - 为声明式和定义式提供不同的头文件
- 请记住
  - 支持“编译依存性最小化”的一般构想是：相依于声明式。不要相依于定义式、基于此构想的两个手段是handle classes和interface classes
  - 程序库头文件应该以”完全且仅有声明式“的形式存在，这种做法不论是否设计templates都适用



###### 条款32:确定你的public继承塑模出is-a关系

- 类D以public的方式继承B，则表示每一个D都是一个B，即B比D表现出更一般化的概念，D比B表现出更特殊化的概念
- 所谓的最佳设计，取决于系统希望做什么事，包括现在和未来
- 这里有两个例子，引人深思：
  - 企鹅是鸟类吗，是的；那鸟类都会飞吗？第一感觉，是啊，鸟嘛，肯定会飞的嘛。但是事实上企鹅是不会飞的。
  - 所以如果要public继承鸟类的话，就要思考fly函数到底应该怎么放置才算好
    - 第一种，鸟类是分为会飞的和不会飞的，所以就让企鹅继承不会飞的鸟类即可
    - 第二种，重写企鹅的fly函数，令其在运行期发生报错
  - 那正方形是矩形吗？是的，那我写一个函数令矩形的一组边变大，如果正方形是直接继承使用的话，按照正方形的性质，这个函数应该令正方形所有的边都变大才对啊
- 所以，对于类与类之间的关系一定要慎重考虑
- 请记住：
  - public继承意味is-a。适用于base classes身上的每一件事情一定也适用于derived classes身上，因为每一个derived class对象也都是一个base class对象



###### 条款33：避免遮掩继承而来的名称

- 补充：

  - 虚函数是为了多态而生的，而不是因为继承同名而生，所以是纯虚函数才需要在继承后被重写，虚函数可以不被重写

- 在继承体系中，对于一个变量来说，是先在该函数内部进行查找，然后是在该子类中进行查找，接着再在其父类中进行查找，而后是在其命名空间查找

- 而对于一个函数也是一样

  - 如果父类和子类都有这个函数，那么一般情况下，父类的这个同名函数会被掩盖掉，只能调用得到子类的该名函数

    - 此时，如果想要调用父类的该函数的话，那就

      - ```cpp
        class Base{
            public:
            	void mf3(int z);
        };
        
        class Derived : public Base{
            public:
            	using Base::mf3;//使得Base中的mf3可以被子类看见
        }
        ```

  - 如果子类没有而父类有的话，那就调用父类的该函数

- 私有继承：父类的所有属性函数到子类都变为了private

  - ```cpp
    class Base{
        public:
        	virtual void func1() = 0;
        	virtual void mf1(int);
    };
    
    class Derived:private Base{
        public:
        	virtual void mf1(){
                Base::mf1();//暗自变为inline
            }
    }
    ```

  - inline转交函数的另一个用途是为那些不支持using声明式的老旧编译器另辟一条新路，将继承而得的名称汇入derived class作用域内

- 请记住：

  - derived classes内的名称会遮掩base classes内的名称，在public继承下从来没有人希望如此
  - 为了让被遮掩的名称再见天日，可使用using声明式或转交函数



###### 条款34：区分接口继承和实现继承

- 纯虚函数（pure virtual）（只继承接口）

  - 性质

    - 不能实例化有纯虚函数的类
    - 任何继承了这个类的类都必须重新声明该函数

  - 声明一个pure virtual函数的目的是为了让derived class只继承函数接口

    - 抽象类的纯虚函数是可以被定义的，也可被子类调用

      - ```cpp
        class Shape{
            public:
            	virtual void draw() const = 0;
        }
        
        class Rectangle{
            
        };
        
        Shape* ps = new Rectangle;
        ps->Shape:draw();
        ```

- 虚函数（impure virtual）（继承接口和一份强制实现）

  - 为多态而生
  - 目的：为了让子类继承该函数的接口和缺省实现
    - 对于每一个子类，最好都要继承重写这个函数，如果子类不写，也可以退回到父类的版本

- non-virtual函数（继承接口和一份强制实现）

  - 目的：为了令derived class继承函数的接口及一份强制性执行

- tips：

  - 不要把所有的函数都设为non-virtual，这样子类就无法特化操作
  - 也不要把所有的函数都变为virtual，感觉会加重子类的负担

- 请记住：

  - 接口继承和实现继承不同，在public继承之下，derived class总是继承base class的接口
  - pure virtual函数只具体指定接口继承
  - 简朴的impure virtual函数具体指定接口继承及缺省实现继承
  - non-virtual函数具体指定接口继承以及强制性实现继承



###### 条款35：考虑virtual函数以外的其他选择

- NVI（non-virtual-interface）
  - 将接口和实现分开，即接口设为public non-virtual函数，而实现函数变为private-virtual函数
- straegy设计模式



###### 条款36、绝不重新定义继承而来的non-virtual函数

- 问题背景：

- ```cpp
  #include <iostream>
  
  using namespace std;
  
  class A{
      public:
          void test(){
              cout << "A::test()" << endl;
          }
  };
  
  class B:public A{
      public:
          void test(){
              cout << "B::test()" << endl;
          }
  };
  
  int main(){
      B b1;
      A *a1 = &b1;
      a1->test();//A::test()，明明是B对象，但是后面调用的还是A对象的函数值
  }
  ```

- 原因：因为指针a1始终是指向A类型的指针，通过a1调用的non-virtual函数永远是A类型所定义的版本（本质：non-virtual是静态绑定的）

- 解决办法：virtual是动态绑定的

- 决定因素不在对象本身，而在于“指向该对象的指针”

- 结论：任何情况下都不应该重新定义一个继承而来的non-virtual函数



###### 条款37：绝不重新定义继承而来的缺省参数值

- virtual函数系动态绑定（late binding，就是在程序中被声明时所采用的类型），缺省参数值却是静态绑定（early binding，就是目前对象所指的类型）

- virtual函数是动态绑定，缺省参数值却是静态绑定，即有可能会出现“调用一个定义于derived class内的virtual函数，却使用了base class为它所指定的缺省参数”

  - 即B类继承了A类的虚函数，但是这个虚函数各自有各自缺省参数，以至于调用B类的虚函数，传进去的却是A类的缺省函数

- 解决办法：

  - 此前的方法

    - ```cpp
      class Shape{
          public:
          	virtual void draw(ShapeColor color = Red) const = 0;
      };
      
      class Rectangle :public Shape{
          public:
          	virtual void draw(ShapeColor color = Red) const;
      };
      ```

  - NVI手法后：

    - ```cpp
      class Shape{
          public:
          	void draw(ShapeColor color = Red) const{
                  doDraw(color);
              }
          
          private:
          	virtual void doDraw(ShapeColor color = Red) const = 0;
      };
      
      class Rectangle:public Shape{
          public:...
          private:
          	virtual void doDraw(ShapeColor color) const;
      };
      ```

- 请记住

  - 绝对不要重新定义一个继承而来的缺省参数值，因为缺省参数值都是静态绑定，而virtual函数——你唯一应该覆写的东西——却是静态绑定



###### 条款38、通过复合塑模出has-a或“根据某物实现出”

- 复合的意思是has-a（一个）或is-implemented-in-terms-of（根据某物实现出）
- 一个具体的场景
  - 想要写一个set，发现stl中有一个list可以复用，但是最后发现，list可以重复数据，而set不可以（这就是复用，感觉有点像侯捷之前说的委托）
  - 但还是想要用list来写，又发现两者不是is-a的关系，所以就用复合，即set中有一个数据成员是list，同时set的接口都用list来实现
- 请记住
  - 复合（composition）的意义和public继承是不一样的
  - 在应用层（application domain），复合意味has-a（有一个），在实物领域，复合意味着is-implemented-in-terms-of（根据某物实现出）



###### 条款39：明智而审慎地使用private继承

- 对于private继承

  - 编译器不会自动将一个derived class对象转换为一个base class对象（针对private继承来说）
  - 由private base class继承来的所有成员，在derived class中都会变为private属性

- private继承意味着：implemented in terms of（根据某物实现出）

- private主要用于：

  - 当一个意欲称为derived class者想访问一个意欲称为base class者的protected成分
  - 或为了重新定义一或多个virtual函数

- private继承不能使用多态了嘛？

  - ```cpp
    #include<iostream>
    
    class A{
        public:
            virtual void test(){
                std::cout << "A::test()" << std::endl;
            }
    };
    
    class B:private A{
        public:
            virtual void test(){
                std::cout << "B::test()" << std::endl;
            }
    };
    
    int main(){
        B b;
        A *a1 = &b;
        // b.test();
    }
    ```

  - 更加准确的说，对于私有继承，不能用父类指针指向子类对象

  - 所以，private继承确实不能用多态了

- 对于空对象

  - ```cpp
    class A{};//它的大小是1，里面有一个char字符；所以如果它作为一个类对象的成员的话，会占用一个字符
    //但是，如果一个空类作为一个基类，被子类私有继承了的话，就不会占用大小，如：
    
    class B:private A{
        int x;//sizeof(A) == sizeof(int)
    };
    ```

  - EBO(空白基类最优化)

- 请记住

  - Private继承意味is-implemented-in-terms-of（根据某物实现出）。通常比复合（compoosition）的级别低，但是当derived class需要访问protected base class的成员，或需要重新定义继承而来的virtual函数时（这里也表明了会导致多态失效），这么设计是合理的
  - 和复合（composition）不同，private 继承可以造成empty base最优化，这对致力于“对象尺寸最小化”的程序库开发者而言，可能很重要



###### 条款40：明智而审慎地使用多重继承

- 如果没有虚继承：A类继承了Base类，B类继承了Base类，C类同时继承了A类和B类，那么C类中就会有两个Base类，那到底该听谁的呢？

  - ```cpp
    class Base{
        int a;
    };
    
    class A:public Base{};
    
    class B:public Base{};
    
    class C:public B, public C{};//菱形继承
    
    C c1;//c1.a = ?，从逻辑上看，应该是只有一个a的
    
    //没有虚继承
    c1.A::a = 10;
    c1.B::a = 100;//用作用域来访问变量
    ```

- 解决办法：

  - ```cpp
    class Base{
        int a;
    };
    
    class A:virtual public Base{};
    
    class B:virtual public Base{};
    
    class C:public B, public C{};//菱形继承，虚继承来解决二义性
    ```

- cpp的解析规则：首先确认这个函数对此调用之言是最佳匹配，找出最佳匹配函数后才检验其可取用性

- 使用virtual继承的那些classes所产生的对象往往比使用non-virtual继承的兄弟吗体积大，访问virtual base classes的成员变量时，也比访问non-virtual base classes的成员变量速度慢

- virtual继承的成本

  - classes若派生自virtual bases而需要初始化，必须认知其virtual class
  - 当一个新的derived class加入继承体系，它必须承担其virtual class的初始化责任

- 忠告

  - 非必要不使用base classes
  - 尽量避免在其中放置数据

- 后面举了一个CPerson，IPerson和PersonInfo三个类关系的例子

  - CPerson需要实现PersonInfo类中的一些功能，那么就有两种实现方式：私有继承或复合
  - IPerson的话则是CPerson本应该继承的对象类
  - 所以这里就用到了多重继承

- 请记住

  - 多重继承比单一继承复杂，它可能导致新的歧义性，以及对virtual继承的需要
  - virtual继承会增加大小、速度、初始化（及赋值）复杂度等等成本，如果virtual base class不带任何数据，将是最具使用价值的情况
  - 多重继承的确有正当用途。其中一个情节涉及“public继承某个Interface class”和“private继承某个协助实现的class”的两相结合



###### 条款41：了解隐式接口和编译期多态

- 对于下列代码

  - ```cpp
    void test(Widget& w){
        if (w.size() ? 10 && w != someNastyWidget){
            Widget temp(w);
            temp.normalize();
            temp.swap(w);
        }
    }
    ```

  - 有关w的函数的调用，能够在源码中明确找到的，都可称为显式接口（是指类继承层次中定义的接口或者某个具体类提供的接口，在代码中能够直接找到的）

  - 但，某些成员函数是virtual的，w对它的调用将表现出运行期多态

- 而对于以下代码

  - ```cpp
    template<typename T>
    void test(Tt& w){
        if (w.size() ? 10 && w != someNastyWidget){//隐式接口，由有效表达式组成
            Widget temp(w);
            temp.normalize();
            temp.swap(w);
        }
    }
    ```

  - 像swap，normalize等函数接口，是T必须支持的一组隐式接口（即对于模板参数而言，这些函数接口都是隐式的，奠基于有效表达式；必须支持哪一种接口，要由模板参数执行于w身上的操作来决定）

  - 以不同的template参数具现化function templates，会导致调用不同的函数，这就是编译期多态

- 一个问题：运行期多态和编译期多态

  - 运行期多态以来的是虚函数机制，是直到运行的时候才知道类对象到底要调用哪一个函数
  - 编译期多态，以不同的模板参数具现化导致调用不同的函数（即因为我传进来的东西不同，导致我最后执行的不同；ps：而传进来又是在编译期执行），不同的推断结果调用不同的函数

- 通常显式接口是由函数的签名式（函数名称，参数类型，返回蕾西）组成

- 而隐式接口，是由有效表达式组成（重点是这个接口的实现带入模板函数中是否free bug）

- 总结：

  - classes和templates都支持接口（interfaces）和多态（polymorphism）
  - 对classes而言，接口是显式的（explicit），以函数签名为中心，多态则是通过virtual函数发生于运行期
  - 对templates而言，接口时隐式的，奠基于有效表达式，多态则是通过template具现化和函数重载解析发生于编译期



###### 条款42：了解typename的双重意义

- 在模板的声明中，typename和class没有什么不同

- template内出现的名称如果相依于某个template参数，称之为从属名称

  - 如果从属名称在class内呈嵌套状，则称为嵌套从属名称

- 不依赖任何template参数的名称，叫做谓非从属名称（独立名称）

- 对于嵌套从属名称，设想下列情景

  - ```cpp
    template<typename C>
    void point2nd(const C& container){
        C::const_iterator* x;//error, need 'typename' before 'C::const_iterator' because 'C' is a dependent scope
    }
    ```

  - 对于编译器而言，编译器无法识别这个`const_iterator`到底是一个什么东西，可能是static变量，可能是两个变量相乘

  - Cpp规则：如果解析器在template中遭遇一个嵌套从属名称，它便假设这名称不是个类型，除非你告诉它是。所以在缺省情况下，嵌套从属名称不是类型

  - 解决办法：

  - ```cpp
    template<typename C>
    void point2nd(const C& container, typename C::iterator iter){
        if (container.size() >= 2){
            typename C:const_iterator iter(container.begin());
            ...
        }
    }
    ```

  - 一般性规则：任何时候当你想要在template中指涉一个嵌套从属类型名称，就必须在紧邻它的前一个位置放上关键字同样typename

  - typename只被用来验明嵌套从属类型名称，其他名称不该有它的存在

  - **例外：**typename不可以出现在base classes list内的嵌套从属类型名称之前，也不可以在member initialization list（成员初始列）中作为base class修饰符

- 最后一个例子

  - ```cpp
    template<typename IterT>
    void workWithIterator(IterT iter){
        typename iterator_traits<IterT>::value_type temp(*iter);//萃取机，把容器里面的类型给提取出来，所以前面必须加上typename
        
        //可以简写
        typedef typename iterator_traits<IterT>::value_type value_type;
    }
    ```

- 总结

  - 声明template参数时，前缀关键字class和typename可互换
  - 使用关键字typename表示嵌套从属类型名称；但不得在base class lists或member initialization list内以它作为base class修饰符



###### 条款43：学习处理模板化基类内的名称

- 设想下列情景

  - ```cpp
    template<typename Company>
    class LoggingMsgSender:public MsgSender<Company>{
        public:
        	void sendClearMsg(const MsgInfo& info){
                sendClear(info);
                /**
                这里的问题是，对于模板的推导来说，它不知道这个sendClear是谁
                即不到Company的话，根本不知道sendClear这个函数,也不知道这个函数存不存在
                **/
            }
    };
    ```

  - 原因：base class template有可能被特化，而特化的版本可能不提供和一般性template的接口，所以template往往拒绝在templatized base classes（模板化基类）内寻找继承而来的名称（说白了，就是传进来的基类有可能不是常规的，你写的基类函数（如sendclear）可能在其他的基类中没有出现）

- ps：模板的偏特化

  - ```cpp
    template<>
    class MsgSender<Company2>{};
    ```

- 解决方案：

  - ```cpp
    template<typename Company>
    class LoggingMsgSender:public MsgSender<Company>{
        public:
        	void sendClearMsg(const MsgInfo& info){
                this->sendClear(info);//成立，加入sendClear被继承
            }
    };
    ```

  - ```cpp
    template<typename Company>
    class LoggingMsgSender:public MsgSender<Company>{
        public:
        	using MsgSender<Company>::sendClear;//告诉编译器，请它假设sendClear位于base class中
        	void sendClearMsg(const MsgInfo& info){
                sendClear(info);
            }
    };
    ```

  - ```cpp
    template<typename Company>
    class LoggingMsgSender:public MsgSender<Company>{
        public:
        	void sendClearMsg(const MsgInfo& info){
                MsgSender<Company>::sendClear(info);//明白指出被调用的函数位于base class中
                //但这种方案不好，因为这会关闭“virtual绑定行为”
            }
    };
    ```

- 例子：

  - ```cpp
    class A{
        public:
            int a;
    };
    
    template<typename T>
    class B{
        public:
            T t1;
    };
    
    template<typename T>
    class C:public B<T>{
        public:
            void fuc(){
                cout << B<T>::t1.a << endl;
            }
    };
    ```

- 总结：

  - 可在derived class template内通过“this->”指涉base class templates内的成员名称，或借由一个明白写出的“base class资格修饰符”完成



###### 条款44：将与参数无关的代码抽离templates

- review一下之前的知识

  - ```cpp
    template<typename T>
    class SquareMatrixBase{
        protected:
        	void invert(size_t matrixSize);
    };
    
    template<typename T, size_t n>
    class SquareMatrix:private SquareMatrixBase<T>{
        private:
        	using SquareMatrixBase<T>::invert;
        public:
        	void invert(){this -> invert(n);}//模板化基类内的函数会被derived classes覆盖
    };
    ```

- 其实，对于它书上说的逆矩阵的写法，我不是很理解，本来用一个模板一个参数就可以解决的，为什么要改为用多个模板才能解决啊？

- 对于类型参数导致的代码膨胀：int和long都有相同的二进制表达，但是有些编译器会把他们编译为两个不同的版本，使得代码膨胀

  - 解决办法：在大多数平台上，所有指针类型都有相同的二进制表述，即可以把`T*`都换为`void*`

- 请记住
  - Templates生成多个classes和多个函数，所以任何template代码都不该与某个造成膨胀的template参数产生相依关系
  - 因非类型模板参数而造成的代码膨胀，往往可消除，做法是以函数参数或class成员变量替换template参数
  - 因类型参数而造成的代码膨胀，往往可降低，做法是让带有完全相同二进制表述的具现类型共享实现码



###### 条款45：运用成员函数模板接受所有兼容类型

- 背景：对于传统的子类和父类，我们都可以用父类的指针指向子类对象。但是，对于有模板的子类和父类，做不到改变指针指向的类型，比如让子类指向父类

  - ```cpp
    template<typename T>
    class SmartPtr{
        public:
        	explicit SmartPtr(T* realPtr);
    };
    
    SmartPtr<Top> pt1 = Smart<Middle>{new Middle};//将SmartPtr<Middle>转换为SmartPtr<Top>
    ```

- 解决办法之一

  - ```cpp
    template<typename T>
    class SmartPtr{
        public:
        	template<typename U>
        	SmartPtr(const SmartPtr<U>& other);//不是explicit，可以用于隐式转换
        //表示对任何类型T和任何类型U，这里可以根据SmartPtr<U>生成一个SmartPtr<T>
    };
    ```

  - 在class内声明泛化copy构造函数并不会阻止编译器生成它们自己的copy构造函数

- 请记住
  - 请使用member function templates（成员函数模板）生成”可接受所有兼容类型“的函数
  - 如果你声明member templates用于”泛化copy构造“或”泛化assignment操作“，你还是需要声明政策的copy构造函数和copy assignment操作符



###### 条款46：需要类型转换时请为模板定义非成员函数

- 背景

  - ```cpp
    template<class T>
    class Rational{
        public:
        	Rational (const T& numerator = 0, const T& denominator = 1);
        	const T numerator() const;
        	const T denominator() const;
    };
    
    template<class T>
    const Rational<T> operator* (const Rational<T>& lhs, const Rational<T>& rhs){}
    
    Rational<int> oneHalf(1, 2);
    Rational<int> result = onHalf * 2;//这里的2不能隐式转换为Rational
    ```

  - 原因：template实参推导的时候从不将隐式类型转换函数考虑在内（但是可以将数组转换为数组指针之类的，都可以）

  - 解决办法：

    - ```cpp
      template<class T>
      class Rational{
          public:
          	friend const Rational<T> operator* (const Rational<T>& lhs, const Rational<T>& rhs);//把乘号设为friend函数
          	Rational (const T& numerator = 0, const T& denominator = 1);
          	const T numerator() const;
          	const T denominator() const;
      };
      
      template<class T>
      const Rational<T> operator* (const Rational<T>& lhs, const Rational<T>& rhs){}
      ```

    - 上述的代码可以过编译，但是无法执行：乘号函数被声明在类内，在类内没有被定义出来

    - 解决办法

      - ```cpp
        template<class T>
        class Rational{
            public:
            	//把乘号设为friend函数
            	friend const Rational<T> operator* (const Rational<T>& lhs, const Rational<T>& rhs){
                    return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
                }
            	Rational (const T& numerator = 0, const T& denominator = 1);
            	const T numerator() const;
            	const T denominator() const;
        };
        
        template<class T>
        const Rational<T> operator* (const Rational<T>& lhs, const Rational<T>& rhs){}
        ```

- 一路走来的奇怪的过程

  - 为了让类型转化可能发生于所有实参身上，我们需要一个non-member函数
  - 为了令这个函数被自动具现化，我们需要将它声明在class内部
  - 而在class内部声明non-member函数的唯一方法就是：令他成为一个friend

- 请记住
  - 当我们编写一个class template，而它所提供的“与此temlate相关的”函数支持“所有参数的隐式类型转换”时，请将那些函数定义为“class template内部的friend函数“



###### 条款48：认识template元编程

- template metaprogramming（TMP）是编写template-based C++程序并执行于编译期的过程

  - 是以cpp写成，执行于cpp编译器内部的程序，一旦tmp程序结束执行，其输出

- 两个优点：

  - 让某些事情更容易
  - 将工作从运行器转移到了编译期，导致某些结果通常在运行期才能侦测到的，现在可在编译期找到
  - 同时具有更小的可执行文件，较短的运行期，较小的内存需求

- 缺点：编译时间变长了

- traits的解法就是用TMP的，引发“编译器发生于类型身上的if..else计算”

- TMP的递归甚至不是正常种类，TMP循环不涉及递归函数调用，而是涉及“递归模板具现化”

- 元编程の初体验

  - ```cpp
    template<int n>
    struct Fasctorial{
        enum{value = n * Fasctorial<n - 1>::value};
    };
    
    template<>
    struct Fasctorial<0>{
        enum {value = 1};
    };
    
    int main(){
        cout << Fasctorial<10>::value;
    }
    ```

- 元编程的用途

  - 确保度量单位正确，在编译期确保程序中所有度量单位的组合正确
  - 优化矩阵运算，提高执行速度，占用较少内存
  - 可以生成用户定制的设计模式实现品

- 总结：

  - Template metaprogramming（TMP，模板元编程）可将工作由运行期移往编译期，因而得以实现早期错误侦测和更高的执行效率
  - TMP可被用来生成“基于政策选择组合”的客户定制代码，也可用来避免生成对某些特殊类型并不适合的代码



###### 条款53：不要轻忽编译器的警告

- 不同编译器的警告内容和警告标准都是不一样的
- 所以要好好学语法，否则有些错误导致的编译器的警告提示不匹配都很难debug的
- 请记住
  - 严肃对待编译器发出的警告信息。努力在你的编译器的最高（最严苛）警告级别下争取“无任何警告”的荣誉
  - 不要过度依赖编译器的报警能力，因为不同的编译器对待事情的态度并不相同。一旦移植到另一个编译器上，你原本依赖的警告信息有可能消失



###### 条款54：让自己熟悉包括TR1在内的标准程序库

- 其实，这就是cpp11的雏形
  - tuple
  - hash tables
  - array
  - smart pointers
  - traits
  - bing
- 请记住
  - cpp标准库的主要机能由STL，iostreams，locales组成，并包括c99标准程序库
  - TR1添加了智能指针（例如：tr1::shared_ptr）、一般化函数指针，hash-based容器，正则表达式以及另外10个组件的支持
  - TR1自身只是一份规范，为获得TR1提供的好处，你需要一份实物，一个好的实物来源是Boost



###### 条款55：让自己熟悉Boost

- Boost由委员会成员创设（目标：作为一个“可被加入标准c++之各种功能”的测试场）
- Boost接纳程序库的过程，它以公开进行的同僚复审为基础
- Boost包含的类目：
  - 字符串于文本处理
  - 容器：bitsets以及多维数组
  - 函数对象和高级编程
  - 泛型编程
  - 模板元编程
  - 数学和数值
  - 正确与测试
  - 数据结构
  - 语言间的支持
  - 内存
  - 杂项
- 请记住
  - Boost是一个社群，也是一个网站，致力于免费，源码开放，同僚复审的cpp程序库开发，Boost在cpp标准化过程中扮演深具有影响力的角色
  - Boost提供许多TR1组件实现品，以及其他许多程序库
