### 前言

- 介于cpp编译器对代码进行了更加深层次的优化，以致于书中的代码与实际操作不符，所以：
  - 首先是要坚信实际操作得到的结果，因为这就是现在的标准，书本上的就是老一套的，落后的代码
  - 其次，虽然书上的是过去的代码，过去的标准，但我认为书籍可能是会培养我们的理解和认识，加深对cpp对象模型的理解，让我们直到编译器在”私下“为我们做了什么事情，从而写出更加优秀的代码



### 名词解释

- 本书是中英文混合翻译的，所以有些名词光从翻译上来看无法窥知其中实意
- memberwise和bitwise
  - memberwise可以理解为平常的深拷贝，即对对象中的每一个元素都进行复制，如果对象的成员中有class object的话，也会直接复制一个对象出来
  - 而bitwise即为浅拷贝，就是逐位逐位的复制对象，如果对象的成员中有class object的话，那么就会直接把他的指针进行复制，而不会复制对象
  - 所以，浅拷贝会造成两个对象都指向同一个member的情况



### 第一章 关于对象

#### 1.1 对象模式

- 加上封装后的布局成本
  - c++在布局以及存取时间上的主要额外负担是由virtual引起的
    - virtual function机制，用以执行一个有效率的”执行期绑定“
    - virtual base class机制，用以实现”多次出现在继承体系中的base class，有一个单一而被共享的实例“
- 在c++中，有两种class data members：static和nonstatic，以及三种class member functions：static，nonstatic和virtual
- 简单对象模型
  - 对象里有一个point table，指针指向对象的data和function
- 表格对象模型
  - 对象里还是一个point table，但是里面只有两个指针，一个指向member data table，另一个指向 function member table
  - member data table里面存放的就是具体的数据，function member table就存放函数地址
- C++对象模型
  - nonstatic data members被配置于每一个对象里面
  - static data members存放在个别的对象之外
  - member function也存放在个别的对象之外
  - 而virtual function则有以下两步：
    - 每一个class产生一堆指向virtual function的指针，存放在表格之中，这个表格称为virtual table（vtbl）
    - 每一个class object被安插一个指针，指向相关的virtual table，通常称为vptr
    - vptr的设定和重置都由class的构造函数，拷贝函数，赋值运算符决定
    - 每个class所关联的type_info也由vtbl决定，通常被放在表格的第一位
  - 在virtual 继承中，无论派生多少次，base class只有一个
- 对象模型如何影响程序
  - 这里后续肯定要放一张图片在这里的

#### 1.2 关键词所带来的差异

- 

#### 1.3 对象的差异

- cpp支持三种程序设计范式
  - 程序模型（和C一样，以面向过程为主）
  - 抽象数据模型（所谓的抽象是和一组表达式（接口）一起提供的）
  - 面向对象模型（类与类之间有了关系，出现了继承复合等关系）
- cpp通过以下方法实现多态
  - 经由一组隐式的转化操作，例如把一个derviced class指针转化为一个指向其public base type的指针
  - 经由



### 第二章 构造函数语意学

#### 2.1 Default Constructor 的构造操作

- 分清楚是编译器的需要还是程序的需要
- 带有 default constructor 的 member class object 
  -  如果A类包含B类，但是没有显式的写出A类的默认构造函数，那么编译器就会自动为你提供一个隐式的构造函数，这个构造函数会根据情况调用B类的构造函数
  - 但是这个隐式的构造函数，不会对类中的数据（int，double 等数据）进行初始化的（这是程序员的需要，不是编译器的需要）
  - 如果 class A 内含一个或一个以上的 member class objects，那么 class A 的每一个 constructor 必须调用每一个 member classes 的 default constructor
    - 即如果一个类的成员包含多个类，那么这个类的每一个构造函数都会调用其包含的类的构造函数
    - 调用的顺序和声明的顺序一样
    - 即编辑器会为我们的代码进行扩张
- 带有 default constructor 的 base class 
  - 如果一个没有任何 constructors 的 class 派生自一个“带有 default constructor ”的 base class，那么这个 derived class 的 default constructor 会被视为 nontrivial，并因此需要被合成出来，它将调用上一层 base classes 的 default constructors





#### 2.3 程序转化语意学

- 显式的初始化

  - 源代码是这样的:

  - ```cpp
    void foo_bar(){
        A a1(a0);//a0可能是一个全局变量
        A a2 = a0;
        A a3 = A(a0);
    }
    ```

  - 但是经过编译器的扩充，可能会变成这样：

  - ```cpp
    void foo_bar(){
        A a1;//定义被重写，初始化操作被剥除
        A a2;
        A a3;
        
        a2.A::A(a0);//调用拷贝构造函数
        a3.A::A(a0);
        a4.A::A(a0);
    }
    ```

  - 总结：普通的显式初始化操作，是要先调用默认构造函数创建对象，然后再调用拷贝构造函数把值赋给对象

- 参数的初始化

  - 把一个class object当作参数传给一个函数（或作为一个函数的返回值），相当于以下操作：

  - ```cpp
    void foo(X x0);
    
    //编译器的拓展操作
    X _temp0;//生成临时对象
    
    _temp0.X::X(x0);
    
    void foo(X& x0);//因为传入的是临时对象，所以原函数也要被修改
    
    foo(_temp0);//传入临时对象
    ```

  - 而另一种实现方式是拷贝建构，把实际参数直接建构在应该的位置上，此位置视函数活动范围的不同，记录于程序堆栈中

  - 总结：参数的初始化是先根据值拷贝出一个临时对象，然后改造原函数，把临时对象传入

