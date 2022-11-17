#### Chapter01、演进、环境与资源

- 测试cpp所支持的版本

  - ```cpp
    #include <iostream>
    
    using namespace std;
    
    int main(){
        cout << __cplusplus << endl;//201402，查看当前编辑器是否支持cpp14的版本
    }
    ```
  
- 新式c header file不带.h名称，而变为`#include<cstdio>`

  - 引入标准库的文件也不需要带.h了，而变为`#include<vector>`

-  在早期版本std::tr1里面的代码现在也被放到了std namespace里面了

- 推荐几个比较好的网站和书籍

  - cplusplue.com
  - gcc.gnu.org
  - zh.cppreference.con



#### Chapter02、Variadic templates

- variadic template（可变参数模板）

  - 用于继承，递归等代码，感觉会使得代码变得难懂

  - 样例

    - ```cpp
      #include <iostream>
      #include <bitset>
      
      using namespace std;
      
      void print(){//因为该函数类似一个递归函数，所以一定要写一个这个函数，因为print递归到最后args是没有东西的
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

  - 也是分特化和泛化的，哪个更加符合就选哪个（埋坑）

    - ```cpp
      #include <iostream>
      #include <bitset>
      
      using namespace std;
      
      void print(){//因为该函数类似一个递归函数，所以一定要写一个这个函数，因为print递归到最后args是没有东西的
      }
      
      template<typename T, typename... Types>//表示传进来的是一个T，再加上一个包（pack），即把后面的一连串变量变为一个pack，传入函数中
      void print(const T& firstArg, const Types&... args){
          cout << firstArg << endl;
          cout << "size:" << sizeof...(args) << endl;//用来求解args的个数（注意这种特殊的写法）
          print(args...);
      }
      
      template<typename... Types>
      void print(const Types&... args){
          //这个和上面是可以共存的，分为特化和泛化，今后会继续讲的
          //传入相同的数据，好像还是调用上面那个函数
      }
      
      int main(){
          print(7.5, "hello", bitset<16>(377), 42);
      }
      ```

  - 出现在不同的地方：

    - 用于template parameters，就是模板参数包
    - 用于function parameter types，就是函数参数类型包
    - 用于function parameters，就是函数参数包

  - 用处：可以理解为一种关于函数参数的递归

    - ```cpp
      template<typename... Values> class tuple;
      template<> class tuple<> {};
      
      template<typename Head, typename... Tail>
      class tuple<Head, Tail...>:private tuple<Tail...>{
          typedef tuple<Tail...> inherited;
          public:
          	tuple(){}
          	tuple(Head v, Tail... vtail):m_head(v), inherited(vtail...){}
          typename Head::type head(){return m_head;}
          inherited& tail(){return *this;}
          protected:
          	Head m_head;
      };
      ```

    - 记录一下上面这种做法，可以认为是tuple一个接一个的继承（并且每个tuple都用一个m_head来存储最前面的一个数据，用inherited来存储上一级的tuple）

    - tips：如果出现这种用参数递归的情况，一定要准备一个空的类来最后继承，即终止点

    - tuple是一个可以放任意数量，类型的一个类型



#### Chapter03、Spaces in Template Expression、nullptr and str::nullptr_t、Automatic Type Deduction with auto

- spaces in template expressions

  - ```cpp
    vector<list<int> >;//ok in each cpp version
    vector<list<int>>;//ok, since cpp11
    //避免了编译器把其认为>>的情况
    ```
  
  - 在过去的cpp版本中，如果两个>>连在一起，编译器会认为那是操作符
  
- nullptr and std::nullptr_t

  - 在cpp11里面，用nullptr来表示空指针

  - 在cpp11以前，把一个指针设为空指针，设为NULL或0都是可以的

  - ```cpp
    void f(int);
    void f(void*);
    f(0);//calls f(int);
    f(NULL);//calls f(int)/f(void*),ambiguous otherwise
    f(nullptr);//calls f(void*);
    ```

  - nullptr的类型是nullptr_t

- automatic type deduction with auto

  - auto可以用来自动类型推导，即有些比较难写的类型，可以用这个类型的一个变量来表示，从而推导得出该类型并给一个变量

    - ```cpp
      auto i = 43;//i has type int
      double f();
      auto d = f();//d has type float
      
      auto l = [](int x) -> bool{
          //auto也可以用于lambda式
      }
      
      //以前
      list<string> c;
      list<string>::iterator ite;
      
      //现在
      list<string> c;
      auto ite = find(c.begin(), c.end(), target);
      ```



#### Chapter04、Unifrom Initialization

- uniform initialization（一致性的初始化，设初值）

  - 在cpp11以前，对象类型的初始化可以用大括号，中括号，以及重载的标识符来进行初始化

  - 而在cpp11以后，都可以用大括号来初始化

    - ```cpp
      int values[] {1,2,3};
      vector<int> v{1,2,3,4,5,6,7};
      vector<string> cities{"","",""};
      complex<double> c{4.0,3.0};
      ```
  
  - 深究其本质：
  
    - 即编译器看到{t1,t2...tn}便做出`initializer_list<T>`，它关联到一个array<T,n>。调用 函数（例如ctor构造函数）时该array内的元素可被编辑器分解逐一传给函数
  
    - 但若函数参数是一个initializer_list<T>，调用者就不能给数个T参数然后以为它们会被自动转为一个initializer_list<T>传入
  
    - 例：
  
      - ```cpp
        vector<int> v{1,2,3,4,5,6,7};
        ```
        
      - 这里会形成一个initializer_list<int>，背后有个array<string>，调用vector<int>ctors时编译器找到了一个vector<int>ctor接收initializer_list<int>（即前面已经形成了一包东西，后面又找到一个函数来接收这一包东西，那就一包传给一包）
      
      - ```cpp
        complex<double> c{1.0, 4.0};
        ```
      
      - 这里形成一个initializer_list<double>，背后有个array<double, 2>。调用complex< double >的构造函数的时候，该array内的2个元素被分解传给构造函数（这里是前面把变量变成了一包东西，但是complex不接受一包东西的传递，只能逐个逐个的传递）



#### Chapter05、Initializer_list I

- 用初始化列表初始化变量，会为变量设定初值

  - ```cpp
    int i;//i has undefined value
    int j{};//j is initialized by 0;
    int* p;//p has undefined value;
    int* q{};//q is initialized by nullptr
    ```

- 不能做很强硬的类型转换（比如整型和浮点的转换，），可以做char和int类型的转换
  - 但是在一些编译器上，是会提示警告，不会报错



#### Chapter06、Initializer_list II

- ```cpp
  void print(std::initializer_list<int> vals){
      for (auto p = vals.begin(); p != vals.end(); ++ p){
          cout << *p << endl;
      }
  }//和之前的variadic templates相比，前者可以接收任意数量任意类型的，而这个只能接收任意数量指定类型的
  
  print({1,2,3,4,5,6});
  
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
  //但是如果是complex之类的话，就会调用到int a，int b的那个函数
  ```
  
- initializer_list的底层实现

  - 包含一个指向array的一个指针和其长度
  - 所以如果copy一个相同的initializer_list，那么，这两个list其中的指针都是指向同一个内存地址的（浅拷贝）

- 被广泛的用于stl中（用list，接受任意个数的对象作为初值）

- 也可以用于比较大小的max和min上，使其可以比较多个对象的大小

  - ```cpp
    int maxn(initializer_list<int> __l){
        int result = INT_MIN;
        for (auto p = __l.begin(); p != __l.end(); p ++ ){
            result = max(*p, result);
        }
        return result;
    }
    
    int main(){
        cout << maxn({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}) << endl;
    }
    ```



#### Chapter07、Explicit for ctors taking more than one argument

- 对于含有一个或多个参数（有默认值的）的构造函数，不希望在程序中隐式的调用，就加上explicit

- ```cpp
  class Complex{
    public:
      explicit Complex(int re, int im = 0):real(re), imag(im){}
      
      Complex operator+(const Complex& x){
          return Complex((real + x.real), (imag) + x.imag);
      }
  };
  
  Complex c1(12, 5);
  Complex c2 = c1 + 5;//error,因为这里不能隐式的把5转换为complex
  ```

- 大概率只会用在类的构造函数上

- ```cpp
  class P{
      public:
      P(int a, int b){
        //  
      }
      
      P(initializer_list<int>){
          //
      }
      
      explicit P(int a, int b, int c){
          //
      }
  };
  
  P p5 = {1,2,32};//error,不能隐式的调用P(int a, int b, int c)函数
  ```



#### Chapter08、Range - based for statement

- ```cpp
  for (decl : coll){
      statement;
  }
  
  vector<doublie> vec;
  for (auto elem: vec){
      cout << elem << endl;//这个只是拷贝
  }
  
  for (auto& elem: vec){
      elem *= 3;//这个是实体
  }
  ```

- 关联式容器（hash set等）不能通过迭代器来修改元素，序列式是可以的

- ```cpp
  class C{
      public:
      	explict C(const string& s);
  };
  
  vector<string> vs;
  for (const C& elem:vs){
      cout << elem << endl;//这里会出错：因为explicit不允许将string隐式转换为C
  }
  ```



#### Chapter09、=default,=delete

- =default
  - 如果你自行定义了一个构造函数，编译器不会再给你一个默认构造函数

  - 如果你强制加上=default，就可以重新获得并使用default 构造函数

  - 一般，构造函数（默认构造函数，默认拷贝构造函数，移动构造函数，移动拷贝函数），运算符（拷贝运算符），析构函数，会使用=default

  - 如果只是单独的一个类，那么默认的构造函数是没有价值的，但如果有多个类继承下来的话，默认构造函数就会调用父类的构造函数，同时每个构造函数都要这么做，都要调用这个默认构造函数（因为这是它的功能嘛），那么这个函数就有价值了

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

- =delete

  - 而=delete可以用于任何函数身上
  - 表示禁止使用该函数

- 在cpp11中有big five，析构函数，拷贝构造函数，移动构造函数，拷贝赋值操作，移动赋值操作

- 总结：

  - 对于=default，用于big-five以外的函数是没有意义的
  - =delete，可以用于任何函数上面

- 一个空类

  - ```cpp
    class Empty{};//你以为的版本
    
    class Empty{
        public:
        Empty(){}//如果有父类的继承的话，还会调用父类的构造函数
        Empty(const Rmpty& rhs){}
        ~Empty(){}//同上，还会调用父类的析构函数
        
        Empty& operator=(const Empty& rhs){}
    }//编译器为你拓宽的版本，而且这些函数都是public inline的
    ```

- 一个类只要含有指针类对象，就一定要自己写big three（析构函数，复制构造函数，operator=）

- 如果不希望一个类被copy或是被delete的话，就可以写一个NoCopy或NoDtor函数，然后让其他类去继承它，PrivateCopy也是同理



#### Chapter10、Alias Template

- ```cpp
  template <typename T>
  using Vec = std::vector<T, MyAlloc<T>>;
  
  //模板化名不能用define来实现
  #define Vec<T> template<typename T> std::vector<T, MyAlloc<T>>;
  //否则就会变为这样
  Vec<int> coll;
  
  template<typename int> std::vector<int, MyAlloc<int>>;//这就变为了定义一个模板了，但却不是我们想要的那一个
  ```

- 不能对化名做全特化或偏特化

- 用模板化名实现萃取（把变量中的类型给提取出来）

  - ```cpp
    template<typename Container>
    void test_moveable(Container c){
        typedef typename iterator_traits<typename Container::iterator>::value_type Valtype;
        //先是获取容器的迭代器，再通过迭代器获取具体的值，最后通过萃取机（iterator_traits）获取该数值的类型，最后赋值给Valtype
        //这种方法可以把容器里面的对象的类型给拿出来
    }
    ```



#### Chapter11、Template template parameter

- ```cpp
  template<typename T, template<class T> class Container>//传进来一个模板Container，模板的模板的类型是T
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

