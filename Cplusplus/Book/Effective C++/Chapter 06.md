# 条款32：确定你的public继承塑模出is-a关系

- 类D以public的方式继承B，则表示每一个D都是一个B，即B比D表现出更一般化的概念，D比B表现出更特殊化的概念
- 所谓的最佳设计，取决于系统希望做什么事，包括现在和未来
- 这里有两个例子，引人深思：
  - 企鹅是鸟类吗，是的；那鸟类都会飞吗？第一感觉，是啊，鸟嘛，肯定会飞的嘛。但是事实上企鹅是不会飞的。
  - 所以如果要public继承鸟类的话，就要思考fly函数到底应该怎么放置才算好
    - 第一种，鸟类是分为会飞的和不会飞的，所以就让企鹅继承不会飞的鸟类即可
    - 第二种，重写企鹅的fly函数，令其在运行期发生报错
  - 那正方形是矩形吗？是的，那我写一个函数令矩形的一组边变大，如果正方形是直接继承使用的话，按照正方形的性质，这个函数应该令正方形所有的边都变大才对啊
- 所以，对于类与类之间的关系一定要慎重考虑
- 请记住：
  - public继承意味is-a。适用于base classes身上的每一件事情一定也适用于derived classes身上，因为每一个derived class对象也都是一个base class对象



# 条款33：避免遮掩继承而来的名称

- 补充：

  - 虚函数是为了多态而生的，而不是因为继承同名而生，所以是纯虚函数才需要在继承后被重写，虚函数可以不被重写

- 在继承体系中，对于一个变量来说，是先在该函数内部进行查找，然后是在该子类中进行查找，接着再在其父类中进行查找，而后是在其命名空间查找

- 而对于一个函数也是一样

  - 如果父类和子类都有这个函数，那么一般情况下，父类的这个同名函数会被掩盖掉，只能调用得到子类的该名函数

    - 此时，如果想要调用父类的该函数的话，那就

      - ```cpp
        class Base{
            public:
            	void mf3(int z);
        };
        
        class Derived : public Base{
            public:
            	using Base::mf3;//使得Base中的mf3可以被子类看见
        }
        ```

  - 如果子类没有而父类有的话，那就调用父类的该函数

- 私有继承：父类的所有属性函数到子类都变为了private

  - ```cpp
    class Base{
        public:
        	virtual void func1() = 0;
        	virtual void mf1(int);
    };
    
    class Derived:private Base{
        public:
        	virtual void mf1(){
                Base::mf1();//暗自变为inline
            }
    }
    ```

  - inline转交函数的另一个用途是为那些不支持using声明式的老旧编译器另辟一条新路，将继承而得的名称汇入derived class作用域内

- 请记住：

  - derived classes内的名称会遮掩base classes内的名称，在public继承下从来没有人希望如此
  - 为了让被遮掩的名称再见天日，可使用using声明式或转交函数



# 条款34：区分接口继承和实现继承

- 纯虚函数（pure virtual）（只继承接口）

  - 性质

    - 不能实例化有纯虚函数的类
    - 任何继承了这个类的类都必须重新声明该函数

  - 声明一个pure virtual函数的目的是为了让derived class只继承函数接口

    - 抽象类的纯虚函数是可以被定义的，也可被子类调用

      - ```cpp
        class Shape{
            public:
            	virtual void draw() const = 0;
        }
        
        class Rectangle{
            
        };
        
        Shape* ps = new Rectangle;
        ps->Shape:draw();
        ```

- 虚函数（impure virtual）（继承接口和一份强制实现）

  - 为多态而生
  - 目的：为了让子类继承该函数的接口和缺省实现
    - 对于每一个子类，最好都要继承重写这个函数，如果子类不写，也可以退回到父类的版本

- non-virtual函数（继承接口和一份强制实现）

  - 目的：为了令derived class继承函数的接口及一份强制性执行

- tips：

  - 不要把所有的函数都设为non-virtual，这样子类就无法特化操作
  - 也不要把所有的函数都变为virtual，感觉会加重子类的负担

- 请记住：

  - 接口继承和实现继承不同，在public继承之下，derived class总是继承base class的接口
  - pure virtual函数只具体指定接口继承
  - 简朴的impure virtual函数具体指定接口继承及缺省实现继承
  - non-virtual函数具体指定接口继承以及强制性实现继承



# 条款35：考虑virtual函数以外的其他选择

- NVI（non-virtual-interface）
  - 将接口和实现分开，即接口设为public non-virtual函数，而实现函数变为private-virtual函数
- straegy设计模式



# 条款36、绝不重新定义继承而来的non-virtual函数

- 问题背景：

- ```cpp
  #include <iostream>
  
  using namespace std;
  
  class A{
      public:
          void test(){
              cout << "A::test()" << endl;
          }
  };
  
  class B:public A{
      public:
          void test(){
              cout << "B::test()" << endl;
          }
  };
  
  int main(){
      B b1;
      A *a1 = &b1;
      a1->test();//A::test()，明明是B对象，但是后面调用的还是A对象的函数值
  }
  ```

- 原因：因为指针a1始终是指向A类型的指针，通过a1调用的non-virtual函数永远是A类型所定义的版本（本质：non-virtual是静态绑定的）

- 解决办法：virtual是动态绑定的

- 决定因素不在对象本身，而在于“指向该对象的指针”

- 结论：任何情况下都不应该重新定义一个继承而来的non-virtual函数



# 条款37：绝不重新定义继承而来的缺省参数值

- virtual函数系动态绑定（late binding，就是在程序中被声明时所采用的类型），缺省参数值却是静态绑定（early binding，就是目前对象所指的类型）

