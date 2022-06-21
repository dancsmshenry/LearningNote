# 背景

- 在C++中，不存在大小是零的类。即便是空类，也要占据一个字节，否则无法比较两个空类对象是否是同一个对象（在C/C++中，默认使用地址来判断两个变量是否是同一个）
- **为保证同一类型的不同对象地址始终有别**，要求任何对象或成员子对象的大小至少为 1，即使该类型是空的类类型（即没有非静态数据成员的 class 或 struct）





# EBCO

- ```cpp
  #include <iostream>
  #include <cassert>
  
  class BaseEmpty { 
  public:
    BaseEmpty() { std::cout<<"Base address:    "<< this << std::endl;}
  };
  
  class DerivedEmpty: public BaseEmpty { 
  public:
    DerivedEmpty() { 
      std::cout<<"Derived address: "<< this << std::endl;
    }
  };
  
  class DerivedDeeperEmpty: public DerivedEmpty {
  public:
    DerivedDeeperEmpty() { 
      std::cout<<"deeper address:  "<< this << std::endl;
    }
  };
  
  class DerivedSameEmpty : public BaseEmpty, DerivedEmpty { 
  public:
    DerivedSameEmpty() { 
      std::cout<<"DerivedSameEmpty address: "<< this << std::endl;
    }
  };
  
  class BaseAnotherEmpty { };
  class DerivedDiffEmpty : public BaseEmpty, BaseAnotherEmpty { };
  
  int main(int argc, char const *argv[]) {
  
    BaseEmpty empty_1{};
    BaseEmpty empty_2{};
    std::cout << sizeof(DerivedDeeperEmpty) << std::endl;
    //	空类继承空类
    //	大小为1
    // 在空类被用作基类时，如果不给它分配内存并不会导致它被存储到与同类型对象（包括子类对象）相同的地址上，那么就可以不给它分配内存
    
    auto derivedSame = DerivedSameEmpty{};
    std::cout<<"size: "<<sizeof(derivedSame)<<std::endl;
    //	空类继承具有父子关系的空类
    //	大小为2
    // 因为在这里，BaseEmpty和DerivedEmpty分别属于两个不同的对象，即继承的时候是先分别创建这两个对象，所以它们两个对象的地址不同，所以就需要2个字节，就不能有EBCO
    
    sizeof(DerivedDiffEmpty{});
    //	空类继承没有父子关系的空类
    //	大小为1
    // 这里的大小是1，因为两个空类没有父子关系，即使是在同一个地址上，也可以区别出来
  }
  ```

- 在空类被用作基类时，如果不给它分配内存并不会导致它被存储到与同类型对象（包括子类对象）相同的地址上，那么就可以不给它分配内存

- 因此，在空类`A`作为基类时，空类`B`继承`A`，空类`C`继承`B`，如果要触发编译器的EBCO机制，那么空类`C`不能再继承`A`及其子类

- 因此，如果一个类继承了两个空类，那么大小还是为1







# 应用

- 当我们想让一个类D包含另一个类B的功能，一般而言有两种做法：D内含一个对象B；D继承于类B
- 若B是一个空类，即一个只有成员函数而没有任何数据成员的类时，继承会比内含更省空间。因为内含时，B还占有1byte的占位空间，以及3byte的对齐空间



stl中的应用

- 容器继承空间配置器类别用以分配内存空间

- ```cpp
  struct _Vector_impl
  	: public _Tp_alloc_type, public _Vector_impl_data
    //	这里继承了默认的空间配置器
  ```

- 没有选择将对象作为成员变量，用于节省空间







# 参考

- https://mp.weixin.qq.com/s?__biz=MzkyMjIxMzIxNA==&mid=2247484770&idx=1&sn=460a07d3abaec0ca0d88721c7fb4d2fb&scene=19#wechat_redirect
- https://zh.cppreference.com/w/cpp/language/ebo