###### 条款1：理解模板类型推导

- 对于

- ```cpp
  template<typename T>
  void f(ParamType param);
  
  f(expr);
  ```

- 情况一：ParamType是个指针或引用，但不是个万能引用

  - 若expr具有引用类型，就先将引用部分忽略（类型推导的过程中会把引用部分给忽略掉）

  - 而后，对expr的类型和ParamType的类型执行模式匹配，来决定T的类型

  - ```cpp
    template<typename T>
    void f(T& param);//这里加上const的话，T的类型是不会变的，param就会在前面加上const
    //或者说这里变为指针的话也是一样的，T的推导类型还是和没加一样，只是后面param的推导会跟着变
    
    int x = 27;
    f(x);//T的类型是int
    
    const int cx = x;
    f(cx);//T的类型是const int，param是const int&
    
    const int& rx = x;
    f(rx);//T的类型也是const int，param是const int&
    ```

  - 总结：凡是以引用或指针来接收参数的，都直接忽略原来是否是引用；而像const和指针的，原封不动的匹配进去

- 情况二：ParamType是个万能引用

  - 万能引用`T&&`

  - 如果expr是一个左值，T和ParamType都会被推导为左值引用

  - 如果expr是一个右值，则用情况一的规则

  - ```cpp
    template<typename T>
    void f(T&& param);
    
    int x = 27;
    f(x);//x是一个左值，T的类型就是int&，param也是int&
    
    const int cx = x;
    f(cx);//cx也是一个左值，T的类型就是const int&，param也是const int&
    
    const int& rx = x;
    f(rx);//rx是左值，T的类型就是const int&，param也是const int&（这里会忽略原参数的&）
    
    f(27);//27是一个右值，T的类型就是int，param则是int&&
    ```

  - 总结：

    - 面对万能引用的类型，如果传进来的是左值，那T和paramtype直接变为左值引用（传进来的就是T的类型和const）
    - 右值就根据类型推导出T的类型，paramType就是T&&

- 情况三：ParamType既非指针也非引用（即值传递）

  - 直接忽略其引用部分，const部分和volatile对象

  - 例外：如果是const修饰的引用或指针，const会因此保留(const仅会在按值形参处被忽略）)

  - ```cpp
    template<typename T>
    void f(T param);
    
    const char* const ptr = "hello world!";
    
    f(ptr);//传递的类型是const char* const
    ```

- 数组实参

  - 对于一个函数，如果直接传入数组，传入后会退化为指针（即如果直接操作传进来的数组，那就是操作数组本身了）

  - ```cpp
    void temp(int[] arrayy);
    
    //退化为
    void temp(int* arrayy);
    ```

  - 但是可以声明引用

  - ```cpp
    template<typename T>
    void f(T& param);//这就是真正的数组，不过传入的也还是数组的引用
    ```

- 函数实参

  - 同数组实参一样，直接传的话也是传入函数指针；传引用的话就是传函数引用

- 要点速记

  - 在模板型别推导过程中，具有引用型别的实参会被当作非引用型别来处理。换言之，其引用性会被忽略
  - 对万能引用形参进行推导时，左值实参会进行特殊处理
  - 对按值传递的形参进行推导时，若实参型别中带有const或volatile饰词，则它们还是会被当作不带const或volatile饰词的型别来处理
  - 在模板型别推导过程中，数组或函数型别的实参会退化成对应的指针，除非它们被用来初始化引用



###### 条款2：理解auto型别推导

- auto的类型推导和templat的推导（条款1的情况）大概都是一样的

  - ```cpp
    auto x = 27;//第三种情况
    
    const auto cx = x;//第三种情况
    
    const auto& rx = x;//第一种情况
    
    auto&& uref1 = x;//第二种情况，传入的左值都变为左值引用，即int&
    
    auto&& uref2 = cx;//同上，const int&
    
    auto&& uref3 = 27;//右值，就直接推导，即int&&
    ```

  - ```cpp
    const char name[] = ":::";
    
    auto arr1 = name;//const char*
    
    auto& arr2 = name;//const char(&)[]
    ```

- 但是也有例外

  - ```cpp
    auto x1 = 27;//int
    auto x2(27);//int
    auto x3 = {27};//initializer_list<int>
    auto x4{27};//initializer_list<int>
    
    auto x5 = {1, 2, 3.0};//error
    
    template<typename T>
    void f(T parm);
    f({1, 2, 3.0});//模板不可以推导出initializer_list<int>
    ```

  - 即auto可以通过`{}`来推导出`initializar_list`，而template需要专门来写