- 像vector等容器都有两到三个参数的位置（写模板的时候需要注意的）

  - ```cpp
    template<typename _Tp, typename _Alloc = std::allocator<_Tq>>
    class vector:protected _Vector_base<_p, _Alloc>//这里是有两个参数的，不过另一个一般都是默认值
    ```

  - 所以用template template parameter和alias template来解决之前的那个问题（又想获得容器元素的类型，又想获得容器的类型）

    - ```cpp
      template<typename T, template<class T> class Container>
      class A{};
      
      template<typename T>
      using Vec = vector<T, allocator<T>>;
      A<string, Vec> c1;//就用这个来实现
      ```



#### Chapter12、Type Alias,noexcept,override,final

- type alias

  - ```cpp
    //typedef void(*func)(int, int)
    using func = void(*)(int, int);//func为一个函数指针，指向的函数返回值是void，参数是两个int
    
    template<typename T>
    struct Container{
        using value_type = T;//typedef T value_type;
    }
    ```

  - 感觉上能够更加方便的表示想要表示的那个对象

  - 和typedef是等价的

  - 总结using的应用：using namespace std，using std::cout，using _Base:: _ M _allocate（表示要使用某个类某个命名空间的某个函数，但是又不想用太多的前缀修饰）

- noexcept

  - 写在函数后面，表示保证该函数不会爆出异常

  - ```cpp
    void foo() noexcept(true);//保证foo函数不会爆出异常，一般来说默认是true，可以直接写noexcept()
    
    void swap(int &x, int &y)noexcept(noexcept(swap(x, y))){
        swap(x, y);
    }
    ```
    
  - 还有一点：如果是vector扩张时要调用得到的函数，就要把这个函数声明为noexcept（只有vector会成长）

  - 总结：如果你的函数有movefunction的话，就不要让它抛出异常

