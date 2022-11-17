# 虚函数和多态

- 类与类之间的关系：复合，委托，继承（对于函数，继承是继承了函数的调用权）

- non-virtual 函数：不希望 derived class 重新定义它（override）

- virutal 函数：希望derived class 重新定义它（override），且对它已经有了默认定义

- pure virtual 函数：希望derived class 一定要重新定义它（override），并且对其没有默认定义

- ```cpp
  class A{
    public:
      //如果子类要重写这个虚函数的话，那么就要把原函数的所有修饰词都抄下来，包括const
      virtual void draw() const = 0;//pure virtual
      virtual void error();//impure virtual
      int objectID() const;//non-virtual
  };
  ```

- 通过子类对象调用父类函数，而在父类函数里面有调用在子类中定义好的纯虚函数（设计模式：template method），很多框架的实现都是这样的

  - 而这种实现，就是依赖虚函数表（因为是在子类调用的父类函数，所以传入的this也是子类对象）

- 继承（inheritance）和复合（composition）的构造和析构

  - 子类继承父类，子类中又复合一个类对象
    - derived object中包含了base part和component
    - 两者的构造顺序上（在我的机器上，gcc9.2，windows，64位机器上），是先调用base part，再调用component，最后调用derived object
    - 析构的顺序就全部相反了，先derived object，再component，最后base part
  - 子类继承父类，父类中又复合一个类对象
    - base part中有一个component，derived object继承了base part（即component最里层，base part第二层，derived object第三层）
    - 先调用component，再调用base part，最后调用derived object
    - 析构则倒过来执行

- 委托（delegation）和继承（inheritance）