- 例外之二

  - 在cpp14中，可以用auto来说明函数返回值从而推导出来（不过这种auto是在使用模板型别推导而非auto推导）

  - ```cpp
    auto createInitList(){
        return {1,2,3};//error
    }
    ```

  - lambda也是同理

  - ```cpp
    vector<int> v;
    auto resetV = [&v](const auto& newValue){
        v = newValue;
    }
    
    reset({1,2,3});//error
    ```

  - tips：模板就不要推导`{}`了，会报错（auto作为返回值的话也是同理）



###### 条款3：理解decltype

- 在cpp11中，decltype的主要用途大概就在于声明那些返回值型别依赖于形参型别的函数模板

- 即decltype可以推导出括号里面的对象的类型，并用于其他的对象

- 返回值类型尾序语法（cpp11允许对表达式的lambda式的返回值类型实施推导）

  - ```cpp
    template<typename Container, typename Index>
    auto authAndAccess(Container& c, Index i)->decltype(c[i]){
        ...
    }
    //该函数的返回值类型时将在形参类型之后（“->”之后），好处：在指定返回值型别时可以使用函数实参
    ```

- 参考一个背景

  - ```cpp
    template<typename Container, typename Index>
    auto test(Container& c, Index i){
        return c[i];
    }
    ```

  - 这里看起来是直接返回一个数组的具体的数字，但是这里的auto推导其实是还是模板推导（参考条款2），所以返回的其实是一个右值，即不能像左值一样操作

  - 使用`decltype(auto)`来解决

  - ```cpp
    template<typename Container, typename Index>
    decltype(auto) test(Container& c, Index i){
        return c[i];
    }
    ```

- 这里挖坑（有点看不懂decltype（auto）的例子，今后再看）

- 要点速记

  - 绝大多数情况下，decltype会得出变量或表达式的型别而不作任何修改
  - 对于类型为T的左值表达式，除非该表达式仅有一个名字，decltype总是得出类型T&
  - cpp14支持decltype(auto)，和auto一样，它会从其初始化表达式出发来推导类型，但是它的类型推导使用的是decltype的规则



###### 条款4：掌握查看型别推导结果的方法

- 撰写代码阶段，编译阶段，运行时阶段
- 第一种方法：IDE编译器的报错提示
- 第二种方法：编译器诊断信息
- 第三种方法：运行时输出（利用`typeid`对类型进行推导输出）
- 要点速记
  - 利用IDE编译器，编译器错误消息和Boost TypeIndex库常常能够查看到推导而得的类型
  - 有些工具产生的结果可能会无用，或者不准确，所以，理解cpp型别推导规则是有必要的



###### 条款5：优先选用auto，而非显示式类型声明

- 用auto声明的变量，其类型都推导自其初始化物，所以它们必须初始化

- 在cpp14中可以这样写

  - ```cpp
    auto derefless = [](const auto& p1, const auto& p1){
        return *p1 < *p2;//把auto作为变量的命名
    }
    ```

- 情景一：std::function

- vector的长度为`std::vector<int>::size_type`

- 情景二：面对size_type在不同平台的表现，用auto来表示size最好

- 情景三：

  - ```cpp
    std::unordered_map<std::string, int> m;
    
    for (const std::pair<std::string, int>& p:m){
        
    }
    //上述代码出现问题，因为pair里面的键值部分应该是const的，而声明的变量却不是；结果编译器就要把pair<const stirng, int>转换为pair<string, int>对象，非常耗时耗力
    
    //解决办法
    for (const auto& p:m){}
    ```

- auto类型可以随着其初始化表达式的类型变化而自动变化

- 要点速记

  - auto变量必须初始化，基本上对会导致兼容性和效率问题的类型比匹配现象免疫，还可以简化重构流程，通常也比显式指定类型要少打一些字
  - auto类型的变量有着条款2和条款6所描述的毛病



###### 条款7：在创建对象时注意区分()和{}

- 在cpp11之前，可以用大括号或中括号来初始化对象

  - ```cpp
    int x(0);//初始化在小括号内
    
    int y = 0;//初始化在等号之后
    
    int z{0};//初始化在大括号内
    
    int a = {0};
    ```