- 返回值的初始化

  - 把一个局部对象值作为函数值返回，相当于以下操作：

  - ```cpp
    X bar(){
        X xx;
        //具体的操作
        return xx;
    }
    
    //会被改造成这样
    void bar(X& _result){
        X xx;
        xx.X::X();//编译器的默认构造函数
        //一些具体的操作
        
        _result.X::X(xx);//拷贝构造函数
        
        return ;
    }
    ```

  - 即先创建一个要返回的对象_result，这个对象就是赋值用的对象，然后对原函数进行改写，把 _result传入函数中，进行上述的操作

  - 总结：返回值的初始化也是先建立一个临时对象，改造原函数，然后再在函数里面建立一个新的对象，对新的对象进行处理过后，赋值拷贝给临时对象

- 在使用者层面做优化

  - 源代码：

  - ```cpp
    X bar(const T &y, const T &z){
        X xx;
        
        return xx;//这里的观点认为，编译器还为你临时建立了一个新的变量，十分浪费
    }
    ```

  - 改造为：

  - ```cpp
    X bar(const T &y, const T&z){
        return X(y, z);//认为这样更好？？？
    }
    ```

  - 我觉得还不如原来的写法呢

- 在编译器层面做优化

  - 上述编译器的优化都叫做NRV（named return value）
  - 一般来说，面对“一个class object作为另一个class object的初值”的情形，语言允许编译器有大量的自由发挥空间，其利益当然是导致机器码产生时有明显的效率提升，缺点则是你不能够安全规划你的copyconstruct的副作用，必须视其执行而定

- Copy Constructor:要还是不要？

  - 如果一个类里面没有member成员，就没必要自己手写一个拷贝构造函数
  - 如果想要哟个memset()实现对象的拷贝，注意虚函数的情况，可能会改变其内部的vptr



#### 2.4 成员们的初始化队伍

- 为了使程序顺利编译，以下四种情况必须使用member initialization list：

  - 当初始化一个reference member时
  - 当初始化一个const member时
  - 当调用一个base class的构造函数时，而且它有一组参数
  - 当调用一个member class的构造函数时，而且它有一组参数

- 例如：

  - ```cpp
    class Word{
        String _name;
        int _cnt;
        
      public:
        	Word(){
                _name = 0;
                _cnt = 0;
            }
    };//如果构造函数没有初始化列表，那么Word（）实质是这样的
    
    Word::Word(){
        _name.String::String();//创建一个String对象
        String temp = String(0);//产生一个临时对象
        _name.String::operator=(temp);//memberwise的拷贝
        temp.String::~String();//摧毁临时对象
        
        _cnt = 0;
        
        //这样做的成本就是消耗很高
    }
    
    //而用列表优化后变为
    Word:Word(){
        _name.String::String(0);
        _cnt = 0;
    }
    ```
    
  - 而这种情况在template中经常发生

    - ```cpp
      template<class type>
      foo<type>::foo(type t){
          _t = t;//如果是一般类型那就没事，但是如果是class类型，就最好用列表初始化
      }
      ```

- 列表初始化的具体操作：执行列表初始化，以适当顺序在constructor之内安插初始化操作，并在任何explicit user code之前

- 注意：list中的项目顺序是由class中的members声明顺序决定的，不是由列表中的排序决定的



### 第三章 Data 语意学

#### 3.1 Data Member 的绑定

- 影响对象大小的三个因素
  - 语言本身所造成的额外负担（如virtual带来的）
  - 编辑器对代码的优化（有些编译器会优化对象的模型和大小）
  - Alignment的限制（结构对齐，将数值调整到某个数的整数倍）
- 编译器的优化
  - 对于一个空类，一般的编译器会认为它的大小为1，里面只有一个char大小的类型
  - 而一些编译器则对其进行了优化，认为它的大小为0
  - 编译器之间的差异说明cpp对象模型的演化
- 

#### 3.2 Data Member 的布局

#### 3.3 Data Member 的存取

#### 3.4 ”继承“与Data Member

#### 3.5 对象成员的效率

#### 3.6 指向 Data Members 的指针



### 第四章 Funciton 语意学

#### 4.1 Member 的各种调用方式

- Nonstatic Member Functions（非静态成员函数）

  - 要和 nonmember function由相同的效率
  - 编译器内部的转化动作：
    - 改写函数原型，以安插一个额外的参数到 member function 中，该额外参数是 this 指针
    - 将每一个”对 nonstatic data member 的存取操作“改为经由 this 指针来存取
    - 将 member function 重新写成一个外部函数，将函数名称经过” mangling “处理，使它在程序中成为独一无二的语汇
  - 名称的特殊化处理：
    - 一般，member的名称钱买你会加上class名称，形成独一无二的命名

- Virtual Member Functions（虚拟成员函数）

  - ```cpp
    ptr -> normalize();//源代码，normalize为一个虚函数
    (* ptr -> vptr[1])(ptr);//会被转化为这样
    ```

  - tips:每一个类只有一个虚函数表

  - vptr表示由编译器产生的指针，指向virtual table

  - 1 是virtual table slot的索引值，关联到 normalize() 函数

  - 第二个 ptr 表示 this 指针

- Static Member Functions （静态成员函数）

  - ```cpp
    obj.normalize();//都是静态函数
    ptr->normalize();
    //都会被转化为下列代码
    normalize_7Point3dSFv();
    normalize_7Point3dSFv();
    ```

  - 一个思路：其实，如果对象的函数没有涉及到对象的数据的处理更改的话，是可以不通过对象来调用函数

  - 静态成员函数的特性：

    - 不能直接存取 class 中的 nonstatic members
    - 不能够被声明为 const，volatile 或 virtual
    - 不需要经由class 才被调用