- override

  - 用在函数的后面，表示该函数父类的一个重载

  - ```cpp
    class Base{
      public:
        void foo(int a);
    };
    
    class Derive:public Base{
        public:
        	void foo(int a) override;//告诉编译器该函数是父类foo函数的重载，既然是重载，那么参数列表和返回值都要匹配（有助于检查错误）
    }
    ```

- final

  - 不让当前的类被继承

  - ```cpp
    struct Base1 final{};
    struct Derived1:Base1{};//不能继承base1类
    
    struct Base2{
      virtual void f() final;//该函数不能被重写
    };
    
    struct Derived2:Base2{};
    ```
    



#### Chapter13、decltype

- ```cpp
  map<string, float> coll;
  map<string, float>::value_type elem;//cpp11之前的写法
  decltype(coll)::value_type elem;//cpp11之后的写法，decltype可以自动推导出类型
  //defines a type equivalent to the type of an expression
  ```

- 作用一：

  - ```cpp
    //used to declare return types
    template<typename T1, typename T2>
    decltype(x + y) add(T1 x, T2 y);
    auto add(T1 x, T2 y);//等价于这个
    ```

- 作用二：

  - ```cpp
    //in metaprogramming
    template<typename T>
    void test(T obj){
        typedef typename decltype(obj)::iterator iType;
        //等价于typedef typename T::itreator iType;
        //模板只是半成品，编译通过不代表使用的时候也会通过
    }
    
    test(complex<int>());//编译失败，因为复数是没有迭代器的
    ```

