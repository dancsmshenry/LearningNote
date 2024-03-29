# 2.1 类对象所占用的空间

- 空类的大小是1，内存中的一个地址单元里面保存的是1个字节的内容（即便是一个空类的对象，但因为在内存中是有起始地址的，既然这个地址属于该对象，该对象必然最少能存得下一个字节）
- 类的成员函数是不占用类对象内存空间的
- 空类的大小为1（即空类的大小为1，里面存放的是该对象的地址）
- 成员变量是包含在每个对象中，是占用对象字节的
- 而成员函数虽然也写在类的定义中，但成员函数不占用对象字节数（不占内存空间）
- 成员函数在每个类中只有一个

<br/>

<br/>

# 2.2 对象结构的发展和演化

- 非静态的成员变量保存在对象内部
- 静态变量不会保存在对象内部，而是保存在对象外面
- 成员函数不管是静态还是非静态的，或者是虚函数，全都保存在类对象之外
- 虚函数
  - 一个类中只要有虚函数，这个类就会产生一个指向虚函数的指针
  - 虚函数指针指向虚函数表，该表一半保存在最后i可执行文件中，在程序执行的时候载入到内存中
  - 虚函数指针指向虚函数表
- 指针大小是固定的，4字节还是8字节取决于平台
- 注意padding（内存字节对齐）
- 非静态的成员变量（普通成员变量）跟着对象走（存在对象内部），也就是每个类对象都有自己的成员变量
- 静态成员变量和对象没有关系，所以肯定不会保存在对象内部，是保存在对象外面（表示所占用的内存空间和类对象无关）
- 成员函数：不管静态的还是非静态的，全部都保存在类对象之外，所以不管几个成员函数，不管是不是静态的成员函数，对象的大小不会因此改变
- 虚函数：不管几个虚函数，sizeof()都是多了4/8个字节（多放了一个虚指针）
- 类里只要有一个虚函数（或者至少有一个虚函数），这个类就会产生一个指向虚函数的指针
  - 有多少个虚函数就有多少个虚函数指针
  - 类本身，指向虚函数的指针，要有地方放，所以存放在一个表格里面，这个表格就是虚函数表 virtual table vtbl
  - 这个虚函数表一般是保存在可执行的文件中，在程序执行的时候载入到内存中
  - 虚函数表是基于类的，跟着类走的
  - 为什么会多出4/8个字节，因为虚函数的存在，导致系统往类对象中添加了一个指针
  - 这个指针正好指向这个虚函数表，很多资料上把这个指针叫做vptr
  - 这个vptr的值由系统在适当的时候(比如构造函数中通过增加额外的代码来给值)
  - 虚函数表存储虚函数的地址，即虚函数表的元素是指向类成员函数的指针
- 总结：
  - 静态数据，普通成员函数和静态成员函数都不计算到对象的大小上
  - 虚函数也不计算到类对象的大小上，但是虚函数会让类对象的大小增加4个字节以容纳虚函数表指针
  - 虚函数表vtbl是基于类的（跟着类走的，和对象没有关系）
  - 虚函数表存放的是函数的指针
  - 如果有多个数据成员，那么为了提高访问速度，某些编译器可能会将数据成员之间的内存占用比例进行调整（内存字节对齐）
  - 不管什么类型的指针，大小都是一样的
- 总结类对象大小的组成
  - 非静态成员变量
  - 内存字节对齐
  - 虚函数指针
  - PS：如果类之间有多重继承的关系，并且每个父类都有虚函数

<br/>

<br/>

# 2.3 this指针调整

- 应用于多继承场景
- A,B；C类先后继承A类和B类，所以C类的this指针和A类的指针都是相同的，A类指针和B类指针差了一个类A的大小
- 总结1：如果一个派生只继承了一个基类，那么这派生类对象和基类子对象地址相同
- 如果派生类对象同时继承多个基类，那么第一个基类子对象的起始地址和派生类对象起始地址相同
- 总结2：调用哪一个子类的成员函数，这个this指针就会被编译器自动调整到对象内存布局中对应该子对象的起始地址去
- 派生类对象 是包含基类子对象的
- 如果派生类只从一个基类继承来的话，那么这个派生类对象的地址和它的基类子对象的地址相同
- 但如果派生类对象同时继承多个基类：
  - 第一个基类子对象的开始地址和派生类对象的开始地址相同
  - 后续这些基类子对象的开始地址 和派生类对象的开始地址相差多少，那就得把前面那些基类子对象所占用的内存空间干碎
