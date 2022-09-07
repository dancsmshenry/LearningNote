# 条款1：理解模板类型推导

- ```cpp
  template<typename T>
  void f(ParamType param);
  f(expr);
  ```



### 情况一：ParamType是个指针或引用，但不是个万能引用

- 若expr具有引用类型，就先将引用部分忽略（类型推导的过程中会把引用部分给忽略掉）

- 而后，对expr的类型和ParamType的类型执行模式匹配，来决定T的类型

- ```cpp
  template<typename T>
  void f(T& param);
  
  int x = 27;
  f(x);//T的类型是int，param是int
  
  const int cx = x;
  f(cx);//T的类型是const int，param是const int&
  
  const int& rx = x;
  f(rx);//T的类型也是const int，param是const int&
  
  
  template<typename T>
  void f(const T& param);
  
  f(x); // T是int，param是const int&
  f(cx);// T是int，param是const int&
  f(rx);// T是int，param是const int&
  
  
  template<typename T>
  void f(T* param);
  int 
  const int *px = 28;
  f(&x); // T是int，param是int*
  f(px); // T是const int，param是const int*
  ```
  
- 总结：

  - 凡是以引用或指针来接收参数的，都直接忽略原来是否是引用
  - 而像const和指针的，原封不动的匹配进去





### 情况二：ParamType是个万能引用

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





### 情况三：ParamType既非指针也非引用（即值传递）

- 直接忽略其引用部分，const部分和volatile对象

- 传进来的都当做是值传递，无论原来是不是const，都回归原来的类型

