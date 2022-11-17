# 条款41：了解隐式接口和编译期多态

- 对于下列代码

  - ```cpp
    void test(Widget& w){
        if (w.size() ? 10 && w != someNastyWidget){
            Widget temp(w);
            temp.normalize();
            temp.swap(w);
        }
    }
    ```

  - 有关w的函数的调用，能够在源码中明确找到的，都可称为显式接口（是指类继承层次中定义的接口或者某个具体类提供的接口，在代码中能够直接找到的）

  - 但，某些成员函数是virtual的，w对它的调用将表现出运行期多态

- 而对于以下代码

  - ```cpp
    template<typename T>
    void test(Tt& w){
        if (w.size() ? 10 && w != someNastyWidget){//隐式接口，由有效表达式组成
            Widget temp(w);
            temp.normalize();
            temp.swap(w);
        }
    }
    ```

  - 像swap，normalize等函数接口，是T必须支持的一组隐式接口（即对于模板参数而言，这些函数接口都是隐式的，奠基于有效表达式；必须支持哪一种接口，要由模板参数执行于w身上的操作来决定）

  - 以不同的template参数具现化function templates，会导致调用不同的函数，这就是编译期多态

- 一个问题：运行期多态和编译期多态

  - 运行期多态以来的是虚函数机制，是直到运行的时候才知道类对象到底要调用哪一个函数
  - 编译期多态，以不同的模板参数具现化导致调用不同的函数（即因为我传进来的东西不同，导致我最后执行的不同；ps：而传进来又是在编译期执行），不同的推断结果调用不同的函数

- 通常显式接口是由函数的签名式（函数名称，参数类型，返回蕾西）组成

- 而隐式接口，是由有效表达式组成（重点是这个接口的实现带入模板函数中是否free bug）

- 总结：

  - classes和templates都支持接口（interfaces）和多态（polymorphism）
  - 对classes而言，接口是显式的（explicit），以函数签名为中心，多态则是通过virtual函数发生于运行期
  - 对templates而言，接口时隐式的，奠基于有效表达式，多态则是通过template具现化和函数重载解析发生于编译期



# 条款42：了解typename的双重意义

- 在模板的声明中，typename和class没有什么不同

- template内出现的名称如果相依于某个template参数，称之为从属名称

  - 如果从属名称在class内呈嵌套状，则称为嵌套从属名称

- 不依赖任何template参数的名称，叫做谓非从属名称（独立名称）

- 对于嵌套从属名称，设想下列情景

  - ```cpp
    template<typename C>
    void point2nd(const C& container){
        C::const_iterator* x;//error, need 'typename' before 'C::const_iterator' because 'C' is a dependent scope
    }
    ```

  - 对于编译器而言，编译器无法识别这个`const_iterator`到底是一个什么东西，可能是static变量，可能是两个变量相乘

  - Cpp规则：如果解析器在template中遭遇一个嵌套从属名称，它便假设这名称不是个类型，除非你告诉它是。所以在缺省情况下，嵌套从属名称不是类型

  - 解决办法：

  - ```cpp
    template<typename C>
    void point2nd(const C& container, typename C::iterator iter){
        if (container.size() >= 2){
            typename C:const_iterator iter(container.begin());
            ...
        }
    }
    ```

  - 一般性规则：任何时候当你想要在template中指涉一个嵌套从属类型名称，就必须在紧邻它的前一个位置放上关键字同样typename

  - typename只被用来验明嵌套从属类型名称，其他名称不该有它的存在

  - **例外：**typename不可以出现在base classes list内的嵌套从属类型名称之前，也不可以在member initialization list（成员初始列）中作为base class修饰符

- 最后一个例子

  - ```cpp
    template<typename IterT>
    void workWithIterator(IterT iter){
        typename iterator_traits<IterT>::value_type temp(*iter);//萃取机，把容器里面的类型给提取出来，所以前面必须加上typename
        
        //可以简写
        typedef typename iterator_traits<IterT>::value_type value_type;
    }
    ```

- 总结

  - 声明template参数时，前缀关键字class和typename可互换
  - 使用关键字typename表示嵌套从属类型名称；但不得在base class lists或member initialization list内以它作为base class修饰符



# 条款43：学习处理模板化基类内的名称

