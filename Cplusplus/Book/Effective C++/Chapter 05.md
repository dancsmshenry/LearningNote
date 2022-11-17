# 条款26：尽可能延后变量定义式的出现时间

- 看完这一条款，也就明白了为什么leetcode中的有些代码非要在使用某个变量之前才定义该变量

  - 对于工程代码，如果说前面的代码不需要某个变量，只有后面一部分才需要，而我们把所有的变量都定义在最前面，那么如果前面的部分代码出现了bug，那我最开始构造这个后面才用得到的变量岂不是浪费资源吗？

  - 同时，还有以下情况

    - ```cpp
      string encrpyPassword(const string& password){
          string encrypted;//这里调用了默认构造函数
          encrypted = password;//又调用了赋值函数
          encrypt(encrypted);
          return encrypted;
          
          //不如一把梭了它
          string encrypted(password);
      }
      ```

- 你不止应该延后变量的定义，直到非得使用该变量的前一刻为止，甚至应该尝试延后这份定义直到能够给它初值实参为止

- 请记住：

  - 尽可能延后变量定义式的出现，这样做可增加程序的清晰度并改善程序效率



# 条款27：尽量少做转型动作

- cpp兼容c中的转型操作

  - （类型）expression

- cpp中四种新式类型转换

  - const_cast：通常被用来将对象的常量性转除（去掉const）
  - dynamic_cast：安全向下转型，用来决定某对象是否归属继承体系中的某个类型，是唯一无法由旧式语法执行的动作，也是唯一可能耗费重大运行成本的转型动作
  - reinterpret_cast：低级转型，实际动作以及结果可能取决于编译器，是不可移植的
  - static_cast：强迫隐式转换（什么都可以强转，维度不可以转const）

- 新转型的好处：

  - 容易在代码中被辨认出来；各转型动作的目标愈窄化，编译器愈可能诊断出错误的运用

- 参考以下代码

  - ```cpp
    class Window{
        public:
        	virtual void onResize();
    }
    
    class Special: public Window{
        virutal void onResize(){
            static_cast<Window>(*this).onResize();
            /*
            这段代码的想法是说，想要在子类使用父类的onResize函数（然后以为是调用的是Special类型去使用父类函数）
            
            但实际上，是通过this新建了一个Window对象，从而调用onResize函数
            这里就会有多余的开销，浪费时间和空间
            
            同时，如果是想要通过Window的onResize来修改当前对象的属性，是不可以做到的
            因为这是新建出来的一个副本，这样就不符合设计者的想法了
            而Special的onResize就可以修改当前的对象
            */
        }
    }
    
    //解决办法
    class Special: public Window{
        virtual void onResize(){
            Window::onResize();
        }
    }
    ```

- dynamic_cast速度比较慢

- 避免父类指针指向子类的问题：

  - 第一， 使用容器并在其中存储直接指向derived class的指针（使用类型安全容器）
  - 第二，利用多态，在base class内提供virtual函数做你想对各个window派生类做的事，这样就不会发生父类指针指向子类对象的情况（将virtual函数往继承体系上方移动）

- 请记住：

  - 如果可以，尽量避免转型，特别是在注重效率的代码中避免dynamic_cast，如果有个涉及需要转型动作，试着发展无需转型的替代设计
  - 如果转型是必要的，试着将它隐藏于某个函数背后，客户随后可以调用函数，而不需要将转型放进它们自己的代码内
  - 宁可使用cpp-style转型，不要使用旧式转型，前者很容易辨认，而且也有着比较分门别类的职掌



# 条款28：避免返回handles指向对象内部成分

- 参考以下代码

  - ```cpp
    #include <iostream>
    #include <memory>
    
    using namespace std;
    
    class Point{
        public:
            Point(int x, int y) : x(x), y(y) {}
    
            void setX(int newx){x = newx;}
    
            void setY(int newy){y = newy;}
    
            int getX() const { return x; }
    
            int getY() const { return y; }
    
        private:
            int x;
            int y;
    };
    
    struct RectangleData{
        RectangleData(Point x, Point y) : ulhc(x), lrhcl(y) {}
        Point ulhc;
        Point lrhcl;
    };
    
    class Rectangle{
        public:
            RectangleData* r1;
    
            Rectangle(RectangleData* z):r1(z) { }
    
            Point& upperLeft() const{
                return r1->ulhc;
            }
    };
    
    int main(){
        Point p1(10, 20);
        Point p2(20, 30);
        RectangleData r11(p1, p2);
        const Rectangle r1(&r11);
    
        cout << "r1.upperleft().getX() = " << r1.upperLeft().getX() << endl;
        r1.upperLeft().setX(10000);
        cout << "r1.upperleft().getX() = " << r1.upperLeft().getX() << endl;
    }
    ```

  - 题外话：对于const的一个理解

    - 如果一个成员函数后面加上了一个const，就表示该函数不能对对象的属性做出变化

      - 这里有一个问题，什么是对象的属性？int，double，float都算是对象的属性吧，那如果是自己编写的对象呢？自己编写的对象的属性呢？
      - 经过测试，发现如果是以自己编写的对象作为实体的话，那么该对象如果作为一个大的对象的属性的话，该对象的属性也是不可变化的
      - 但，如果是把一个指向该对象的指针作为对象的属性的话，我感觉哈，应该是指针不可变，但是指针所指的该对象的属性是可以变的（即可以通过指针来修改对象属性的属性），那这样的话封装性就是不存在的了

    - 测试1：当函数为const的时候，是否可以修改对象的属性（包括基本类型和指针），发现是不可以的

      - ```cpp
        Point p3(10, 10);
        Point p4(100,100);
        
        class Rectangle{
            public:
                RectangleData* r1;
        
                Rectangle(RectangleData* z):r1(z) { }
        
                Point& upperLeft() const{
                    RectangleData* r2 = new RectangleData(p3, p4);
                    r1 = r2;//这里就会报错，因为const是保证对象的属性不发生变化，但是r1的指向，即r1所存储的地址发生了变化，不符合const，所以报错
                    return r1->ulhc;
                }
        };
        ```

    - 测试2：当函数为const的时候，是否可以修改对象的属性的属性（第一个属性为一个对象，第二个属性为前一个对象的属性），发现也是不可以的

      - ```cpp
        struct RectangleData{
            RectangleData(Point x, Point y) : ulhc(x), lrhcl(y) {}
            Point ulhc;
            Point lrhcl;
        };
        
        class Rectangle{
            public:
                RectangleData r1;
        
                Rectangle(RectangleData z):r1(z) { }
        
                Point& upperLeft() const{
                    return r1.ulhc;
                    /*
                    这里会报错：
                    首先，因为返回的是引用，本质是指针，可以借此来修改RectanglaData的ulhc
                    而被const修饰的函数是不可以修改对象的值的，所以会报错
                    */
                }
        };
        ```

  - ok，说完了题外话，这种方式就表明，即使是用const来修饰了变量，但是如果最终返回的是一个引用，还是有可能修改变更对象内部的值的，致使const变得无用。同样的，如果返回的是指针，或是迭代器，也是会间接修改对象的值的

    - 因为reference、point和迭代器都是handles（号码牌，用来取得某个对象）
    - 返回handles会使得对象的封装性减低，造成“虽然调用const成员函数却造成对象状态被更改”

  - 函数前面加上const表示函数的返回值不可被修改

  - 而如何解决上述问题呢？

    - ```cpp
      class Rectangle{
          public:
          	const Point& upperLeft() const{
                  return pData->ulhc;
              }
          
          	const Point& lowerRight() const{
                  return pData->lrhc;
              }//即在函数的前面加上const，防止返回的引用或指针或迭代器被修改
      }
      ```