- 总结：调用哪个子类的成员函数，这个this指针就会被编译器自动调整到对象内存布局中，对应该子类对象的起始地址去

<br/>

<br/>

# 2.4 分析obj（目标文件）与构造函数语义

- obj文件是微软编译器编译cpp文件后得到的中间文件
- 编译器生成“合成默认构造函数”的几种情况
  - 第一种情况：该类没有任何构造函数，但包含一个类类型的成员变量，而且该成员变量有一个默认构造函数
  - 第二种情况：父类带有默认构造函数，子类没有任何构造函数（父子类的构造是由内而外的）
  - 第三种情况：一个类含有虚函数，该类没有任何构造函数（需要创建虚函数表和虚指针）
  - 第四种情况：如果一个类带有虚基类，编译器也会为它生成一个“合成默认构造函数”
  - 第五种情况：如果在定义成员变量的时候赋初值，cpp11支持这种新语法
- 传统观念认为，如果我们自己没定义任何构造函数，那么编译器就会为我们隐式自动定义一个默认的构造函数
  - 我们称这种构造函数为合成的默认构造函数
- 事实上：合成默认构造函数，只有在必要的时候，编译器才会为我们合成出来，而不是必然或者必须为我们合成出来
- 第一种情况：该类没有任何构造函数，但包含一个对象类型的成员，并且该对象所属的类有一个缺省构造函数
  - 这时，编译器就会为该类生成一个 合成默认的构造函数，合成的目的是为了调用上述类的缺省构造函数
  - 换句话，编译器合成了默认的构造函数，并且在其中安插代码，调用成员对象类的缺省构造函数

<br/>

<br/>

# 2.5 拷贝构造函数语义与移动构造函数语义

拷贝构造函数

- 如果没有定义自己的拷贝构造函数，编译器会在必要的时候合成一个拷贝构造函数
- 如果是这种简单类型，直接就按值拷贝过来，编译器在不需要合成拷贝构造函数
- 第一种情况：如果一个类A没有拷贝构造函数，但该类有一个类类型的成员变量，该类含有拷贝构造函数
  - 结论：只是一些类成员变量的值复制这些简单的事情，编译器不用专门生成拷贝构造函数来做，编译器内部就可以完成
- 第二种情况：如果该类没有拷贝构造函数，它有一个父类，且这个父类构造函数有拷贝构造函数
- 第三种情况：如果一个类没有拷贝构造函数，该类定义了虚函数或者该类的父类定义了虚函数
- 第四种情况：如果一个类没有拷贝构造函数，但是该类含有虚基类



移动构造函数

- 如果一个类定义了自己的拷贝构造函数、拷贝赋值运算符或者析构函数，编译器就不会为该类生成出移动析构函数和移动赋值运算符
- 只有一个类没定义任何自己版本的拷贝构造函数、拷贝赋值运算符、析构函数，且类的每个非静态成员都可以移动时，编译器才会为该类合成移动构造函数或者移动赋值运算符
  - 内置类型的成员便来给你可以移动
  - 如果成员变量是一个类类型，如果这个类有对应的移动操作相关的函数，则该成员变量可以移动



- 第二种情况：父类带缺省构造函数，子类没有任何构造函数，那因为父类这个缺省的构造函数要被调用，所以编译器会为这个子类合成出一个默认构造函数

  - 合成的目的：为了调用父类的构造函数，换句话说，编译器为它合成了默认的构造函数，并在其中安插代码，调用其父类的缺省构造函数

- 第三种情况：如果一个类含有虚函数，但没有任何构造函数时

  - 因为虚函数的存在，编译器会为我们生成一个基于该类的虚函数表
  - 编译器为它合成了默认的构造函数，并在其中安插代码，把类的虚函数表地址赋给类对象的虚函数表指针（赋值语句/代码）：
  - 我们可以把虚函数表指针看成是我们表面上看不见的一个类的成员函数（把虚函数表的首地址赋值给虚指针）
  - 即使有默认构造函数，编译器还是会为我们额外添加代码：
    - 生成虚函数表；调用父类的构造函数；因为虚函数的存在，把类的虚函数表地址赋给对象的虚函数表指针