- 作用三：

  - ```cpp
    //used to pass the type of a lambda
    auto cmp = [](const Person& p1, const Person& p2){
        return p1.lastname() < p2.lastname();
    }
    
    std::set<Person,decltype(cmp)> coll(cmp);
    ```



#### Chapter14、lambdas

- lambda的介绍
  - ```cpp
    auto I = []{
        cout << "Hello World!" << endl;
    }
    
    I();
    
    //完整形式
    [...](...) mutable throwSpec -> retType{};
    //()里面写参数（一般函数的参数）
    //[]里面写的是可以取用的外部的变量（所以对于外部的值，会出现值传递和引用传递的情况）
    //mutable表示是否可变
    //retType表示lambdas的返回类型
    //throwSpec表示是否可以丢出异常
    //上述三个参数都是可有可无的，但是如果写了其中一个，就要加上小括号
    ```

- 有关值传递和引用传递

  - ```cpp
    int id = 0;
    auto f = [id]() mutable{
        //mutable表示该传进来的变量[]里面的变量是可变的
        //如果没有加上mutable，以值传递进来的变量是无法更改的（但是以引用传递的加不加mutable都可以改变，可以理解为：引用传递的本质是指针，无论如何引用的指针都是不会变化的吗？）
        cout << "id:" << id << endl;
        ++ id;
    };
    
    id = 42;
    f();//id:0
    f();//id:1
    f();//id:2
    cout << id << endl;//42
    /**
    理解：
    就和上面创建一个类一样，是把属性以值传递给了这个类，所以后续调用这个函数相当于是不断调用类的函数（重点是值传递）
    要想变为43 44 45的话，就改为引用传递
    **/
    ```