- 另一个问题：

  - 如果让函数返回的是一个对象的话，并且还用指针来接收这个对象，就会导致在这条语句结束后，对象会被销毁，指针指向空值

- 请记住：

  - 避免返回handles（包括引用，指针，迭代器）指向对象内部。遵守这个条款可增加封装性，帮助const成员函数的行为像个const，并将发生“虚吊号码”的可能性降至最低



# 条款29、为“异常安全”而努力是值得的

- 当异常被抛出时，带有异常安全性的函数会：
  - 不泄露任何资源（用对象来管理资源）
  - 不允许数据败坏
- 异常安全函数提供以下三个保证之一：
  - 基本承诺：如果异常被抛出，程序内的任何事物仍然保持在有效状态下，没有任何对象或数据结构会因此而败坏
  - 强烈保证：如果异常被抛出，程序状态不改变，如果成功，就完全成功，如果失败，程序会恢复到“调用函数之前”的状态
  - 不抛掷保证：承诺绝不抛出异常，因为它们总是能够完成它们原先承诺的功能
- 请记住
  - 异常安全函数即使发生异常也不会泄漏资源或允许任何数据类型结构败坏，这样的函数区分三种可能的保证：基本型，强烈型，不抛异常型、
  - “强烈保证”往往能够以“copy and swap”实现出来，但“强烈保证”并非对所有函数都可实现或具备现实意义
  - 函数提供的“异常安全保证”通常最高只等于其所调用之各个函数的“异常安全保证”中的弱者



# 条款30：透彻了解inlining的里里外外

- 调用inline不需要蒙受函数调用所招致的额外开销

- inline可能增加你的目标码（过度使用）

- 如果inline函数的本体很小，编译器针对“函数本体”所产出的码可能比针对“函数调用”所产出的码更小（编译器会对inline函数进行优化）

- inline只是对编译器的一个申请

- 在类里面定义实现的成员函数都是inline

- 大部分编译器拒绝将太过复杂的函数inling，而所有的virtual都不会是inlining

- 总结：一个表面上看似inline的函数是否真实inline，取决于你的建置环境，主要取决于编译器

- 构造函数和析构函数往往都不是inline函数（它的底层非常精细复杂）

  - ```cpp
    Derived::Derived(){
        Base::Base();
        try{dm1.std::string::string()}
        catch(...){
            Base::~Base();
            throw;
        }
        ....
    }
    ```

- inline函数无法随着程序库的升级而升级，一旦程序设计者决定改变f，所有用到f的客户端程序都必须重新编译

  - 所以inline适合哪些比较小的，使用的多的，不会频繁更改的函数

- 请记住

  - 将大多数inlining限制在小型、被频繁调用的函数身上，这可使日后的调试过程和二进制升级更容易，也可使潜在的代码膨胀问题最小化，使程序的速度提升机会最大化
  - 不要只因为function templates出现在头文件，就将它们声明为inline



# 条款31：将文件间的编译依存关系降至最低

- 背景：如果这些头文件中又任何一个被改变，或这些头文件所以来的其他头文件有任何改变，那么每一个函数Person class的文件就得重新编译，任何使用Person class的文件也必须重新编译
- 解决办法：
  - 接口和实现分离，一个头文件写实现（实现），另一个头文件写接口（接口）
  - 设计纯虚函数，后面写的类都调用这个接口
- 一些设计策略
  - 如果使用object references或object pointers可以完成任务，就不要使用objects
  - 如果能够，尽量以class声明式替换class定义式
  - 为声明式和定义式提供不同的头文件
- 请记住
  - 支持“编译依存性最小化”的一般构想是：相依于声明式。不要相依于定义式、基于此构想的两个手段是handle classes和interface classes
  - 程序库头文件应该以”完全且仅有声明式“的形式存在，这种做法不论是否设计templates都适用