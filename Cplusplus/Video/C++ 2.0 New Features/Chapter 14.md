# lambdas

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