- 一种奇怪的写法

  - ```cpp
    auto qqq = [=, &y]{};//等号的位置表示可以以值传递传入任何对象
    ```

- 有关lambda的坑

  - ```cpp
    auto cmp[...](...){...};
    
    std::set<Person, decltype(cmp)> coll(cmp);//这里必须要在coll后面加上cmp
    ```

- 能够简化代码

  - ```cpp
    vector<int> vi = {};
    int x = 30;
    int y = 100;
    vi.erase(remove_if(vi.begin(), vi.end(), [x, y](int n){return x < n && n < y;}), vi.end());
    
    //下面是以前的写法
    class LambdaFunctor{
      public:
        LambdaFunctor(int a, int b):m_a(a), m_b(b){}
        bool operator()(int n)const{
            return m_a < n && n < m_b;
        }
      private:
        int m_a;
        int m_b;
    };
    
    vi.erase(remove_if(vi.begin(), vi.end(), LambdaFunctor(x, y)), vi.end());
    ```

- 深度解析lambda

  - ```cpp
    int tobefound = 5;
    auto lambda1 = [tobefound](int val){return val == tobefound};
    
    //等价于下面的代码
    class UnNamedLocalFunction{
      int localVar;
      public:
        UnNamedLocalFunction(int var):localVar(var){}
        bool operator()(int val){
            return val == localVar;
        }
    };
    UnNameLocalFunction lambda2(tobefound);
    
    //可以把lambda理解为一个匿名的函数对象
    bool b1 = lambda1(5);
    bool b2 = lambda1(5);
    ```



#### Chapter15、Variadic templates I

- 变化的是：

  - 参数个数（利用参数个数逐一逐减的特性，实现递归函数调用，使用function template完成）
  - 参数类型（利用参数个数逐一逐减导致参数类型也逐一逐减的特性，以class template完成）

- 代码一

  - ```cpp
    void printX{}
    
    template<typename T, typename... Types>
    void printX(const T& firstArg, const Types&... args){
        cout << firstAeg << endl;
        printX(args);
    }
    
    template<typename... Types>
    void printX(const Types&... args){
        ...
    }
    
    /**
    对于模板函数的重载，是谁更特化就用谁，这里的话，认为是第一个版本更加的特化（可能是第一个版本有第一个参数吗？）
    **/
    ```



