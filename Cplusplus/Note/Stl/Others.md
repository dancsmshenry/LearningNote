# 为什么stl的扩容没有用到移动构造

- 可以发现 `std::vector` 的move构造函数并没有采用 `std::move`，而是调用的copy构造函数
- 因为移动构造意味着所有权的变更，因此在移动构造的过程中，如果出现了异常，那么原始数据很有可能是无法恢复的
- 而拷贝构造就不一样了，即使产生了异常，原始数据还是存在的。这也是 STL 中的设计思路之一







# back()

- ```cpp
  typedef typename _Alloc_traits::reference		reference;
  reference
  back() _GLIBCXX_NOEXCEPT
  {
  __glibcxx_requires_nonempty();
  return *(end() - 1);
  }
  ```

- back返回的是对象元素的引用
- 如果被引用的对象析构或消失了，那么这就是一个空引用...







# stl容器不能用memset

- 不要用memset对容器进行清空初始化，因为容器的内部结构很复杂，必定codedump，从而后续造成内存泄漏
- 比如说，vector中有其自身的结构，不能单纯的按字节进行初始化。使用memset对vector进行初始化，会破坏vector中的结构，造成vector中的数据错误







# 不要继承stl容器

- 它们的析构函数都不是虚析构，多态的情况下会内存泄漏







# 萃取

- traits运用显式模板特殊化将代码中因为类型不同而发生变化的片段提取出来，用统一的接口来包装，并通过traits模板类公开的接口间接访问相应的类

- traits中文意思是特性，它通过提取不同类的共性，使得可以统一处理

- ```cpp
  #include <iostream>
  using namespace std;
  
  //①基本类写法
  class IntArray
  {
  public:
      IntArray()
      {
          a = new int[10];
          for (int i = 0; i < 10; ++i)
          {
              a[i] = i + 1;
          }
      }
      ~IntArray()
      {
          delete[] a;
      }
  
      int GetSum(int times)
      {
          int sum = 0;
          for (int i = 0; i < 10; ++i)
              sum += a[i];
          cout << "int sum=" << sum << endl;
          return sum * times;
      }
  
  private:
      int *a;
  };
  class FloatArray
  {
  public:
      FloatArray()
      {
          f = new float[10];
          for (int i = 1; i <= 10; ++i)
          {
              f[i - 1] = 1.0f / i;
          }
      }
      ~FloatArray()
      {
          delete[] f;
      }
      float GetSum(float times)
      {
          float sum = 0.0f;
          for (int i = 0; i < 10; i++)
              sum += f[i];
          cout << "float sum=" << sum << endl;
          return sum * times;
      }
  
  private:
      float *f;
  };
  //②模板写法
  template <class T>
  class Apply
  {
  public:
      float GetSum(T &t, float inarg)
      {
          return t.GetSum(inarg);
      }
  };
  
  //以上方法不能完全解决我们的问题(函数返回值固定，就会导致异常)
  //③采用萃取机制：模板特化
  template <class T>
  class NumTraits
  {
  };
  //模板特化的格式
  template <>
  class NumTraits<IntArray>
  {
  public:
      typedef int resulttype;
      typedef int inputargtype;
  };
  template <>
  class NumTraits<FloatArray>
  {
  public:
      typedef float resulttype;
      typedef float inputargtype;
  };
  template <class T>
  class Apply2
  {
  public:
      NumTraits<T>::resulttype GetSum(T &obj, NumTraits<T>::inputargtype inputarg)
      {
          return obj.GetSum(inputarg);
      }
  };
  int main()
  {
      IntArray intary;
      FloatArray floatary;
      Apply<IntArray> ai;   //采用模板
      Apply<FloatArray> af; //采用模板
      cout << "1整型数组的和3倍：" << ai.GetSum(intary, 3) << endl;
      cout << "1浮点数组的和3.2倍：" << af.GetSum(floatary, 3.2f) << endl;
      cout << endl;
      cout << endl;
      Apply2<IntArray> ai2;   //采用萃取
      Apply2<FloatArray> af2; //采用萃取
      cout << "2整型数组的和3倍：" << ai2.GetSum(intary, 3) << endl;
      cout << "2浮点数组的和3.2倍：" << af2.GetSum(floatary, 3.2f) << endl;
      return 0;
  }
  ```

- 即利用模板把数据特化出来，并提供统一名称类型的接口，方便用户使用

- https://zhuanlan.zhihu.com/p/358113531



- 由此引申出的有关typename的问题：如果要引用别的类里面的类型（因为类是一个作用域，就相当于要用A::value_type的话），就必须在其前面加上一个typename，因为编译器不能判断你说的这个到底是什么类型，所以要加上一个关键词告诉编译器这是一个型别，如此才能顺利通过编译





- 利用typedef和模板的偏特化，实现对类型的提取

- ```cpp
  template<class T>
  struct iterator_traits{
      typedef typename T::value_type value_type;
  }
  
  template<class I>
  typename iterator_traits<I>::value_type test() {}
  //	利用模板和内嵌型别就把当前I中的value_type给提取出来，作为返回值了
  
  template<class T>
  struct iterator_traits<T*>{ // 模板的偏特化
      typedef T value_type; // 这里可能会萃取出const
  } // 可以方便的提取原生指针的类型
  
  template<class T>
  struct iterator_traits<const T*> {
      typedef T value_type; // 这里就不会萃取出const，直接得到T
  }
  ```



- 对于萃取的理解
  - 提取一个类中我们想要的类型
  - 概念很简单，但是运用起来很复杂，参考stl的关于traits的讲述



使用 accumulate 可以计算求和， max_element 求最大值

```C++
#include "numeric"

std::vector<int> vec(10, 10);
auto sum = std::accumulate(vec.begin(), vec.end(), 0);

auto itmax = std::max_element(vec.begin(), vec.end()); // return iterator
```
