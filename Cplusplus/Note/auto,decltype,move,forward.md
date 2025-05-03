# backround

## left value

- 左值：可以取地址并且有名字的，位于等号左边，非临时的
  - 是在内存的表达式，能够用内置的&进行取地址
- 左值引用：能指向左值，但不能指向右值的，即对象一定要是一个变量（左值引用还是一个左值）

- 左值引用可以理解为cpp的语法糖，更加方便的使用指针

  - const左值引用可以指向右值（涉及到const的底层实现，它新建了一个值给左值引用）

  - ```cpp
    int a = 10;
    const int& i = a; // 从const的实现上来看，是新建了一个位置用于存放a的值
    
    void test(const int& a) {}
    // 而这里就没有新建值，只是表明用什么方式来接收这个值
    ```
  
- 应用

  - 函数名和变量名
  - 返回左值引用的函数调用
  - 前置自增自减表达式++i、--i
  - 由赋值表达式或赋值运算符连接的表达式(a=b, a += b等)
  - 解引用表达式*p
  - **字符串字面值"abcd"**（经测试，确实是）

- ```cpp
  void reference_in_test(int& a) {
      a = 10;
  }
  // 这里的a必须传入的是一个左值，而且不能传入具有const性质的变量，否则的话绑定的性质会丢失
  
  void reference_in_test(const int& a) {
      // a = 10;
  }
  // 这里的a的传入既可以是一个左值，也可以是一个右值，是不是const更是无所谓
  ```







## right value

- 右值：不能取地址的没有名字的，临时的，位于等号右边的（没有地址，立即生成的值是放在了寄存器中）
  - 更多的是一种值的表达

- 右值引用的对象是常量（感觉是对引用的一种补偿，使其更加像一个指针）

- 右值引用既可以是左值，也可以是右值

  - 如果有名称就是左值，否则就是右值
  - 或者说作为函数返回值的 && 是右值，直接声明出来的 && 是左值

- 右值引用可以指向右值，不可以指向左值（需要依靠move）

- 右值引用指向右值，本质上也是把右值提升为一个左值，并定义一个右值引用通过std::move指向该左值

  - ```cpp
    int &&ref_a = 5;
    ref_a = 6; 
    //等同于以下代码：
    int temp = 5;
    int &&ref_a = std::move(temp);
    ref_a = 6;
    ```


- 应用：

  - 非字符串的字面量以及枚举项，如：`nullptr`,`true`
  - 内置的后++与后--，如：`a--`
  - 内置的算术，逻辑，比较表达式，如：`a+b`，`a&b`，`a||b`, `a<b`
  - 内置取地址表达式，this指针，如:`&a`
  - lamda表达式,如：`[](int a){ return 2*a; }`
  - 转型为非引用的表达式，如：`static_cast<double>(fValue)`, `(float)42`
  - 转型为右值引用的表达式，如：`static_cast<double&&>(fValue)`，`std::move(x)`;

- 左值转右值引用

  - ```cpp
    //可以将左值转为右值，再进行右引用
    TestClassA kTA2(1000);
    // 使用std::move转为右值引用
    TestClassA&& c3 = std::move(kTA2);
    // 使用static_cast转为右值引用
    TestClassA&& c4 = static_cast<TestClassA&&>(kTA2);
    // 使用C风格强转为右值引用
    TestClassA&& c5 = (TestClassA&&)kTA2;
    // 使用std::forwad<T&&>为右值引用
    TestClassA&& c6 = std::forward<TestClassA&&>(kTA2);
    ```



### 纯右值

- 运算表达式产生的临时变量、不和对象关联的原始字面量、非引用返回的临时变量、lambda表达式等都是纯右值
- 一般有：
  - 除字符串字面值外的字面值
  - 返回非引用类型的函数调用
  - 后置自增自减表达式i++、i--
  - 算术表达式(a+b, a*b, a&&b, a==b等)
  - 取地址表达式等(&a)



### 将亡值

- 通常指将要被移动的对象、T&&函数的返回值、std::move函数的返回值、转换为T&&类型转换函数的返回值
- 将亡值可以理解为即将要销毁的值，通过“盗取”其它变量内存空间方式获取的值，在确保其它变量不再被使用或者即将被销毁时，可以避免内存空间的释放和分配，延长变量值的生命周期，常用来完成移动构造或者移动赋值的特殊任务
- 我的理解：将要被销毁的值（说是将要，是因为后面有人一定要把它接收）