- 当我们有自己的默认构造函数时，编译器会根据需要扩充我们自己写的构造函数代码，比如调用父类的构造函数，给对象的虚函数表指针赋值

- 编译器干了很多事，没默认构造函数时必要情况下帮助我们合成默认构造函数，如果我们有自己的默认构造函数，编译器会根据需要扩充默认构造函数的代码

- 第四种情况：如果一个类带有虚基类，编译器也会为它合成一个默认构造函数（虚基类：通过两个直接基类继承同一个基类，所以一般是三层）

  - 虚基类结构，编译器为子类和父类都产生了“合成的默认构造函数”

- 传统上，大家认为如果我们没有定义一个自己的拷贝构造函数，编译器会帮助我们合成一个拷贝构造函数

- 这个合成的拷贝构造函数，也是在 **必要**的时候才会被编译器合成出来

- ```cpp
  A a1;
  a1.a = 10;
  A a2 = a1;//这里没有为其合成拷贝构造函数
  //这里其实是编译器内部的一种手法，成员变量初始化手法，比如int这种简单类型，直接就按值拷贝过去，编译器不需要合成拷贝构造函数就可以实现
  //同时，这是递归实现的，即如果A里面还有一个对象A1，A1里面有int类型的话，那么也是会递归的去按值拷贝的
  //这种按值拷贝会出现在所有的拷贝构造函数里面
  ```

- 某些情况下，如果我们不写自己的拷贝构造函数，编译器就会帮助我们合成出拷贝函数来

  - 第一种情况：如果一个类A没有拷贝构造函数，但是含有一个类类型CTB的成员变量，该CTB含有拷贝构造函数，那么当代码中有涉及到类A的拷贝构造时，编译器就会为类A合成一个拷贝构造函数
  - 第二种情况：如果一个类A没有拷贝构造函数，但是它的父类CTB有拷贝构造构造函数，那么当代码中有涉及到类A的拷贝构造时，编译器就会为类A合成一个拷贝构造函数
  - 第三种情况：如果一个类A没有拷贝构造函数，但是该类声明了或继承了虚函数，那么当代码中有涉及到类A的拷贝构造时，编译器就会为类A合成一个拷贝构造函数（这个语句的含义是，设定类对象的虚函数指针值，虚函数表指针，虚函数表等概念）
  - 第四种情况：如果一个类A没有拷贝构造函数，但是该类继承了虚基类，那么当代码中有涉及到类A的拷贝构造时，编译器就会为类A合成一个拷贝构造函数

- 编译器合成的拷贝构造函数往往都是干一些特殊的事情，如果只是一些类成员变量值的拷贝，是不用专门生成拷贝构造函数的，内部就会干的

<br/>

<br/>

# 2.6 程序转换语义

定义时初始化对象

- ```cpp
  X x0;
  X x2(x0);
  //程序员写的代码
  
  X x3_2;
  x3_2.X::X(x0);
  //cpp内部转化的代码
  ```



参数的初始化

- 当把实参传递给形参的时候，调用了拷贝构造函数

- ```cpp
  void func(X tempx){
      return ;
  }
  //这里会调用X的拷贝函数和析构函数
  ```



返回值初始化

- 返回对象的时候，也会调用拷贝构造函数，把局部对象拷贝给返回的对象

<br/>

<br/>

# 2.7 程序的优化

- 从开发者和编译器的角度对程序进行优化

- ```cpp
  X test(X& ts) {
      X tmpm;//这里生产了临时对象，消耗了两个
      tmpm.x1 = ts.x1 * 2;
      tmpm.x2 = ts.x2 * 2;
      return tmpm;
      
      //优化后
      return X(ts.x1 * 2, ts.x2 * 2);
  }
  ```

- 我们写的代码，编译器会对代码进行拆分，拆分成编译器更容易理解和实现的代码

- 站在程序员角度和站在编译器角度看代码

- ```cpp
  //1、定义时初始化对象（编译器视角）
  X x100;//步骤一：定义一个对象，为对象分配内存，从编译器的角度来看，这句是不调用X类的构造函数的
  x100.X::X(x0);//步骤二：直接调用对象的拷贝构造函数
  //等价于下列语句
  X x3(x0);
  ```