#### Chapter16、Variadic templates II

- 代码二

  - ```cpp
    template<typename T, typename... Args>
    void printf(const char* s, T value, Args... args){
        while (*s){//一直循环
            if (*s == '%' && *(++s) != '%'){
                cout << value;//如果是符号，并且后面一项不是符号，就把后面的值，即value给输出
                printf(++s, args...);
                return ;
            }
            cout << *s ++ ;//不是符号的话就直接输出
        }
        throw logic_erroe("extra argtements provided to printf");
    }
    
    void printf(const char* s){
        while (*s){
            if (*s == '%' && *(++s) != '%'){
                throw logic_erroe("extra argtements provided to printf");
            }
            cout << *s ++ ;
        }
    }
    ```



#### Chapter17、Variadic templates III

- 比较同一种数据的大小，可以用initializer_list来实现
- 代码三
  - 使用initializer_list来实现代码过多，下次用图片来代替



#### Chapter18、Variadic templates IV

- 若参数type相同，比较的是同一种数据，则无需改动

- 代码四

  - ```cpp
    int maximum(int n){return n;}
    
    template<typename... Args>
    int maximum(int n, Args... args){
        return std::max(n, maximum(args...));
    }
    ```

- 在标准库中，max已经可以接收任意数量的参数值了，不过要这样写

  - ```cpp
    #include<algorithm>
    cout << max({1,2,3,4,5,6,7,8,9,10}) << endl;
    ```



#### Chapter19、Variadic templates V

- 代码五

  - ```cpp
    template<typename... Args>//重载操作符，如果是对tuple进行操作，就用这个
    ostream& operator<<(ostream& os, const tuple<Args...> &t){
        os << "[";
        PRINT_TUPLE<0, sizeof...(Args), Args...>::print(os, t);
        return os << "]"; 
    }
    
    template<int IDX, int MAX, typename... Args>//IDX表示当前输出到了第几个，MAX表示tuple的长度
    struct PRINT_TUPLE{
        static void print(ostream& os, const tuple<Args...> &t){
            os << get<IDX>(t) << (IDX + 1 == MAX ? "" : ",");//输出第几个字符，get应该是tuple的专用函数
            PRINT_TUPLE<IDX + 1, MAX, Args...>::print(os, t);
        }
    }
    
    template<int MAX, typename... Args>
    struct PRINT_TUPLE<MAX, MAX, Args...>{//如果当前操作的是最后一个，即全部都输出完了，就return
        static void print(ostream& os, const tuple<Args...> &t){
            return;
        }
    }
    
    //使用过程
    cout << make_tuple(7.5,546,64116,16,"lsdjkf") << endl;
    //结果是：[7.5,546,64116,16,lsdjkf]
    ```



#### Chapter20、Variadic templates VI

- 代码六（递归+继承）

  - ```cpp
    //递归的继承
    template<typename Head, typename... Tail>
    class tuple<Head, Tail...>:private tuple<Tail...>{
        typedef tuple<Tail...> inherited;
        protected:
        	Head m_head;
        public:
        	tuple(){}
        	tuple(Head v, Tail... vtail):m_head(v),inherited(vtail...){}
        //前缀是表示Head的类型是什么
        //意义是取出第一个元素
        	typename Head::type head(){return m_head;}//这里是无法编译过的，是求出Head类型的时候出现了问题，用auto可以解决
        	auto head() -> decltype(m_head){return m_head}
        	Head head() {return m_head;}
        //意义是取出除去第一个元素后的tuple，用到的一个技巧就是，this指针子类指针指向父类对象
        	inherited& tail(){return *this;}
    };
    
    template<typename... Values> class tuple;
    template<> class tuple<> {};
    ```



#### Chapter21、Variadic templates VII & Cpp keywords

