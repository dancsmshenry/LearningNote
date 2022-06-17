# 背景

### left value

- 左值：可以取地址并且有名字的，位于等号左边，非临时的
  - 对于左值的定义，很难说有一个真正确定的定义，你比如说int i = 1; int b = i;这其中，你能说i是右值吗
  - 目前一个比较满意的定义：是在内存的表达式，能够用内置的&进行取地址
- 左值引用：能指向左值，但不能指向右值的，即对象一定要是一个变量（本身还是左值）

- 左值引用可以理解为cpp的语法糖，更加方便的使用指针

- 注意：const左值引用可以指向右值（涉及到const的底层实现）

  - ```cpp
    int a = 10;
    const int& i = a; // 这里，从const的实现上来看，是又新建了一个位置用于存放a的值
    
    void test(const int& a) {
        // 而这里就没有新建值，因为这里只是表明用什么方式来接收这个值
    }
    ```

- 一般有：

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
  // 这里的a既可以是一个左值，也可以是一个右值，是不是const更是无所谓
  ```







### right value

- 右值：不能取地址的没有名字的，临时的，位于等号右边的（没有地址，立即生成的值是放在了寄存器中）
  - 更多的是一种值的表达

- 右值引用的对象是常量（感觉是对引用的一种补偿，使其更加像一个指针）

- 右值引用既可以是左值，也可以是右值

  - 如果有名称就是左值，否则就是右值
  - 或者说作为函数返回值的 && 是右值，直接声明出来的 && 是左值

- 右值引用可以指向右值，不可以指向左值（需要依靠move）

- 右值引用能指向右值，本质上也是把右值提升为一个左值，并定义一个右值引用通过std::move指向该左值

  - ```cpp
    int &&ref_a = 5;
    ref_a = 6; 
    //等同于以下代码：
    int temp = 5;
    int &&ref_a = std::move(temp);
    ref_a = 6;
    ```


- 举例：

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





#### 纯右值

- 运算表达式产生的临时变量、不和对象关联的原始字面量、非引用返回的临时变量、lambda表达式等都是纯右值
- 一般有：
  - 除字符串字面值外的字面值
  - 返回非引用类型的函数调用
  - 后置自增自减表达式i++、i--
  - 算术表达式(a+b, a*b, a&&b, a==b等)
  - 取地址表达式等(&a)



#### 将亡值

- 通常指将要被移动的对象、T&&函数的返回值、std::move函数的返回值、转换为T&&类型转换函数的返回值
- 将亡值可以理解为即将要销毁的值，通过“盗取”其它变量内存空间方式获取的值，在确保其它变量不再被使用或者即将被销毁时，可以避免内存空间的释放和分配，延长变量值的生命周期，常用来完成移动构造或者移动赋值的特殊任务





# move

- 单纯的move只是一个强制类型转换罢了，所以无事发生
- 数据和所有权的移动是在某个参数为右值引用的函数中完成的（最常见的就是类似于a=move(b)会匹配到移动构造函数上）

  - move仅仅是类型擦除
  - 实际上发生移动是move通过强制类型转换，触发了类对象的 operator = (T&& a)函数或Object(Object&& o)，才会有数据和所有权的转移
- 总结：**std::move的变更所有权其实是通过移动构造函数或者移动赋值函数实现的**

- ```cpp
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
  ```

- 举例
  - `bb` 的类型是 `Foo&`，`move` 之后变为 `Foo&&`，会调用移动赋值函数；
  - `cc` 的类型是 `const Foo`，`move` 之后变为 `const Foo&&`，会调用拷贝赋值函数；
  - `bb` 的类型是 `const Foo&`，`move` 之后变为 `const Foo&&`，会调用拷贝赋值函数。



- 只能说在某个特定的实现中，移动后的对象会变为空，但是cpp标准没有规定被移动后的对象为空，所以使用标准库的程序不应当依赖有这些行为的代码

- 比如说int的move，原来的对象还是没有改变值；而string经过move之后就会变为nullptr
- 修正：unique_ptr经过move之后变为nullptr



- move是不会改变原来的const属性的



- 如果只是move变量而没有左值接收它的话，那么该变量是不会变化的

  - ```cpp
    string s1 = "sdf";
    move(s1);
    //s1的值还是sdf
    //仅仅进行的是类型擦除的动作，
    ```





# forward

- auto&&以及模板函数里面的T&&都是万能引用
- 万能引用只有在模板函数里，参数是左值还是右值无法确定的时候，才是不可替代的

- move本身没啥意义，它的意义在于将左值转换成右值，如果转换后的值在一个构造或者赋值的context内，就会调用对应的移动构造或者赋值的函数
- 可以用引申一下为什么stl扩容的时候没有用到移动构造

- auto&&可以绑定左值或者右值，并且保留const属性（写代码的人偷懒）

```cpp
for(auto x : range) // 创建拷贝，无法修改range中的元素

for(auto& x : range) // 可以修改range中的元素

for(auto&& x : range)

for(const auto& x: range) // 只读range中的元素
```

- std::forward<T>(u)有两个参数：T与 u。 a. 当T为左值引用类型时，u将被转换为T类型的左值； b. 否则u将被转换为T类型右值
- 即如果T是左值引用（int&），那么就会把值转换为左值；如果是右值引用（int&&），那么就会把值转换为右值





# auto

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

- 







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

- ```cpp
  template<typename T>
  ReturnType Function(T&& parem) {
      // function main
  }
  ```

- 传入左值，变为左值引用（参考引用折叠）



背景：左值，右值，左值引用，右值引用

名词：auto，decltype，模板推导，move，forward（这几个名词与上述背景的碰撞）

引用折叠 ->(基于引用折叠产生了)万能引用（引用折叠+模板推导，注意一定是模板）

一个具体的应用场景：需要一个函数既能够接收左值，又能够接收右值，同时又要根据左值和右值转发给不同的函数版本

由此引发了完美转发



这里的一套组合拳：左值，右值，模板和auto和decltype推导左右引用值，既然讲到了引用，先聊一下函数传参，就说一下move和forward，接着就是完美转发引用折叠万能引用





# 应用

### 移动语义

- 通过右值，可以实现浅拷贝
- 通过万能引用，对push_back进行优化
- 背景：对于一个类，我们想要根据传入值得不同，实现不同得构造函数，从而实现拷贝构造和移动构造





### 完美转发

- 一个具体的应用场景：需要一个函数既能够接收左值，又能够接收右值，同时又要根据左值和右值转发给不同的函数版本

- 由此引发了完美转发

- 我们发现在万能引用中，一个元素的原本是左值还是右值的信息其实是保存在了T中的

  - 如果传入实参是个右值(包括右值引用)，那模板类型 T 就被推导为实参的类型（没有引用属性）
  - 如果传入实参是个左值，T被推导为左值引用

- 因此可以利用T里面的信息对数据转发，实现上面的效果

- forward的源码（简易版）

  - ```cpp
    template<typename T>
    T&& forward(T& param) {
    	return static_cast<T&&>(param);
    }
    ```

- 我们可以看到，不管T是值类型，还是左值引用，还是右值引用，T&经过引用折叠，都将是左值引用类型。也就是forward 以左值引用的形式接收参数 param, 然后 通过将param进行强制类型转换 static_cast<T&&>()，最终再以一个 T&&返回





# 参考

- https://zhuanlan.zhihu.com/p/50816420
- https://zhuanlan.zhihu.com/p/335994370
- https://zhuanlan.zhihu.com/p/137662465
- https://zhuanlan.zhihu.com/p/402251966
- https://mp.weixin.qq.com/s/_9-0iNUw6KHTF3a-vSMCmg