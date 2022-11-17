# Type Alias,noexcept,override,final

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

