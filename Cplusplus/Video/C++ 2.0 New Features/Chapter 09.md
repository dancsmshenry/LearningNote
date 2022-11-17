# =default,=delete

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
