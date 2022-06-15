# 条款7：在创建对象时注意区分()和{}

- 在cpp11中，可以用大括号或中括号来初始化对象

  - ```cpp
    int x(0);	//	初始化在小括号内
    
    int y = 0;	//	初始化在等号之后
    
    int z{0};	//初始化在大括号内
    
    int a = {0}; // 使用等号和大括号来指定初始化物
    
    Widget w1; // 调用的是默认构造函数
    
    Widget w2 = w1; // 调用的是复制构造函数
    
    w1 = w2; // 调用的是复制构造函数
    ```





- cpp11的统一初始化：单一的，至少从概念上可以用于一切场合、表达一切意思的初始化

- 它的基础是大括号形式

- ```cpp
  // 指定容器的初始内容
  std::vector<int> v{1,2,3};
  
  int x{0};
  
  // 类对象里面成员的初始化
  class A {
  public:
      int x = 0; // ok
      int y{0}; // ok
      int z(0); // error
  }
  
  //对于不可复制的对象，也可以用大括号和小括号来初始化
  atomi<int> a1{0};
  atomi<int> a2(0);
  atomi<int> a3 = 0;//error
  ```





特点1：禁止内建类别之间进行隐式窄化类别转换

- 是指不能从大的变量强转为小的变量

- ```cpp
  doublie x, y ,z;
  int sum1{x + y + z};//error，double之和无法用int来表示
  int sum2(x + y + z);//ok
  ```



特点2：对解析语法免疫

- c++的一个标准就是任何能够解析为声明的都要解析为声明

- ```cpp
  Widget w1(10);//一般的调用构造函数
  
  Widget w2();//原意想要创建一个空的类对象，但是变为了一个函数的声明
  
  //解决办法：{}
  Widget w3{};//创建空对象
  ```





缺点1：initializer_list

- 对于一个类，只要形参中没有任何一个具备initializer_list型别，那小括号或大括号就没有区别

- 可，如果有了的话，即有一个或多个构造函数声明了任何一个具有initializer_list类型的形参，那么采用了大括号初始化语法的调用语句会优先选用initializer_list类型形参的重载版本

- ```cpp
  class Widget{
      public:
      	Widget(initializer_list<long double> i1);
      	Widget(int i, double b);
      	operator float() const;
  };
  
  Widget w1(10, 1.1);//调用的是第二个
  Widget w2{10, 1.1};//调用的是第一个
  Widget w3{10, true}; // 调用的是第一个（将数据强转为long double即可）
  
  Widget w3(w2);//调用复制函数
  Widget w4{w2};//调用initializer_list的那个函数
  // 这里是先强转为long double，在调用
  ```

- 但，如果initializer_list里面的参数不符合就会匹配其他的构造函数了

- ```cpp
  vector<int> v1(10, 20);//创建了一个10个元素的，每个的值都是20
  vector<int> v2{10, 20};//创建了一个含有两个元素的vector，10和20
  
  Widget w4({});//带有initializer_list的构造函数传入一个空的initializer_list里面
  ```

- 只有在找不到任何办法把大括号初始化物中的实参转换成std::initializer_list模板时，才会退而去检查普通的重载协议





### 要点速记

- 大括号初始化可以应用的语境最为宽泛，可以阻止隐式窄化类型转换，还对最令人苦恼的解析语法免疫
- 在构造函数重载决议期间，只要有任何可能，大括号初始化就会与带有std::initializer_list类型的形参相匹配，即使其他重载版本有着貌似更加匹配的形参表
- 使用小括号还是大括号，会造成结果大相径庭的一个例子是：使用两个实参来创建一个std::vector<数值类型>对象
- 在模板内容进行对象创建时，到底应该使用小括号还是大括号会成为一个棘手问题







# 条款8：优先选用nullptr，而非0或NULL

- ```cpp
  void f(int);
  void f(bool);
  void f(void*);
  
  f(0); // 在cpp98中，调用的是f(int)
  f(NULL);
  f(nullptr); // 调用的是f(void*)
  ```



- 优点：不具备整型型别，也不具备指针型别，但是可以把它想象成一种任意类型的指针
- 本质：实质是：std::nullptr_t，可以隐式转换到所有的裸指针类型





情景1

- ```cpp
  auto result = findRecord(/**实参**/);
  
  if (result == 0){}//表示不清楚，具有多义性
  
  if (result == nullptr){}
  ```





情景2

- 模板下方便使用，用于区别0,NULL,nullptr
- 模型型别的推导会将0和NULL推导为错误类型





### 要点速记

- 相对于0或NULL，优先选用nullptr
- 避免在整型和指针类型之间重载







# 条款9：优先选用别名声明，而非typedef

情景一

- 代码的可读性高

- ```cpp
  typedef unique_ptr<unordered_map<string, string>> UPtrMapSS;//cpp98的写法
  
  using UPtrMapSS = unique_ptr<unordered_map<string, string>>;//cpp11的写法
  
  // FP是⼀个指向函数的指针的同义词，它指向的函数带有int和const std::string&形参，不返回任何东西
  typedef void (*FP)(int, const std::string&); // typedef
  
  //同上
  using FP = void (*)(int, const std::string&); // 别名声明，这样写就更加的清晰易懂
  ```



情景二

- 更加方便

