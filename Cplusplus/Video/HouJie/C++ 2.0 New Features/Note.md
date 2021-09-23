##### 第一节

- 测试cpp所支持的版本

  - ```cpp
    #include <iostream>
    
    using namespace std;
    
    int main(){
        cout << __cplusplus << endl;//201402，查看当前编辑器是否支持cpp14的版本
    }
    ```



##### 第二节

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



##### 第三节

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



##### 第四节

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



##### 第五节

- initializer_list（初始化列表）上
  - 用初始化列表初始化变量，会为变量设定初值
  - 不能做很强硬的类型转换（比如整型和浮点的转换，），可以做char和int类型的转换
    - 但是在一些编译器上，是会提示警告，不会报错



##### 第六节

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



##### 第九节

- 如果你自行定义了一个构造函数，编译器不会再给你一个默认构造函数

- 如果你强制加上=default，就可以重新获得并使用default 构造函数

- ```cpp
  class Foo{
      private:
      	int _i;
      
      public:
      	Foo(i):_i(i){}
      	Foo() = default;//表示使用编译器默认提供的版本（因为有了参数构造函数，编译器是不会提供那个默认构造的函数的）
      	
      	~Foo() = default;
      	void func1() = default;//一般的函数没有默认版本，所以不能用
      	void func2() = delete;//禁止使用编译器默认生成的函数，可以用于任何函数
      	//也可以禁止使用某函数
  };
  ```

- 一般，构造函数（默认构造函数，默认拷贝构造函数，移动构造函数，移动拷贝函数），运算符（拷贝运算符），析构函数，会使用=default

- 而=delete可以用于任何函数身上

- 一个类只要含有指针类对象，就一定要自己写big three（析构函数，复制构造函数，operator=）

- 在cpp11中有big five，析构函数，拷贝构造函数，移动构造函数，拷贝赋值操作，移动赋值操作

- 浅拷贝，深拷贝





###### 第十一节

- template template parameter

- ```cpp
  template<typename T, template<class> class Container>//传进来一个模板Container，模板的模板的类型是T
  class XCLs{
    private:
      Container<T> c;
    public:
      XCIs(){
          for (long i = 0; i < size; ++ i){
              c.insert(c.end(), T());
          }
          output_static_data(T());
          Container<T> c1(c);
          Container<T> c2(std::move(c));
          c1.swap(c2);
      }
  };
  ```

- 





###### 第十二节

- noexcept

  - 写在函数后面，表示保证该函数不会爆出异常

  - ```cpp
    void foo() noexcept(true);//保证foo函数不会爆出异常
    
    void swap(int &x, int &y)noexcept(noexcept(swap(x, y))){
        swap(x, y);
    }
    ```

- override

  - 用在函数的后面，表示该函数父类的一个重载

  - ```cpp
    class Base{
      public:
        void foo(int a);
    };
    
    class Derive:public Base{
        public:
        	void foo(int a) override;
    }
    ```

- final

  - 不让当前的类被继承

  - ```cpp
    struct Base1 final{};
    struct Derived:Base1{};//不能继承base1类
    ```

  - 