- cpp11的同意初始化：单一的，至少从概念上可以用于一切场合、表达一切意思的初始化

  - 基础是大括号形式

  - ```cpp
    std::vector<int> v{1,2,3};
    
    int x{0};
    
    //对于不可复制的对象，也可以用大括号和小括号来初始化
    atomi<int> a1{0};
    atomi<int> a2(0);
    atomi<int> a3 = 0;//error
    ```

  - 特点1：禁止内建类别之间进行隐式窄化类别转换

  - ```cpp
    doublie x, y ,z;
    int sum1{x + y + z};//double之和无法用int来表示
    int sum2(x + y + z);//ok
    ```

  - 特点2：对解析语法免疫

  - ```cpp
    Widget w1(10);//一般的调用构造函数
    
    Widget w2();//原意想要创建一个空的类对象，但是变为了一个函数的声明
    
    //解决办法：{}
    Widget w3{};//创建空对象
    ```

  - 缺点1：initializer_list

  - 对于一个类，只要形参中没有任何一个具备initializer_list型别，那小括号或大括号就没有区别

  - 可，如果有了的话，即有一个或多个构造函数声明了任何一个具有initializer_list类型的形参，那么采用了大括号初始化语法的调用语句会优先选用initializer_list类型形参的重载版本

  - ```cpp
    class Widget{
        public:
        	Widget(initializer_list<long, double> i1);
        	Widget(int i, double b);
    };
    
    Widget w1(10, 1.1);//调用的是第二个
    Widget w2{10, 1.1};//调用的是第一个
    
    Widget w3(w2);//调用复制函数
    Widget w4{w2};//调用initializer_list的那个函数
    ```

  - 但，如果initializer_list里面的参数不符合就会匹配其他的构造函数了

  - 其他

  - ```cpp
    vector<int> v1(10, 20);//创建了一个10个元素的，每个的值都是20
    vector<int> v2{10, 20};//创建了一个含有两个元素的vector，10和20
    
    Widget w4({});//带有initializer_list的构造函数传入一个空的initializer_list里面
    ```

- 要点速记

  - 大括号初始化可以应用的语境最为宽泛，可以阻止隐式窄化类型转换，还对最令人苦恼的解析语法免疫
  - 在构造函数重载决议期间，只要有任何可能，大括号初始化就会与带有std::initializer_list类型的形参相匹配，即使其他重载版本有着貌似更加匹配的形参表
  - 使用小括号还是大括号，会造成结果大相径庭的一个例子是：使用两个实参来创建一个std::vector<数值类型>对象
  - 在模板内容进行对象创建时，到底应该使用小括号还是大括号会成为一个棘手问题



###### 条款8：优先选用nullptr，而非0或NULL

- ```cpp
  void f(int);
  void f(bool);
  void f(void*);
  
  f(0);
  f(NULL);
  f(nullptr);
  ```

- 优点：不具备整型型别，也不具备指针型别，但是可以把它想象成一种任意类型的指针

  - 本质：实质是：std::nullptr_t，可以隐式转换到所有的裸指针类型

- 情景1

  - ```cpp
    auto result = findRecord(/**实参**/);
    
    if (result == 0){}//表示不清楚
    
    if (result == nullptr){}
    ```

- 情景2

- 要点速记
  - 相对于0或NULL，优先选用nullptr
  - 避免在整型和指针类型之间重载



###### 条款9：优先选用别名声明，而非typedef

- ```cpp
  typedef unique_ptr<unordered_map<string, string>> UPtrMapSS;//cpp98的写法
  
  using UPtrMapSS = unique_ptr<unordered_map<string, string>>;//cpp11的写法
  ```

- 优点1：更加的方便

- ```cpp
  //cpp11的写法，可以认为这是个非依赖性的类型
  template<typename T>
  using MyAllocList = list<T, MyAlloc<T>>;
  
  MyAllocList<Widget> lw;
  
  //cpp98的写法，这个更加复杂了的
  template<typename T>
  struct MyAllocList{
      typedef list<T, MyAlloc<T>> type;
  };
  
  //关于cpp98的写法更加复杂的一个原因,编译器需要考虑下面的这种情况
  template<>
  classMyAllocList<Wine>{
      enum class WineType{
          White, Red, Rose
      };
      WineType type;
  };
  
  MyAllocList<Widget>::type lw;
  ```

- 要点速记

  - typedef不支持模板化，但别名声明支持
  - 别名模板可以让人免写“::type”后缀，并且在模板内，对于内嵌typedef的引用经常要求加上typename前缀



###### 条款15：只要有可能使用constexpr，就使用它

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
- 要点速记
  - constexpr对象都具备const属性，并由编译期已知的值完成初始化
  - constexpr函数在调用时若传入的实参值时编译期已知的，则会产出编译期结果
  - 比起非constexpr对象或constexpr函数而言，constexpr对象或是constexpr函数可以用在一个作用域更广的语境中