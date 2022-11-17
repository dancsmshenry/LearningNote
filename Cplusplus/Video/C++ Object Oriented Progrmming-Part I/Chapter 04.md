# 参数传递与返回值

- ctors放在private区（参考单例模式）

- const member functions（常量成员函数）

  - 背景：如果对象是一个const对象，表示该对象的数据不能被修改，但是你的函数名因为没有加上const而修改了数据内容，就发生错误了（即设计不好）

  - 在函数的最后面加上const，表明该函数的内容不能改变对象的数据内容

  - 如果类被定义为const，那么它只能调用const的常量函数

  - ```cpp
    class complex{
      public:
        double real() const {return re;}
        double imag() const {return im;}
       
      private:
        double re, im;
    };
    ```

- 参数传递：pass by value and pass by reference(to const)

  - 传引用更快一点，传的是指针（就4个字节）
  - 不过也要看具体对象的大小来定
  - 防止因为传入指针而修改了原来的变量，所以可以在传入引用对象的时候在前面加上const，表明该变量只读，不可修改

- 返回值传递：return by value and return by reference(to const)

  - 什么时候不用引用传递：返回的是局部变量的时候

- friend（友元）

  - 在类里面声明定义该函数为类的友元函数（或在类外定义），友元函数可以访问类的私有成员

  - friend打破了类的封装性

  - 相同class的各个objects互为friends

    - ```cpp
      class complex{
        public:
          complex(double r = 0, double i = 0):re(r) im(i){
              
          }
          
          int func(const complex& param){
              return param.re + param.im;
          }
          
        private:
          double re, im;
      };
      ```

- 好的编程习惯

  - 数据放在private
  - 用引用来传递参数，看情况加const
  - 以引用的方式返回参数
  - 在类本体的函数，应该加上const的就要加上
  - 构造函数要用初始值列表