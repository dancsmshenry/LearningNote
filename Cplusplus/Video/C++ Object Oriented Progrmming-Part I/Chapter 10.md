# 关键字与模板的补充

- 关键词static

  - 加上static的成员存在于类之外的区域中，无论对象有多少个，该数据都只有一个

  - 静态函数也是类似，单独存在于外边

  - 所以静态函数无法调用类的属性以及函数（因为它不属于类对象的，它是单独存在于某个区域），只能调用静态变量和静态函数

  - 而静态变量需要在类外进行定义初始化

    - ```cpp
      class A{
        public:
          static double m_rate;
      };
      
      double A::m_rate = 8.0;
      ```

  - 调用static函数的两种方式：通过object调用（类似作用域），通过class name调用（类似普通函数）

  - 单例模式就是通过static来实现的(singleton)

    - ```cpp
      class A{
        public:
          static A& getInstance(){
              return a;
          }
          setup(){}
          
        private:
          A();
          A(const A& rhs);
      };
      
      A& A::getInstance(){
          static A a;
          return a;
      }
      ```

- 关键词cout

  - 底层使用了很多重载使得其能用于浮点数，整数，字符串上面

- class template

  - ```cpp
    template <typename T>
    class complex{
        public:
        	complex(T r = 0, T i = 0):re(r), im(i){}
        private:
        	T re, im;
    };
    
    complex<double> c1(1.1, 1.2);
    ```

  - 相当于用T来代替class中所有的代码

- function template

  - ```cpp
    template<typename T>
    inline const T& min(const T& a, const T& b){
        return b < a ? b : a;
    }
    
    int a = 10, b = 1, c = 100;
    c = min(a, b);//编译器会对函数模板进行引数推导
    ```

  - 所以对于每个类，只需要重载小于号即可，这样就可以统一调用min函数

- 关键字namespace

  - 把代码都放到这样一个命名空间里面，进行封装，有助于防止变量同名
  - 标准库的所有代码都放在std里面
  - 可以分段写（即namespace是共享的，这样可以防止代码过长）
  - 使用namespace： using namespace std;