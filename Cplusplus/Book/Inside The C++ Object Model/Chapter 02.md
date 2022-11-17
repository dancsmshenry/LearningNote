# 第二章 构造函数语意学

## 2.1 Default Constructor 的构造操作

- 分清楚是编译器的需要还是程序的需要
- 带有 default constructor 的 member class object 
  -  如果A类包含B类，但是没有显式的写出A类的默认构造函数，那么编译器就会自动为你提供一个隐式的构造函数，这个构造函数会根据情况调用B类的构造函数
  -  但是这个隐式的构造函数，不会对类中的数据（int，double 等数据）进行初始化的（这是程序员的需要，不是编译器的需要）
  -  如果 class A 内含一个或一个以上的 member class objects，那么 class A 的每一个 constructor 必须调用每一个 member classes 的 default constructor
     - 即如果一个类的成员包含多个类，那么这个类的每一个构造函数都会调用其包含的类的构造函数
     - 调用的顺序和声明的顺序一样
     - 即编辑器会为我们的代码进行扩张
- 带有 default constructor 的 base class 
  - 如果一个没有任何 constructors 的 class 派生自一个“带有 default constructor ”的 base class，那么这个 derived class 的 default constructor 会被视为 nontrivial，并因此需要被合成出来，它将调用上一层 base classes 的 default constructors





## 2.3 程序转化语意学

- 显式的初始化

  - 源代码是这样的:

  - ```cpp
    void foo_bar(){
        A a1(a0);//a0可能是一个全局变量
        A a2 = a0;
        A a3 = A(a0);
    }
    ```

  - 但是经过编译器的扩充，可能会变成这样：

  - ```cpp
    void foo_bar(){
        A a1;//定义被重写，初始化操作被剥除
        A a2;
        A a3;
        
        a2.A::A(a0);//调用拷贝构造函数
        a3.A::A(a0);
        a4.A::A(a0);
    }
    ```

  - 总结：普通的显式初始化操作，是要先调用默认构造函数创建对象，然后再调用拷贝构造函数把值赋给对象

- 参数的初始化

  - 把一个class object当作参数传给一个函数（或作为一个函数的返回值），相当于以下操作：

  - ```cpp
    void foo(X x0);
    
    //编译器的拓展操作
    X _temp0;//生成临时对象
    
    _temp0.X::X(x0);
    
    void foo(X& x0);//因为传入的是临时对象，所以原函数也要被修改
    
    foo(_temp0);//传入临时对象
    ```

  - 而另一种实现方式是拷贝建构，把实际参数直接建构在应该的位置上，此位置视函数活动范围的不同，记录于程序堆栈中

  - 总结：参数的初始化是先根据值拷贝出一个临时对象，然后改造原函数，把临时对象传入

- 返回值的初始化

  - 把一个局部对象值作为函数值返回，相当于以下操作：

  - ```cpp
    X bar(){
        X xx;
        //具体的操作
        return xx;
    }
    
    //会被改造成这样
    void bar(X& _result){
        X xx;
        xx.X::X();//编译器的默认构造函数
        //一些具体的操作
        
        _result.X::X(xx);//拷贝构造函数
        
        return ;
    }
    ```

  - 即先创建一个要返回的对象_result，这个对象就是赋值用的对象，然后对原函数进行改写，把 _result传入函数中，进行上述的操作

  - 总结：返回值的初始化也是先建立一个临时对象，改造原函数，然后再在函数里面建立一个新的对象，对新的对象进行处理过后，赋值拷贝给临时对象

- 在使用者层面做优化

  - 源代码：

  - ```cpp
    X bar(const T &y, const T &z){
        X xx;
        
        return xx;//这里的观点认为，编译器还为你临时建立了一个新的变量，十分浪费
    }
    ```

  - 改造为：

  - ```cpp
    X bar(const T &y, const T&z){
        return X(y, z);//认为这样更好？？？
    }
    ```

  - 我觉得还不如原来的写法呢

- 在编译器层面做优化

  - 上述编译器的优化都叫做NRV（named return value）
  - 一般来说，面对“一个class object作为另一个class object的初值”的情形，语言允许编译器有大量的自由发挥空间，其利益当然是导致机器码产生时有明显的效率提升，缺点则是你不能够安全规划你的copyconstruct的副作用，必须视其执行而定

- Copy Constructor:要还是不要？

  - 如果一个类里面没有member成员，就没必要自己手写一个拷贝构造函数
  - 如果想要哟个memset()实现对象的拷贝，注意虚函数的情况，可能会改变其内部的vptr



## 2.4 成员们的初始化队伍

- 为了使程序顺利编译，以下四种情况必须使用member initialization list：

  - 当初始化一个reference member时
  - 当初始化一个const member时
  - 当调用一个base class的构造函数时，而且它有一组参数
  - 当调用一个member class的构造函数时，而且它有一组参数

- 例如：

  - ```cpp
    class Word{
        String _name;
        int _cnt;
        
      public:
        	Word(){
                _name = 0;
                _cnt = 0;
            }
    };//如果构造函数没有初始化列表，那么Word（）实质是这样的
    
    Word::Word(){
        _name.String::String();//创建一个String对象
        String temp = String(0);//产生一个临时对象
        _name.String::operator=(temp);//memberwise的拷贝
        temp.String::~String();//摧毁临时对象
        
        _cnt = 0;
        
        //这样做的成本就是消耗很高
    }
    
    //而用列表优化后变为
    Word:Word(){
        _name.String::String(0);
        _cnt = 0;
    }
    ```

  - 而这种情况在template中经常发生

    - ```cpp
      template<class type>
      foo<type>::foo(type t){
          _t = t;//如果是一般类型那就没事，但是如果是class类型，就最好用列表初始化
      }
      ```

- 列表初始化的具体操作：执行列表初始化，以适当顺序在constructor之内安插初始化操作，并在任何explicit user code之前

- 注意：list中的项目顺序是由class中的members声明顺序决定的，不是由列表中的排序决定的