- ```cpp
  //2、参数初始化（程序员视角）
  void func(X tempx) {//因为这里是拷贝出来的一个临时对象，所以会调用拷贝构造函数
      return ;
  }//出来的时候会析构tempx
  X x1;
  func(x1);
  //上面是现代编译器的
  
  //老编译器的视角
  X tempoj;//编译器产生一个临时对象
  tempoj.X::X(x0);//调用拷贝构造函数
  func(tempoj);//用临时对象调用func
  void func(X& tempx) {//这里改为了引用传递了
  }
  tempoj.X::~X();//析构临时对象
  ```

- ```cpp
  //3、返回值初始化
  X func() {
      X x0;
      //...
      return x0;//系统产生临时对象并把x0的内容拷贝构造给了临时对象
  }
  
  //编译器的角度
  void func(X &extra) {
      X x0;//这里不会调用构造函数
      //..
      //..
      extra.X::X(x0);
      return ;
  }
  
  //返回值初始化（程序员角度）
  X my = func();
  
  //编译器的角度
  X my;//不会调用构造函数
  func(my);
  ```

- ```cpp
  func().functest();//通过函数返回的临时对象调用成员函数
  
  //切换到编译器视角
  X my;//不会调用构造函数
  (func(my), my).functest();//逗号表达式，返回值是第二个值
  ```

- ```cpp
  //程序员视角
  X(*pf)();//定义一个函数指针
  pf = func;
  pf().functest();
  
  //编译器视角
  X my;//不调用构造函数
  void (*pf)(X &);
  pf = func;
  pf(my);
  my.functest();
  ```

从开发者层面的优化

- ```cpp
  //原函数
  X Double(X& ts){
      X temp;
      temp.x1 = ts.x1 * 2;
      temp.x2 = ts.x2 * 2;
      return temp;
  }//因为里面生成了一个对象（后续需要析构里面的临时对象），返回的又是一个临时对象（拷贝给返回值以后又要析构）
  
  //优化后的
  X Double(X& ts){
      return X(ts.x1 * 2, ts.x2 * 2);
  }
  //这样，就减少了一次析构
  ```

从编译器层面的优化

<br/>

<br/>

# 2.8 程序优化续、拷贝构造函数续与深浅拷贝

- ```cpp
  class A {
      public:
          A() = default;
          A(int value): m_i(value) {//类型转换函数
              cout << "A(int)" << endl;
          }
          A(const A& other): m_i(other.m_i) {
              cout << "A(const A&)" << endl;
          }
          int m_i;
          ~A() {
              cout << "~A()" << endl;
          }
  };
  
  int main() {
      A x10(100);//没有优化的情况下，这种写法效率最高
      cout << "--------------------------------" << endl;
      A x11 = 100;
      cout << "--------------------------------" << endl;
      A x12 = A(100);
      cout << "--------------------------------" << endl;
      A x13 = (A)100;
      cout << "--------------------------------" << endl;
  }
  
  //结果：（g++ -fno-elide-constructors test.cpp -o test）关闭优化了的
  A(int)
  --------------------------------
  A(int)
  A(const A&)
  ~A()
  --------------------------------
  A(int)
  A(const A&)
  ~A()
  --------------------------------
  A(int)
  A(const A&)
  ~A()
  --------------------------------
  ~A()
  ~A()
  ~A()
  ~A()
  
  //上述代码在msvc中运行得到的都是一样的，但是在linux下的gcc下关闭优化的情况下运行，就不一样
  //从编译器视角来看（不优化）
  //第一行
  X x1;
  x1.X::X(100);
  //第二行
  X temp0;
  temp0.X::X(1000);//带一个参数的构造函数被调用
  X x2;
  x2.X::X(temp0);//拷贝函数被调用
  temp0.X::~X();//调用析构函数
  ```

- 总结：

  - 当编译器面临用一个类对象作为另一个类对象初值的情况，各个编译器表现不同，但是所有编译器都为了提高效率而努力
  - 我们也没有办法确定我们自己使用的编译器是否一定会调用拷贝构造函数

