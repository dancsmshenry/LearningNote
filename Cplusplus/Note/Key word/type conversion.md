# static_cast

#### 用法

- ```cpp
  static_cast < type-id > (expression);//该运算符把expression转换为type-id类型
  ```



#### 作用

- 用于基本数据类型之间的转换，如把int转换成char，把int转换成enum
  - 把空指针转换成目标类型的空指针 
  - 把任何类型的表达式转换成void类型
  - 用于类层次结构中基类（父类）和派生类（子类）之间指针或引用引用的转换
    - 可以上行转换（派⽣类指针->基类指针）和下行转换（基类指针->派⽣类指针），但下行转换没有动态类型检查，所以不安全

- 优点
  - 更加安全
  - 更加直接明显，能够一眼看出是什么类型转换成什么类型

- 缺点
  - 没有运行时类型检查来保证转换的安全性
  - 不能用于在不同类型的指针之间互相转换
  - 不能用于整型和指针之间的互相转换
  - 不能用于不同类型的引用之间的转化
  - **不能转换掉const**或volatile，或者 __unaligned属性






# dynamic_cast

#### 用法

- ```cpp
  dynamic_cast<type-id> (expression);//	type-id 必须是类指针，类引⽤或 void*
  //	如果 type-id 是类指针类型，那么expression也必须是一个指针，如果 type-id 是一个引用，那么 expression 也必须是一个引用
  ```

- 要么是指针，要么是引用



#### 作用

- 主要用于类层次间的上行转换和下行转换，还可以用于类之间的交叉转换 
- 专⻔⽤于派⽣类之间的转换
- dynamic_cast运算符可以在执行期决定真正的类型，也就是说expression必须是多态类型
  - 如果下行转换是安全的（也就说，如果基类指针或者引用确实指向一个派生类对象）这个运算符会传回适当转型过的指针
  - 如果下行转换不安全，这个运算符会传回空指针（也就是说，基类指针或者引用没有指向一个派生类对象）
  - ⽽static_cast，当类型不⼀致时，转换过来的是错误的指针，可能造成⾮法访问等问题
- 在类层次间进行上行转换时，dynamic_cast和static_cast的效果是一样的 
- 在进行下行转换时，dynamic_cast具有类型检查的功能，比static_cast更安全

纠正

- 基类对象（指针）转子类对象（指针），是不安全的，在dynamic_cast中是不会成功的
  - 那么为什么基类转子类是不安全的，是因为：
  - 基类是包含于派生类的，即基类的“体积”比派生类的小。如果有一个基类对象的指针强转为派生类，我们调用派生类的方法(而基类没有)的时候，就会访问到一个不存在的东西，之后就是未知的行为了(极有可能崩溃)
- 而在dynamic_cast中，失败的话会返回nullptr
- 而子类转基类都是安全的







# reinterpret_cast

#### 用法

- type-id 必须是一个指针、引用、算术类型、函数指针或者成员指针

- ```cpp
  reinterpret_cast<type-id>(expression);
  //type-id必须是一个指针、引用、算术类型、函数指针或者成员指针，用于类型之间进行强制转换
  ```



#### 作用

- 可以将整形转换为指针，也可以把指针转换为数组可以在指针和引⽤之间进⾏肆⽆忌惮的转换
- 它可以用于类型之间进行强制转换
- 从底层对数据进⾏重新解释，依赖具体的平台，可移植性差
- 不到万不得已，不要使⽤这个转换符，⾼危操作





# const_cast

#### 用法

- ```cpp
  const_cast <type-id> (expression);
  ```





#### 作用

- 专⻔⽤于 const 属性的转换，去除 const 性质，或增加 const 性质；用来修改类型的const或volatile属性
- 唯⼀⼀个可以操作常量的转换符
- 常量指针被转化成非常量的指针，并且仍然指向原来的对象
- 常量引用被转换成非常量的引用，并且仍然指向原来的对象 
- 一般用于修改底指针，如const char *p形式







# example

- ```cpp
  #include <iostream>
  using namespace std;
  class Base {
  public:
      Base() : b(1) {}
      virtual void fun(){};
      int b;
  };
  
  class Son : public Base {
  public:
      Son() : d(2) {}
      int d;
  };
  
  int main() {
      //reinterpret_cast(以下两者效果相同)
      int n = 97;
      int *p = &n;
      char *c = reinterpret_cast<char *>(p);
      char *c2 = (char *)(p);
      cout << "reinterpret_cast输出：" << *c2 << endl;
  
      // const_cast
      const int *p2 = &n;
      int *p3 = const_cast<int *>(p2);
      *p3 = 100;
      int *i = nullptr;
      const int* p = const_cast<const int*>(i); // 也可以用来添加const熟悉
      cout << "const_cast输出：" << *p3 << endl;
  
      // static_cast
      Base *b1 = new Son;
      Base *b2 = new Base;
      Son *s1 = static_cast<Son *>(b1); //同类型转换
      Son *s2 = static_cast<Son *>(b2); //下行转换，不安全
      cout << "static_cast输出：" << endl;
      cout << s1->d << endl;
      cout << s2->d << endl; //下行转换，原先父对象没有d成员，输出垃圾值
      
      // dynamic_cast
      Son *s3 = dynamic_cast<Son *>(b1); //同类型转换
      Son *s4 = dynamic_cast<Son *>(b2); //下行转换，安全
      cout << "dynamic_cast输出：" << endl;
      cout << s3->d << endl;
      if (s4 == nullptr) cout << "s4指针为nullptr" << endl;
      else cout << s4->d << endl;
  }
  
  
  // 输出结果
  // reinterpret_cast输出：a
  // const_cast输出：100
  // static_cast输出：
  // 2
  // -33686019
  // dynamic_cast输出：
  // 2
  // s4指针为nullptr
  ```





# 参考

- https://zhuanlan.zhihu.com/p/368267441