- ```cpp
  //	cpp11的写法，可以认为这是个非依赖性的类型
  template<typename T>
  using MyAllocList = list<T, MyAlloc<T>>;
  
  MyAllocList<Widget> lw;
  
  //	cpp98的写法，这个更加复杂了的
  template<typename T>
  struct MyAllocList{
      typedef list<T, MyAlloc<T>> type;
      //	带依赖的类型前必须要加上typename
  };
  
  MyAllocList<Widget>::type lw; // 用户代码
  
  //	为什么说typedef不好，是因为有以下这种奇怪的情况
  template<>
  class MyAllocList<Wine>{
      enum class WineType{
          White, Red, Rose
      };
      WineType type;
  };
  
  MyAllocList<Widget>::type lw;
  ```

- 因为编译器不能确定MyAllocList<Widget>::type到底是不是定义了一个类型，比如上面所说的，这也是为什么编译器坚持让你通过在前面一个typename来断定这个意思
- 而对于编译器来说，MyAllocList<T>必然是一个类型的名字





### 要点速记

- typedef不支持模板化，但别名声明支持
- 别名模板可以让人免写“::type”后缀，并且在模板内，对于内嵌typedef的引用经常要求加上typename前缀





# 条款11：优先选用删除函数，而非private未定义函数

- 在C++98中防⽌调⽤这些函数的⽅法是将它们声明为私有成员函数
- 意味着如果一段代码仍然可以访问它们（如成员函数，或类的友元）并使用了它们，链接阶段就会由于缺少函数定义而告失败（就是说其实过得了编译，过不了链接）
  - 简述：如果把复制构造函数给私有了，但是又在成员函数中使用了复制构造函数，那么程序是过得了编译，但是过不了链接的（复制构造函数不给他链接）
- 但是如果改用delete的话，那么代码是过不了编译的（编译器上就会提示错误）
- 删除函数无法通过任何方法调用，即使成员或者友元函数都不可以





- 另一个优点，所有的函数都可以是删除函数，而私有函数只能是成员函数

- ```cpp
  bool isLucky(int number); // 原始版本
  bool isLucky(char) = delete; // 拒绝char
  bool isLucky(bool) = delete; // 拒绝bool
  bool isLucky(double) = delete; // 拒绝float和double
  ```

- 防止强转





- 最后一个优点，阻止那些不应该进行的模板具体的实现

- ```cpp
  template<typename T>
  void processPointer(T* ptr); // 有些模板的特化版本是我不想要的，就删除了
  
  template<>
  void processPointer<void>(void*) = delete;
  template<>
  void processPointer<char>(char*) = delete;
  ```





情景三

- 想要禁用一个类里面其中模板的一个特化版本

- ```cpp
  class Widget {
  public:
  …
  template<typename T>
  void processPointer(T* ptr)
  { … }
  …
  };
  template<>
  void Widget::processPointer<void>(void*) = delete; // 还是public，但是已经被删除了
  ```

- 为什么把该模板私有化达不到这样的效果

  - 是因为模板特例化必须位于⼀个命名空间作⽤域，而不是类作⽤域





### 要点速记

- 优先选用删除函数，而非private未定义函数
- 任何函数都可以删除，包括非成员函数和模板具现





# 条款12：为意在改写的函数添加override声明









# 条款15：只要有可能使用constexpr，就使用它

- 在编译阶段已知的值有以下好处
  - 可能被放置在只读内存里面
- constexpr用于函数身上
  - 若传入的是编译期常量，则产出编译期常量
  - 如果是直至运行期才知晓的值，则产出运行期值
- 解释
  - constexpr函数可以用在要求编译期常量的语境中，若传给constexpr函数的实参值在编译期未知，则你的代码无法通过编译
  - 若传入的值有一个或多个在编译期未知，则它的运作方式和普通函数无异
- 在cpp11和cpp14的不同
  - 在cpp11中，constexpr函数不得包含多于一个可执行语句（有点类似函数式编程了）
  - 在cpp14中，可以写多条语句
- 用处：一些在运行期才能完成的操作，现在在编译期就可以完成
- 异同
  - 在cpp11中，一个类的成员函数如果修改了其成员变量，那么就不可以设为constexpr
    - 因为，constexpr都被隐性地设为了const
    - 同时，如果一个类的成员函数返回的是void，也不可以设为constexpr
  - 但是在cpp14中，这些限制都被取消了
- 对于单个变量而言，constexpr和const的作用一样，不过constexpr是在编译期就完成了初始化了的
- 对于函数而言
  - 如果传进来的实参是能够在编译期就知道的话（就不用去推导，例如现成的int，double，char，已设好的类对象之类的，就是编译期常量；对立面就是auto之流的需要执行才知道类型的），则其结果也会在编译期间计算出来
  - 否则，即出现了说有变量是在编译期无法得知的，那就和普通函数一样，在执行期执行
  - 同时发现在constexpr函数里面无法指向io操作，输入输出的操作



### 要点速记

- constexpr对象都具备const属性，并由编译期已知的值完成初始化
- constexpr函数在调用时若传入的实参值时编译期已知的，则会产出编译期结果
- 比起非constexpr对象或constexpr函数而言，constexpr对象或是constexpr函数可以用在一个作用域更广的语境中