- 拷贝构造函数是否必须要有？视情况而定

  - 如果只有一些简单的类型变量，根本不需要拷贝构造函数，编译器内部本身就提供支持成员变量的bitwise copy（按位拷贝）

程序优化续

- ```cpp
  class A{
      public:
      	A(int value){
              cout << "A(int value)" << endl;
          }
  };
  
  A a = 100;//会调用转换函数
  ```



拷贝构造续

- 编译器自带的拷贝是bitwise（按位）赋值
- 当处理一些很复杂的成员变量类型的时候，就将指针变量作为类的成员变量
- 程序员往类中增加了拷贝构造函数后，就要对类中各个成员变量的初始化负责



深浅拷贝

- 深拷贝和浅拷贝的区别
- 浅拷贝：对于类定义中有指针变量的情况，只复制指针值，指针所指向的地址编译器并没有额外做处理

<br/>

<br/>

# 2.9 成员初始化列表

何时必须用成员初始化列表

- 成员变量是引用类型时
- 成员变量是const类型

- 如果该类继承自一个基类，并且基类中有构造函数，这个构造函数里还有参数
- 如果类中成员变量的类型是某个类类型，而这个类类型所指类的构造函数带有参数



使用初始化列表的优势

- 提高程序效率（可以在这节的代码里面看优化详情）



初始化列表的细节探究

- 初始化列表中的代码可以看作被编译器安插在构造函数中的
- 是在构造函数的函数体代码执行之前被执行
- 其中成员变量的初始化顺序，是这些变量在类中定义的顺序



何时必须用成员初始化列表

- 如果这个成员是个引用
- 如果是个const类型成员
- 如果这个类是继承一个基类，并且基类中有构造函数，这个构造函数里面还有参数
- 如果你的成员变量类型是某个类类型，而这个类的构造函数带参数时

- 使用初始化列表的优势

  - 提高程序的运行效率

  - ```cpp
    class A{
        public:
            int m_i;
            A(int value = 0):m_i(value) {
                cout << this << endl;
                cout << "A(int)构造函数调用" << endl;
            }
            A(const A&mid) {
                cout << this << endl;
                cout << "A拷贝构造函数调用" << endl;
            }
            A& operator=(const A&tmp) {
                cout << this << endl;
                cout << "A的operator=函数调用" << endl;
                return *this;
            }
            ~A() {
                cout << this << endl;
                cout << "A析构函数调用" << endl;
            }
    };
    
    class B{
        public:
            A m_a;
        
            B(int tmp) {//会调用两次int构造函数，一次operaotr=函数，两次析构函数
            /*
            因为在这一行（最开始的一行）会创建一个m_a对象，然后下面又要把tmp先转换为A类
            再调用=赋值给m_a
            相当于多调用了一遍构造析构和operator=
           	从编译器的视角来看：
           	A aobj;
           	aobj.A::A();
           	//上面是一开始就安插好了的
           	A taobj;//生成一个临时对象
           	taobj.A::A(1000);//临时对象调用构造函数
           	aobj.A::opeartor=(taobj);//调用拷贝赋值运算符
           	taobj.A::~A();//调用析构函数回收对象
            */
            
            
            // B(int tmp) : m_a(tmp){//只调用一次析构一次int构造
            /*
            而这里就直接解决了，从一开始就是调用int构造函数
            从编译器的视角来看：
            A m_a;
            m_a.A::A(1000);
            */
                m_a = tmp;
            }
    };
    
    int main() {
        B b1(1000);
        cout << &b1.m_a << endl;
    }
    ```

  - 对于类类型成员变量放到初始化列表中能够比较明显的看到效率的提升

  - 但如果是个简单类型的成员变量，比如int，其实放到初始化列表或者放在函数体里效率差别不大

  - 最好写在初始化列表中，更加专业，高端

- 初始化列表细节探究

  - 初始化列表中的代码可以看作是被编译器安插到构造函数体中，只是这些代码有些特殊
  - 这些代码 是在任何用户自己的构造函数体代码之前被执行的，所以要区分构造函数中用户代码和编译器插入的 初始化所属的代码
  - 这些列表中变量的初始化顺序是 定义顺序，而不是在初始化列表中的顺序（所以不要相互赋值）
    - 建议不在初始化列表中进行  两个 都在初始化列表中出现的成员之间的赋值