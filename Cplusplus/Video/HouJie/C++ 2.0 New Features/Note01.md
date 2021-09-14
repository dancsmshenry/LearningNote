第一节

- 测试cpp所支持的版本

  - ```cpp
    #include <iostream>
    
    using namespace std;
    
    int main(){
        cout << __cplusplus << endl;//201402，查看当前编辑器是否支持cpp14的版本
    }
    ```



第二节

- variadic template（可变参数模板）

  - ```cpp
    #include <iostream>
    #include <bitset>
    
    using namespace std;
    
    void print(){//如果是递归的话，最后一定要写一个这个函数，因为print递归到最后args是没有东西的
    }
    
    template<typename T, typename... Types>//表示传进来的是一个T，再加上一个包（pack），即把后面的一连串变量变为一个pack，传入函数中
    void print(const T& firstArg, const Types&... args){
        cout << firstArg << endl;
        cout << "size:" << sizeof...(args) << endl;//用来求解args的个数（注意这种特殊的写法）
        print(args...);
    }
    
    int main(){
        print(7.5, "hello", bitset<16>(377), 42);
    }
    ```

  - 用于继承，递归等代码，感觉会使得代码变得难懂

  - 也是分特化和泛化的，哪个更加符合就选哪个

  - tuple是一个可以放任意数量，类型的一个类型



第三节

- automatic type deduction with auto

  - auto可以用来自动类型推导，即有些比较难写的类型，可以用这个类型的一个变量来表示，从而推导得出该类型并给一个变量

    - ```cpp
      auto i = 43;//i has type int
      double f();
      auto d = f();//d has type float
      
      auto l = [](int x) -> bool{
          //auto也可以用于lambda式
      }
      ```

- nullptr and std::nullptr_t

  - 在cpp11里面，用nullptr来表示空指针

- spaces in template expression

  - 在cpp11里面，可以这样写

    - ```cpp
      vector<list<int> >;//ok,in each cpp version
      vector<list<int>>;//ok since cpp11
      //避免了编译器把其认为>>的情况
      ```



第四节

- uniform initialization（一致性的初始化，设初值）

  - 在cpp11以前，对象类型的初始化可以用大括号，中括号，以及重载的标识符来进行初始化

  - 而在cpp11以后，都可以用中括号来初始化

  - 会涉及iniitializer_list<T>的问题

    - 即编译器看到{t1,t2...tn}便做出initializer_list<T>，它关联到一个array<T,n>。调用 函数（例如ctor构造函数）时该array内的元素可被编辑器分解逐一传给函数

    - 但若函数参数是一个initializer_list<T>，调用者就不能给数个T参数然后以为它们会被自动转为一个initializer_list<T>传入

    - 例：

      - ```cpp
        complex<double> c{1.0, 4.0};
        ```

      - 这里形成一个initializer_list<double>，背后有个array<double, 2>。调用complex< double >的构造函数的时候，该array内的2个元素被分解传给构造函数



第五节

- initializer_list（初始化列表）上
  - 用初始化列表初始化变量，会为变量设定初值
  - 不能做很强硬的类型转换（比如整型和浮点的转换，），可以做char和int类型的转换
    - 但是在一些编译器上，是会提示警告，不会报错



第六节

- initializer_list（初始化列表）下

  - ```cpp
    class P{
      P(int a, int b){
          //
      }
      
      P(initializer_list<int> initlist){
          //
      }
    };
    
    P p(11, 5);//调用的是第一个构造函数
    P p{11, 5};//调用的是第二个函数（如果没有了第二个函数，会自动调用第一个函数）
    P p{11, 22, 33};//调用的是第二个函数
    P s={11, 5};//调用的也是第二个函数（如果没有了第二个函数，会自动调用第一个函数）
    ```

  - initializer_list的底层实现包含一个指向array的一个指针和其长度

    - 所以如果copy一个相同的initializer_list，那么，这两个list其中的指针都是指向同一个内存地址的（浅拷贝）

  - 被广泛的用于stl中（用list，接受任意个数的对象作为初值）