- 例外：如果是const修饰的引用或指针，const会因此保留(const仅会在按值形参处被忽略）

- ```cpp
  template<typename T>
  void f(T param);
  
  const char* const ptr = "hello world!";
  
  f(ptr);//传递的类型是const char* const
  ```





### 数组实参

- 对于一个函数，如果直接传入数组，传入后会退化为指针（即如果直接操作传进来的数组，那就是操作数组本身了）

- ```cpp
  void temp(int[] arrayy);
  //退化为
  void temp(int* arrayy);
  ```

- 但是可以声明引用

- ```cpp
  template<typename T>
  void f(T& param);//这就是真正的数组，不过传入的也还是数组的引用（不过引用和指针，懂得都懂）
  
  template<typename T>
  void f(T* param); // 这里数组退化为指针，就会导致传入数组的指针
  ```





### 函数实参

- 同数组实参一样，直接传的话也是传入函数指针；传引用的话就是传函数引用

- ```cpp
  void someFunc(int, double);
  
  template<typename T>
  void f1(T param); // 值传递
  
  template<typename T>
  void f2(T& param); // 引用传递
  
  f1(someFunc); // 推导为函数指针
  
  f2(someFunc); // 推导为函数引用
  ```





### 要点速记

- 在模板型别推导过程中，具有引用型别的实参会被当作非引用型别来处理。换言之，其引用性会被忽略
- 对万能引用形参进行推导时，左值实参会进行特殊处理
- 对按值传递的形参进行推导时，若实参型别中带有const或volatile饰词，则它们还是会被当作不带const或volatile饰词的型别来处理
- 在模板型别推导过程中，数组或函数型别的实参会退化成对应的指针，除非它们被用来初始化引用











# 条款2：理解auto型别推导

- auto的类型推导和templat的推导（条款1的情况）大概都是一样的





- ```cpp
  auto x = 27;//第三种情况，推导为int
  
  const auto cx = x;//第三种情况，推导为const int
  
  const auto& rx = x;//第一种情况，推导为const int&
  
  auto&& uref1 = x;//第二种情况，传入的左值都变为左值引用，即int&
  
  auto&& uref2 = cx;//第二种情况，左值，const int&
  
  auto&& uref3 = 27;//第二种情况，右值，就直接推导，即int&&
  
  const char name[] = ":::"; // const char[]
  
  auto arr1 = name;//const char*
  
  auto& arr2 = name;//const char(&)[]
  
  auto func1 = someFunc; // void(*)(int, double)
  
  auto& func2 = someFunc; // void(&)(int, double)
  ```

  



有关{}的例外

- ```cpp
  auto x1 = 27;//int
  auto x2(27);//int
  auto x3 = {27};//initializer_list<int>
  auto x4{27};//initializer_list<int>
  
  auto x5 = {1, 2, 3.0};//error，auto不会强转数据类型，所以无法推导
  
  template<typename T>
  void f(T parm);
  f({1, 2, 3.0});//模板不可以推导出initializer_list<int>
  
  // 只能这样写
  template<typename T>
  void f(std::initializer_list<T> initList);
  f({11,23,9}); // 其中T推导为int
  ```

- 对于大括号初始化表达式的处理方式，是auto型别推导和模板型别推导的唯一不同之处

- 即auto可以通过`{}`来推导出`initializar_list`，而template需要专门来写





在cpp14的变化

- 在cpp14中，可以用auto来说明函数返回值从而推导出来（不过这种auto是在使用模板型别推导而非auto推导）

- ```cpp
  // 所以这种写法是错误的，不能推导出initializer_list类型
  // 即带有auto返回值的函数，若要返回一个大括号括起来的初始化表达式，是无法同故宫编译的
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





### 要点速记

- 在一般情况下，auto型别推导和模板型别推导是一模一样的，但是auto型别推导会假定用大括号括起的初始化表达式代表一个std::initializer+list，但模板推导型别不会如此
- 在函数返回值或lambda式的形参中使用auto，意思是使用模板推导而非auto推导









# 条款3：理解decltype

- 在cpp11中，decltype的主要用途大概就在于声明那些返回值型别依赖于形参型别的函数模板
  - 即decltype可以推导出括号里面的对象的类型，并用于其他的对象





- 返回值类型尾序语法（cpp11允许对表达式的lambda式的返回值类型实施推导）

- 在函数参数列表后面使用一个->符号指出函数的返回类型，好处是可以在函数返回类型中使用函数参数相关的信息

  - ```cpp
    template<typename Container, typename Index>
    auto authAndAccess(Container& c, Index i)->decltype(c[i]){
        return c[i];
    }
    // 如果我们按照传统语法把函数返回类型放在函数名称之前， c和i就未被声明所以不能使⽤
    ```





参考一个背景

- ```cpp
  template<typename Container, typename Index>
  auto test(Container& c, Index i){
      return c[i];
  }
  ```

- 这里看起来是直接返回一个数组的具体的数字，但是这里的auto推导其实是还是模板推导（参考条款2），所以返回的其实是一个右值，即不能像左值一样操作，即在模板的推导中，初始化表达的引用性会被忽略

- ```cpp
  // 间接导致下列代码发生错误
  std::deque<int> d;
  test(d, 4) = 9; // 报错，因为不能把右值赋给一个右值
  ```

- 使用`decltype(auto)`来解决，可以保留被推导原来的性质

- ```cpp
  template<typename Container, typename Index>
  decltype(auto) test(Container& c, Index i){
      return c[i];
  } // 完美保留了引用的性质
  
  Widget w;
  const Widget& cw = 2;
  auto myWidget1 = cw; // auto推导为Widget
  decltype(auto) myWidget2 = cw; // 推导为const Widget&
  ```





参考另一个背景

- 对于左值和右值的传递，比如说我想写一个函数，无论传入的是左值还是右值，返回的都得是容器的指定位置

- ```cpp
  template<typename Container, typename Index>
  decltype(auto) authAndAccess(Container&& c, Index i) {
      return std::forward<Container>(c)[i];
  }
  ```





一个坑点

- ```cpp
  decltype(auto) f1() {
      int x = 0;
      return x; // return int
  }
  
  decltype(auto) f2() {
      int x = 0;
      return (x); // return int&
  }
  ```





### 要点速记

- 绝大多数情况下，decltype会得出变量或表达式的型别而不作任何修改
- 对于类型为T的左值表达式，除非该表达式仅有一个名字，decltype总是得出类型T&
- cpp14支持decltype(auto)，和auto一样，它会从其初始化表达式出发来推导类型，但是它的类型推导使用的是decltype的规则









# 条款4：掌握查看型别推导结果的方法

- 研究的三个阶段：撰写代码阶段，编译阶段，运行时阶段



- 第一种方法：IDE编译器的报错提示
- 在IDE中的代码编辑器通常可以显⽰程序代码中变量，函数，参数的类型，你只需要简单的把⿏标移到它 们的上⾯



- 第二种方法：编译器诊断信息
- 看报错



- 第三种方法：运行时输出（利用`typeid`对类型进行推导输出）

- ```cpp
  std::cout<<typeid(x).name()<<"\n"; //显⽰x和y的类型
  std::cout<<typeid(y).name()<<"\n";
  ```





### 要点速记

- 利用IDE编译器，编译器错误消息和Boost TypeIndex库常常能够查看到推导而得的类型
- 有些工具产生的结果可能会无用，或者不准确，所以，理解cpp型别推导规则是有必要的