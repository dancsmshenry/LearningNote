# member template

- ```cpp
  template <class T1, class T2>
  struct Pair
  {
      typedef T1 fritd_type;
      typedef T2 seconde_type;
  
      T1 first;
      T2 second;
  
      Pair() : first(T1()), second(T2()) {}
  
      Pair(const T1 &a, const T2 &b) : first(a), second(b) {}
  
      template <class U1, class U2>
      Pair(const Pair<U1, U2> &p) : first(p.first), second(p.second) {}
  };
  
  int main(){
      Pair<int, int> p1(1, 2.0);//这里初始化一个Pair对象，T1T2分别是int，int
      Pair<int, int> p2(p1);//这里设计好pairT1T2的初始值，然后再用p1去把它初始化
  }
  ```

- 初一看好像没什么用途，但是看了解析才发现，用到父类和子类上是真的好用

  - ```cpp
    class Base1{};
    class Derived1:public Base1{};
    
    class Base2{};
    class Derived2:public Base2{};
    
    pair<Derived1, Derived2> p1;
    pair<Base1, Base2> p2(p1);
    //上述代码变为
    pair<Base1, Base2> p2(pair<Derived1, Derived2>());
    ```

  - 理解

    - U2一定可以转换为T2的
    - 相当于后面给的范围会大于原有的范围，以便装下更多的类型（后面给的是父类吗，父类和子类是相通的）
    - 把一个鲫鱼和麻雀构成的pair，放到一个由鱼类和鸟类构成的pair中，是可以的（反之则不行）

- ```cpp
  template<typename _Tp>
  class shared_ptr:public __shared_ptr<_Tp>
  {
      template<typename _Tp1>
      explict shared_ptr(_Tp1* _p):__shared_ptr<_Tp>(__p){}
  };
  
  Base1* ptr = new Derived;//up-cast
  shared_ptr<Base1> sptr(new Derived1);//模拟up-cast
  ```