- 设想下列情景

  - ```cpp
    template<typename Company>
    class LoggingMsgSender:public MsgSender<Company>{
        public:
        	void sendClearMsg(const MsgInfo& info){
                sendClear(info);
                /**
                这里的问题是，对于模板的推导来说，它不知道这个sendClear是谁
                即不到Company的话，根本不知道sendClear这个函数,也不知道这个函数存不存在
                **/
            }
    };
    ```

  - 原因：base class template有可能被特化，而特化的版本可能不提供和一般性template的接口，所以template往往拒绝在templatized base classes（模板化基类）内寻找继承而来的名称（说白了，就是传进来的基类有可能不是常规的，你写的基类函数（如sendclear）可能在其他的基类中没有出现）

- ps：模板的偏特化

  - ```cpp
    template<>
    class MsgSender<Company2>{};
    ```

- 解决方案：

  - ```cpp
    template<typename Company>
    class LoggingMsgSender:public MsgSender<Company>{
        public:
        	void sendClearMsg(const MsgInfo& info){
                this->sendClear(info);//成立，加入sendClear被继承
            }
    };
    ```

  - ```cpp
    template<typename Company>
    class LoggingMsgSender:public MsgSender<Company>{
        public:
        	using MsgSender<Company>::sendClear;//告诉编译器，请它假设sendClear位于base class中
        	void sendClearMsg(const MsgInfo& info){
                sendClear(info);
            }
    };
    ```

  - ```cpp
    template<typename Company>
    class LoggingMsgSender:public MsgSender<Company>{
        public:
        	void sendClearMsg(const MsgInfo& info){
                MsgSender<Company>::sendClear(info);//明白指出被调用的函数位于base class中
                //但这种方案不好，因为这会关闭“virtual绑定行为”
            }
    };
    ```

- 例子：

  - ```cpp
    class A{
        public:
            int a;
    };
    
    template<typename T>
    class B{
        public:
            T t1;
    };
    
    template<typename T>
    class C:public B<T>{
        public:
            void fuc(){
                cout << B<T>::t1.a << endl;
            }
    };
    ```

- 总结：

  - 可在derived class template内通过“this->”指涉base class templates内的成员名称，或借由一个明白写出的“base class资格修饰符”完成



# 条款44：将与参数无关的代码抽离templates

- review一下之前的知识

  - ```cpp
    template<typename T>
    class SquareMatrixBase{
        protected:
        	void invert(size_t matrixSize);
    };
    
    template<typename T, size_t n>
    class SquareMatrix:private SquareMatrixBase<T>{
        private:
        	using SquareMatrixBase<T>::invert;
        public:
        	void invert(){this -> invert(n);}//模板化基类内的函数会被derived classes覆盖
    };
    ```

- 其实，对于它书上说的逆矩阵的写法，我不是很理解，本来用一个模板一个参数就可以解决的，为什么要改为用多个模板才能解决啊？

- 对于类型参数导致的代码膨胀：int和long都有相同的二进制表达，但是有些编译器会把他们编译为两个不同的版本，使得代码膨胀

  - 解决办法：在大多数平台上，所有指针类型都有相同的二进制表述，即可以把`T*`都换为`void*`

- 请记住

  - Templates生成多个classes和多个函数，所以任何template代码都不该与某个造成膨胀的template参数产生相依关系
  - 因非类型模板参数而造成的代码膨胀，往往可消除，做法是以函数参数或class成员变量替换template参数
  - 因类型参数而造成的代码膨胀，往往可降低，做法是让带有完全相同二进制表述的具现类型共享实现码



# 条款45：运用成员函数模板接受所有兼容类型

- 背景：对于传统的子类和父类，我们都可以用父类的指针指向子类对象。但是，对于有模板的子类和父类，做不到改变指针指向的类型，比如让子类指向父类

  - ```cpp
    template<typename T>
    class SmartPtr{
        public:
        	explicit SmartPtr(T* realPtr);
    };
    
    SmartPtr<Top> pt1 = Smart<Middle>{new Middle};//将SmartPtr<Middle>转换为SmartPtr<Top>
    ```