# move

单纯的move只是一个强制类型转换罢了，所以无事发生

数据和所有权的移动是在某个参数为右值引用的函数中完成的（最常见的就是类似于a=move(b)会匹配到移动构造函数上）

move仅仅是类型擦除，实际上发生移动是move通过强制类型转换，触发了类对象的 operator = (T&& a)函数或Object(Object&& o)，才会有数据和所有权的转移

从语义上来说，对一个左值使用move，就意味着你不再需要这个变量上的值了，即你要将它的值移走（这也导致了很多人会误认为就是move将值移走的）

总结：**std::move的变更所有权其实是通过移动构造函数或者移动赋值函数实现的**

```c++
// clang中的实现
/**
  *  @brief  Convert a value to an rvalue.
  *  @param  __t  A thing of arbitrary type.
  *  @return The parameter cast to an rvalue-reference to allow moving it.
*/
template<typename _Tp>
_GLIBCXX_NODISCARD
constexpr typename std::remove_reference<_Tp>::type&& move(_Tp&& __t) noexcept {
    return static_cast<typename std::remove_reference<_Tp>::type&&>(__t);
}

// STRUCT TEMPLATE remove_reference
template <class _Ty>
struct remove_reference {
    using type                 = _Ty;
    using _Const_thru_ref_type = const _Ty;
};

template <class _Ty>
struct remove_reference<_Ty&> {
    using type                 = _Ty;
    using _Const_thru_ref_type = const _Ty&;
};

template <class _Ty>
struct remove_reference<_Ty&&> {
    using type                 = _Ty;
    using _Const_thru_ref_type = const _Ty&&;
};
```

举例：
- `bb` 的类型是 `Foo&`，`move` 之后变为 `Foo&&`，会调用移动赋值函数
- `cc` 的类型是 `const Foo`，`move` 之后变为 `const Foo&&`，会调用拷贝赋值函数
- `bb` 的类型是 `const Foo&`，`move` 之后变为 `const Foo&&`，会调用拷贝赋值函数



- 只能说在某个特定的实现中，移动后的对象会变为空，但是cpp标准没有规定被移动后的对象为空，所以使用标准库的程序不应当依赖有这些行为的代码

- 比如说int的move，原来的对象还是没有改变值；而string经过move之后就会变为nullptr
  - 例外：unique_ptr经过move之后变为nullptr




- move是不会改变原来的const属性的（参考static_cast是不会修改其属性的）



- 如果只是move变量而没有左值接收它的话，那么该变量是不会变化的（换言之，move之所以能够改变数据，是因为它有移动构造函数..）

  - ```cpp
    string s1 = "sdf";
    move(s1);
    //s1的值还是sdf
    //仅仅进行的是类型擦除的动作，
    ```





# forward

- std::forward<T>(u)有两个参数：T与 u

  - 当T为左值引用类型时，u将被转换为T类型的左值
  - 否则u将被转换为T类型右值

- 总结

  - 如果T是左值引用（int&），那么就会把值转换为左值
  - 如果T是右值引用（int&&），那么就会把值转换为右值

- ```cpp
  /// remove_reference
  template<typename _Tp>
  struct remove_reference
  { typedef _Tp   type; };
  
  template<typename _Tp>
  struct remove_reference<_Tp&>
  { typedef _Tp   type; };
  
  template<typename _Tp>
  struct remove_reference < _Tp&& >
  { typedef _Tp   type; };
  
  // forward源码
  // 处理左值作为左引用或者右引用
  template<typename _Tp>
  constexpr _Tp&&
  forward(typename std::remove_reference<_Tp>::type& __t) noexcept
  { return static_cast<_Tp&&>(__t); }
  
  // 处理右值作为右引用
  template<typename _Tp>
  constexpr _Tp&&
  forward(typename std::remove_reference<_Tp>::type&& __t) noexcept
  {
      static_assert(!std::is_lvalue_reference<_Tp>::value, "template argument"
          " substituting _Tp is an lvalue reference type");
      return static_cast<_Tp&&>(__t);
  }    
  ```