- 代码七（递归+复合）

  - ```cpp
    template<typename... Values> class tup;
    template<> class tup<> {};
    
    template<typename Head, typename... Tail>
    class tup<Head, Tail...>{
        typedef tup<Tail...> composited;
        protected:
        	composited m_tail;
        	Head m_head;
        public:
        	tup(){}
        	tup(Head v, Tail... vtail):m_tail(vtail...), m_head(v){}
        	Head head(){return m_head;}
        	composited& tail(){return m_tail;}
    };
    ```
    



#### Chapter22、标准库源代码分布

- 查看c++2.0的源代码



#### Chapter23、Rvalue references and Move Semantics

- Rvalue references（右值引用）
  - 目的：用来解决非必要的拷贝（临时对象的insert，push_back）
  - 当赋值的右手边是右值，那么左边的接收端可以去偷右边的值而不用去执行copy，分配空间等操作
  - 左值一般是变量，可以出现在operator=左侧者
  - 右值出现在operator=右侧者，一般是临时匿名对象或数值常量
    - （准确来说是不能放到左边的？但是左值又都可以作为右值啊）
    - 解释：左值是可以出现在左边的，右值是只能出现在右边的，所以不能以是在=的左右来判断是否为左右值
    - 但是有一点，右值是不可以出现在左边的
  - 当右值出现于operator=(copy assignment)的右侧，我们认为对其资源进行偷取/搬运（move）而非拷贝是可以的，是合理的
    - 必须有语法让我们在调用端告诉编译器，这个是rvalue
    - 必须有语法让我们在被调用端写出一个专门处理Rvalue的所谓move assignment函数
  - 一个理解：右值的意思是说，对于传进来的对象，此前我们是以这个临时对象作为模板，copy一个新的对象出来，而有了右值引用，我们就直接让指针指向这个临时对象吗？
  - `std::move`的作用：把一个变量（左值）放进去，得到的就是一个右值



#### Chapter24、Perfect Forwarding

- unperfect forwarding

  - ```cpp
    void process(int& i){
        cout << "int& i = " << i << endl;
    }
    
    void process(int&& i){
        cout << "int&& i = " << i << endl;
    }
    
    ina a = 0;
    
    process(a);//a被当作左值处理
    process(1);//1被当作右值处理
    process(move(a));//move使得变为右值，当作右值处理
    
    void forward(int&& i){
        cout << "forward(int&&)" << endl;
        process(i);
    }
    
    forward(2);//以右值的方式传入forward，但是最后却是以左值的方式传入process,原因：传递过程中它变成了一个named object
    forward(move(a));//理由同上，最后都是以左值的方式传入process
    forward(a);//error，左值根本调用不起来
    ```

  - 起初的目标：想要设计一个类型，它的值是可以被偷的，从而大幅提高容器的效率



#### Chapter25、写一个Move-aware class