- 解决办法之一

  - ```cpp
    template<typename T>
    class SmartPtr{
        public:
        	template<typename U>
        	SmartPtr(const SmartPtr<U>& other);//不是explicit，可以用于隐式转换
        //表示对任何类型T和任何类型U，这里可以根据SmartPtr<U>生成一个SmartPtr<T>
    };
    ```

  - 在class内声明泛化copy构造函数并不会阻止编译器生成它们自己的copy构造函数

- 请记住

  - 请使用member function templates（成员函数模板）生成”可接受所有兼容类型“的函数
  - 如果你声明member templates用于”泛化copy构造“或”泛化assignment操作“，你还是需要声明政策的copy构造函数和copy assignment操作符



# 条款46：需要类型转换时请为模板定义非成员函数

- 背景

  - ```cpp
    template<class T>
    class Rational{
        public:
        	Rational (const T& numerator = 0, const T& denominator = 1);
        	const T numerator() const;
        	const T denominator() const;
    };
    
    template<class T>
    const Rational<T> operator* (const Rational<T>& lhs, const Rational<T>& rhs){}
    
    Rational<int> oneHalf(1, 2);
    Rational<int> result = onHalf * 2;//这里的2不能隐式转换为Rational
    ```

  - 原因：template实参推导的时候从不将隐式类型转换函数考虑在内（但是可以将数组转换为数组指针之类的，都可以）

  - 解决办法：

    - ```cpp
      template<class T>
      class Rational{
          public:
          	friend const Rational<T> operator* (const Rational<T>& lhs, const Rational<T>& rhs);//把乘号设为friend函数
          	Rational (const T& numerator = 0, const T& denominator = 1);
          	const T numerator() const;
          	const T denominator() const;
      };
      
      template<class T>
      const Rational<T> operator* (const Rational<T>& lhs, const Rational<T>& rhs){}
      ```

    - 上述的代码可以过编译，但是无法执行：乘号函数被声明在类内，在类内没有被定义出来

    - 解决办法

      - ```cpp
        template<class T>
        class Rational{
            public:
            	//把乘号设为friend函数
            	friend const Rational<T> operator* (const Rational<T>& lhs, const Rational<T>& rhs){
                    return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
                }
            	Rational (const T& numerator = 0, const T& denominator = 1);
            	const T numerator() const;
            	const T denominator() const;
        };
        
        template<class T>
        const Rational<T> operator* (const Rational<T>& lhs, const Rational<T>& rhs){}
        ```

- 一路走来的奇怪的过程

  - 为了让类型转化可能发生于所有实参身上，我们需要一个non-member函数
  - 为了令这个函数被自动具现化，我们需要将它声明在class内部
  - 而在class内部声明non-member函数的唯一方法就是：令他成为一个friend

- 请记住

  - 当我们编写一个class template，而它所提供的“与此temlate相关的”函数支持“所有参数的隐式类型转换”时，请将那些函数定义为“class template内部的friend函数“



# 条款48：认识template元编程

- template metaprogramming（TMP）是编写template-based C++程序并执行于编译期的过程

  - 是以cpp写成，执行于cpp编译器内部的程序，一旦tmp程序结束执行，其输出

- 两个优点：

  - 让某些事情更容易
  - 将工作从运行器转移到了编译期，导致某些结果通常在运行期才能侦测到的，现在可在编译期找到
  - 同时具有更小的可执行文件，较短的运行期，较小的内存需求

- 缺点：编译时间变长了

- traits的解法就是用TMP的，引发“编译器发生于类型身上的if..else计算”

- TMP的递归甚至不是正常种类，TMP循环不涉及递归函数调用，而是涉及“递归模板具现化”

- 元编程の初体验

  - ```cpp
    template<int n>
    struct Fasctorial{
        enum{value = n * Fasctorial<n - 1>::value};
    };
    
    template<>
    struct Fasctorial<0>{
        enum {value = 1};
    };
    
    int main(){
        cout << Fasctorial<10>::value;
    }
    ```

- 元编程的用途

  - 确保度量单位正确，在编译期确保程序中所有度量单位的组合正确
  - 优化矩阵运算，提高执行速度，占用较少内存
  - 可以生成用户定制的设计模式实现品

- 总结：

  - Template metaprogramming（TMP，模板元编程）可将工作由运行期移往编译期，因而得以实现早期错误侦测和更高的执行效率
  - TMP可被用来生成“基于政策选择组合”的客户定制代码，也可用来避免生成对某些特殊类型并不适合的代码