- 有一个疑惑：为什么用的时候只要把T放进去就行了呢？

  - 猜测：用户传入的信息推测后的类型会存入T中，但是我们用的都是解析后的T（即param），所以导致我们用的时候都是左值，无法感受它到底是左还是右，所以就得用forward

- 一个应用：完美转发（如下）





# auto

- 编译的时候推导的



规则

- 对于单独的指针或引用
  - 凡是以引用或指针来接收参数的，都直接忽略原来是否是引用
  - 而像const和指针的，原封不动的匹配进去




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
  
  ////////////////////////函数表达式
  for(auto x : range) // 从原容器中拷贝一份数据
  
  for(auto& x : range) // 原容器中数据的引用
  
  for(auto&& x : range)
  
  for(const auto& x: range) // 只能对原容器中的数据进行读操作
      
  auto&& result = foo(); // auto&& 意味着后边要转发
  ```
  
- 关于auto的用法总结
  - `auto` ：拷贝
  - `auto&` ：左值引用，只能接左值（和常量右值）
  - `auto&&` ：万能引用，能接左值和右值
  - `const auto&` ：const 万能引用，能接左值和右值
  - `const auto&&` ：常量右值引用，只能接右值
- 具体的场景
  - `auto`：用于你想修改右值的情形
  - `auto&`：用于你想修改左值的情形
  - `auto&&`：用于泛型编程中的转发
  - `const auto&`：用于只读
  - `const auto&&`：**基本没用**，基本可被 `const auto&` 替代（比 `const auto&` 多一个语义：一定得是右值。然而这没什么用，因为你都不对其进行修改，是左还是右没什么影响）







# decltype









# 引用折叠

- 只存在于模板推导，以及完美转发中

- 所有的引用折叠，最后都代表一个引用，要么是左值引用，要么是右值引用

- 规则：如果任一引用为左值引用，则结果为左值引用。否则（即两个都是右值引用），结果为右值引用

- 即在万能引用中int& &&就代表int&

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







# 万能引用

- 是利用语法实现的一个功能，既能接收左值，也能接收右值

- 万能引用只有在模板函数里，参数是左值还是右值无法确定的时候，才是不可替代的

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
  
- auto&&以及模板函数里面的T&&都是万能引用







# 应用

## 移动语义

- 背景：对于一个类，我们想要根据传入值得不同，实现不同得构造函数，从而实现拷贝构造和移动构造

- 通过右值，可以实现浅拷贝
- 通过万能引用，对push_back进行优化





## 完美转发

- 一个具体的应用场景：需要一个函数既能够接收左值，又能够接收右值，同时又要根据左值和右值转发给不同的函数版本，但发现如果直接用万能引用+左右值函数重载，导致的问题就是拿到的params都是左值，根本用不到右值

- 解决办法：使用万能引用+forward，即利用T的信息实现转发

- ```cpp
  #include <iostream>
  using namespace std;
  
  // 万能引用，转发接收到的参数 param
  template<typename T>
  void PrintType(T&& param)
  {
  	f(param);  // 将参数param转发给函数 void f()
      // 修改后的版本
      f(std::forward<T>(param)); // 用了这个修改后的版本，就可以正确区分了
  }
  
  // 接收左值的函数 f()
  template<typename T>
  void f(T &)
  {
  	cout << "f(T &)" << endl;
  }
  
  // 接收右值的函数f()
  template<typename T>
  void f(T &&)
  {
  	cout << "f(T &&)" << endl;
  }
  
  int main(int argc, char *argv[])
  {
  	int a = 0;
  	PrintType(a);//传入左值
  	PrintType(int(0));//传入右值，结果是最后用到的还是左值的版本
  }
  ```

- 我们可以看到，不管T是值类型，还是左值引用，还是右值引用，T&经过引用折叠，都将是左值引用类型

- 也就是forward 以左值引用的形式接收参数 param, 然后通过将param进行强制类型转换 static_cast<T&&>()，最终再以一个 T&&返回





# 参考

- https://zhuanlan.zhihu.com/p/50816420
- https://zhuanlan.zhihu.com/p/335994370
- https://zhuanlan.zhihu.com/p/137662465
- https://zhuanlan.zhihu.com/p/402251966
- https://mp.weixin.qq.com/s/_9-0iNUw6KHTF3a-vSMCmg
- https://zhuanlan.zhihu.com/p/99524127
- https://www.jianshu.com/p/4538483a1d8a
