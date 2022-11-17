# 模板模板参数

- template template parameter

- 只有在模板上的默认参数的位置上class和typename等变量才能共通

- ```cpp
  template<typename T, template<typename T> class Container>
  class XCls{
  private:
  	Container<T> c;
  public:
  	...
  };
  
  //ps：这里的typename在gcc中有一个bug，就是如果两个都写的是T的话是无法通过的，要把后面的T改为其他的变量才行
  //还是因为说，这里写成T会使得编译器认为是同时同一个变量，导致错误呢？
  
  template<typename T>
  using Lst = list<T, allocator<T>>
  //这里需要注意的是，list其实是不止一个参数的，它有一个参数是默认了的，所以要上述操作
  XCls<string, Lst> mylst2;
  ```

- 这里有一个问题：如果都是T的话，会不会就限制了Container的参数类型（即我不想要T这种类型，我想要其他类型，但是现在只能是T）？

- 就是在模板参数里面再加一个模板

- 注意：这里绑定了就不是模板了

  - ```cpp
    template<class T, class Sequence = deque<T>>
    class stack{};
    
    stack<int> s1;
    stack<int, list<int>> s2;//这里被绑定了，所以就不能叫做模板（参考上面，上面的T是没绑定的，好像有点牵强）
    stack<int, list<double>> s3;//要明白上面的=deque<T>只是提供了一个默认的参数罢了
    ```