- ```cpp
  class MyString{
    static size_t DCtor;
    static size_t CTor;
    static size_t CCtor;
    static size_t MCtor;
    static size_t MAsgn;
    static size_t Dtor;
    private:
      char* _data;
      size_t _len;
      void _init_data(const char *s){
          _data = new char[_len + 1];
          memcpy(_data, s, _len);
          _data[_len] = '\0';
      }
    public:
      //default constructor
      MyString():_data(NULL), _len(0){++DCtor;}
      
      //constructor
      MyString(const char* p):_len(strlen(p)){
          ++CTor;
          _init_data(p);
      }
      
      //copy constructor
      MyString(const MyString& str): _len(str._len){
          ++CTor;
          _init_data(str._data);
      }
      
      //move constructor
      MyString(MyString&& str) noexcept:_data(str._data), len(str._len){
          ++MCtor;
          str.len = 0;//新的指针指向了传进来的对象后，原来的那个对象的指针的len属性就要设为0，_data就要指向空（如果没指向空，就会造成多个指针指向同一个对象，而如果这里直接是删除了这个指针，那么在后面的析构函数的位置，就会变为delete一个不存在的东西，就会报错；同时，因为传进来的大多是临时对象，在作用域结束后会消失的，如果指针没有指向null，那么就会使得本对象一起和他消失）
          str._data = NULL;//重要
      }
      
      //copy assignment
      MyString& operator=(const MyString& str){
          ++CAsgn;
          if (this != &str){
              if (_data) delete _data;
              _len = str._len;
              _inity_data(str._data);
          }else{}
          
          return *this;
      }
      
      //move assignment
      MyString& operator=(MyString&& str) noexcept{
          ++MAsgn;
          if (this 1= &str){
              if (_data) delete _data;//如果原来有指向的，先把它删除
              _len = str._len;
              _data = str._data;
              str.len = 0;
              str._data = NULL;
          }
          return *this;
      }
      
      //dtor
      virtual ~MyString(){
          ++Dtor;
          if (_data){//需要先判断是不是null，如果不是才delete
              delete _data;
          }
      }
  };
  ```



#### Chater26、Move-aware class对容器的效能测试

- 只要是以结点形式存在的，move construct和copy construct都是一样的
- 针对vector，deque，list等容器进行了move construct测试，发现性能有显著的提升



#### Chapter27、容器-结构与分类_ 旧与新的比较 _ 关于实现手法

- 注意：把一个对象当作了右值，进行了move construct，就不能用这个资源了
- sequence containers
  - array(cpp11)
  - vector
  - deque
  - list(双向链表)
  - forward-list(cpp11，单向链表)
- assoviative containers
  - set/multiset
  - map/multimap
- unordered containers(cpp11)
  - unordered set/multiset
  - unordered map/multimap



#### Chapter28、容器 array

- 相当于一个包装好的数组

- gcc2.9版本
  - 没有ctor，也没有dtor

- cpp2.0后的array

  - ```cpp
    int a[1000];
    int[1000] b;//error
    typedef int T[100];
    T b;//yes
    ```



#### Chapter29、容器hashtable

- hashtable的底层实现（我理解的）：是有一个指针数组，每个位置都装有一个指针，每个指针接着一串链表，链表可以是双向的，也可以是单向的
- 每算出一个hashcode，就把数据接到这个链表下面



#### Chapter30、Hash function

- g4.9

  - ```cpp
    //hash是一个仿函数对象，（1，2，3）的前面是构造出一个临时对象，（1，2，3）则是调用它重载的()函数
    cout << hash<int>()(1,2,3) << endl;//返回的是一个hash code
    ```

- 查看底层是如何实现hash code的（在g2.9？）

  - int等整数类型直接返回整数类型
  - char用特殊的hash算法实现



#### Chapter31、tuple

- ```cpp
  tuple<string, int, int, complex<double>> t;
  cout << "sizeof = " << sizeof(t) << endl;//32,为什么不是（4+4+4+16）呢？
  
  cout << get<0>(t) << get<1>(t) << endl;//get是获取tuple中的第n个元素
  
  auto t2 = make_tuple(22,49,"77");//make_tuple制造出一个tuple
  
  get<1>(t1) = get<1>(t2);//get其中的元素并赋值
  
  t1 < t2;//把tuple中的每个元素都拿出来进行比较，最后返回结果
  
  tuple<int, float, string> t3(77, 1.1, "more light");
  int i1;
  float f1;
  string s1;
  tie(i1, f1, s1) = t3;//把i1,f1,s1三个值放到t3里面
  
  typedef tuple<int, float, string> TupleType;
  cout << tuple_size<TupleType>::value << endl;//输出tuple的元素个数
  tuple_element<1, TupleType>::type f1 = 1.0;//拿出tuple的第一个值的类型来定义参数
  ```

- 在cpp11之前，实现tuple这种数据类型都是逐个逐个去定义的
