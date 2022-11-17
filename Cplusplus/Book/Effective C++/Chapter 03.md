# 条款13：以对象管理资源

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



# 条款14：在资源管理类中小心copying行为

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



# 条款15：在资源管理类中提供对原始资源的访问

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



# 条款16：成对使用new和delete时要采取相同形式

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



# 条款17：以独立语句将newed对象置入智能指针

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