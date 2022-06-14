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