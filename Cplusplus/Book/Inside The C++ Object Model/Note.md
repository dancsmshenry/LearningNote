### 第二章 构造函数语意学

#### 2.1 Default Constructor 的构造操作

- 分清楚是编译器的需要还是程序的需要
- 带有 default constructor 的 member class object 
  -  如果A类包含B类，但是没有显式的写出A类的默认构造函数，那么编译器就会自动为你提供一个隐式的构造函数，这个构造函数会根据情况调用B类的构造函数
  - 但是这个隐式的构造函数，不会对类中的数据（int，double 等数据）进行初始化的（这是程序员的需要，不是编译器的需要）
  - 如果 class A 内含一个或一个以上的 member class objects，那么 class A 的每一个 constructor 必须调用每一个 member classes 的 default constructor
    - 即如果一个类的成员包含多个类，那么这个类的每一个构造函数都会调用其包含的类的构造函数
    - 调用的顺序和声明的顺序一样
    - 即编辑器会为我们的代码进行扩张
- 带有 default constructor 的 base class 
  - 如果一个没有任何 constructors 的 class 派生自一个“带有 default constructor ”的 base class，那么这个 derived class 的 default constructor 会被视为 nontrivial，并因此需要被合成出来，它将调用上一层 base classes 的 default constructors





#### 2.4 成员们的初始化队伍

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
        _name.String::operator=(temp);
        temp.String::~String();//摧毁临时对象
        _cnt = 0;
        
        //这样做的成本就是消耗很高
    }
    ```

  - 而这种情况在template中经常发生

    - ```cpp
      template<class type>
      foo<type>::foo(type t){
          _t = t;
      }
      ```

- 注意：list中的项目顺序是由class中的members声明顺序决定的，不是由列表中的排序决定的