- virtual函数是动态绑定，缺省参数值却是静态绑定，即有可能会出现“调用一个定义于derived class内的virtual函数，却使用了base class为它所指定的缺省参数”

  - 即B类继承了A类的虚函数，但是这个虚函数各自有各自缺省参数，以至于调用B类的虚函数，传进去的却是A类的缺省函数

- 解决办法：

  - 此前的方法

    - ```cpp
      class Shape{
          public:
          	virtual void draw(ShapeColor color = Red) const = 0;
      };
      
      class Rectangle :public Shape{
          public:
          	virtual void draw(ShapeColor color = Red) const;
      };
      ```

  - NVI手法后：

    - ```cpp
      class Shape{
          public:
          	void draw(ShapeColor color = Red) const{
                  doDraw(color);
              }
          
          private:
          	virtual void doDraw(ShapeColor color = Red) const = 0;
      };
      
      class Rectangle:public Shape{
          public:...
          private:
          	virtual void doDraw(ShapeColor color) const;
      };
      ```

- 请记住

  - 绝对不要重新定义一个继承而来的缺省参数值，因为缺省参数值都是静态绑定，而virtual函数——你唯一应该覆写的东西——却是静态绑定



# 条款38、通过复合塑模出has-a或“根据某物实现出”

- 复合的意思是has-a（一个）或is-implemented-in-terms-of（根据某物实现出）
- 一个具体的场景
  - 想要写一个set，发现stl中有一个list可以复用，但是最后发现，list可以重复数据，而set不可以（这就是复用，感觉有点像侯捷之前说的委托）
  - 但还是想要用list来写，又发现两者不是is-a的关系，所以就用复合，即set中有一个数据成员是list，同时set的接口都用list来实现
- 请记住
  - 复合（composition）的意义和public继承是不一样的
  - 在应用层（application domain），复合意味has-a（有一个），在实物领域，复合意味着is-implemented-in-terms-of（根据某物实现出）



# 条款39：明智而审慎地使用private继承

- 对于private继承

  - 编译器不会自动将一个derived class对象转换为一个base class对象（针对private继承来说）
  - 由private base class继承来的所有成员，在derived class中都会变为private属性

- private继承意味着：implemented in terms of（根据某物实现出）

- private主要用于：

  - 当一个意欲称为derived class者想访问一个意欲称为base class者的protected成分
  - 或为了重新定义一或多个virtual函数

- private继承不能使用多态了嘛？

  - ```cpp
    #include<iostream>
    
    class A{
        public:
            virtual void test(){
                std::cout << "A::test()" << std::endl;
            }
    };
    
    class B:private A{
        public:
            virtual void test(){
                std::cout << "B::test()" << std::endl;
            }
    };
    
    int main(){
        B b;
        A *a1 = &b;
        // b.test();
    }
    ```

  - 更加准确的说，对于私有继承，不能用父类指针指向子类对象

  - 所以，private继承确实不能用多态了

- 对于空对象

  - ```cpp
    class A{};//它的大小是1，里面有一个char字符；所以如果它作为一个类对象的成员的话，会占用一个字符
    //但是，如果一个空类作为一个基类，被子类私有继承了的话，就不会占用大小，如：
    
    class B:private A{
        int x;//sizeof(A) == sizeof(int)
    };
    ```

  - EBO(空白基类最优化)

- 请记住

  - Private继承意味is-implemented-in-terms-of（根据某物实现出）。通常比复合（compoosition）的级别低，但是当derived class需要访问protected base class的成员，或需要重新定义继承而来的virtual函数时（这里也表明了会导致多态失效），这么设计是合理的
  - 和复合（composition）不同，private 继承可以造成empty base最优化，这对致力于“对象尺寸最小化”的程序库开发者而言，可能很重要



# 条款40：明智而审慎地使用多重继承

- 如果没有虚继承：A类继承了Base类，B类继承了Base类，C类同时继承了A类和B类，那么C类中就会有两个Base类，那到底该听谁的呢？

  - ```cpp
    class Base{
        int a;
    };
    
    class A:public Base{};
    
    class B:public Base{};
    
    class C:public B, public C{};//菱形继承
    
    C c1;//c1.a = ?，从逻辑上看，应该是只有一个a的
    
    //没有虚继承
    c1.A::a = 10;
    c1.B::a = 100;//用作用域来访问变量
    ```

- 解决办法：

  - ```cpp
    class Base{
        int a;
    };
    
    class A:virtual public Base{};
    
    class B:virtual public Base{};
    
    class C:public B, public C{};//菱形继承，虚继承来解决二义性
    ```

- cpp的解析规则：首先确认这个函数对此调用之言是最佳匹配，找出最佳匹配函数后才检验其可取用性

- 使用virtual继承的那些classes所产生的对象往往比使用non-virtual继承的兄弟吗体积大，访问virtual base classes的成员变量时，也比访问non-virtual base classes的成员变量速度慢

- virtual继承的成本

  - classes若派生自virtual bases而需要初始化，必须认知其virtual class
  - 当一个新的derived class加入继承体系，它必须承担其virtual class的初始化责任

- 忠告

  - 非必要不使用base classes
  - 尽量避免在其中放置数据

- 后面举了一个CPerson，IPerson和PersonInfo三个类关系的例子

  - CPerson需要实现PersonInfo类中的一些功能，那么就有两种实现方式：私有继承或复合
  - IPerson的话则是CPerson本应该继承的对象类
  - 所以这里就用到了多重继承

- 请记住

  - 多重继承比单一继承复杂，它可能导致新的歧义性，以及对virtual继承的需要
  - virtual继承会增加大小、速度、初始化（及赋值）复杂度等等成本，如果virtual base class不带任何数据，将是最具使用价值的情况
  - 多重继承的确有正当用途。其中一个情节涉及“public继承某个Interface class”和“private继承某个协助实现的class”的两相结合