# 构造函数

- inline（内联）函数

  - 较为复杂的函数即使把它声明为了inline，编译器也不会视为inline（inline只是建议）
  - 函数若在class body内部定义完成，便会变为inline

- access level（访问级别）

  - public，private，protected

- constructor（ctor，构造函数）

  - ```cpp
    class complex{
      public:
        complex(double r = 0, double i = 0):re(r), im(i){}
        //默认实参，初始值列表
        //初始值列表是一种大气的写法，能够避免很多的问题，能够同时定义初始化赋值
        
      private：
          double im, re;
    };
    ```

  - 创建对象的时候自己调用

  - 函数没有返回值，名称要和类名相同

  - 构造函数可以有很多个，也可以被重载（原理是编译器部会对函数的名字重写一遍）