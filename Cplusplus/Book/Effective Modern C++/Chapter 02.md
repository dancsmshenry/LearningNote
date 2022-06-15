# 条款5：优先选用auto，而非显示式类型声明

- 

- 在cpp14中可以这样写

  - ```cpp
    auto derefless = [](const auto& p1, const auto& p1){
        return *p1 < *p2;//把auto作为变量的命名
    }
    ```



情景一

- 用auto声明的变量，其类型都推导自其初始化物，所以它们必须初始化

- 所以可以避免定义变量的时候未初始化

- ```cpp
  int x1;//未初始化，但是能过编译
  auto x2; //未初始化，但是不能过编译
  auto x3 = 1; // 已初始化，能过编译
  ```

- 由于auto使用了型别推导，就可以用它来表示只有编译器才能掌握的型别

- ```cpp
  auto derefUPLess = [](const std::unique_ptr<Widget>& p1,
                       const std::unique_ptr<Widget>& p2) {
      return *p1 < *p2;
  }
  ```





情景二

- std::function是cpp11标准库中的一个模板，可以涉任何可调用对象，任何可以像函数一样实施调用之物，正如你若要创建一个函数指针就必须指定欲指涉的函数的型别

- ```cpp
  bool(const std::unique_ptr<Widget> &p1,
  const std::unique_ptr<Widget> &p2);
  
  std::function<bool(const std::unique_ptr<Widget> &p1,
  const std::unique_ptr<Widget> &p2)> func;
  ```

- 当使⽤这个对象保存⼀个闭包时它可能⼤小不⾜不能存储，这个时候 std::function 的构造函数将会在堆上⾯分配内存来存储

- 这就造成了使⽤ std::function ⽐auto会消耗更多的内存。并且通过具体实现我们得知通过std::function调⽤⼀个闭包⼏乎⽆疑⽐auto声明的对象调⽤要慢

- 从结果上来说，使用function的缺点：书写麻烦，而且function的占用比auto大，所以还是auto好





情景三

- vector的长度为`std::vector<int>::size_type`
- 但是在32位的windows平台上，是unsigned；而到了64位的windows上，size_type变为64位了，可移植性就差了

- 面对size_type在不同平台的表现，用auto来表示size最好





情景四

- ```cpp
  std::unordered_map<std::string, int> m;
  
  for (const std::pair<std::string, int>& p:m){}
  //	pair里面的键值部分应该是const的，即应该是这样的std::pair<const std::string, int>
  //	但是上面上面声明的变量却不是const，编译器就要把其进行转化，耗时耗力
  
  //解决办法
  for (const auto& p:m){}
  //	还有一个优点，就是当前这个取址得到的是指针，而上面的那一个返回的是一个临时指针，还要析构
  ```

- auto类型可以随着其初始化表达式的类型变化而自动变化





### 要点速记

- auto变量必须初始化，基本上对会导致兼容性和效率问题的类型比匹配现象免疫，还可以简化重构流程，通常也比显式指定类型要少打一些字
- auto类型的变量有着条款2和条款6所描述的毛病







# 条款6：当auto推导的型别不符合要求时，使用带显式型别的初始化物习惯用法



### 要点速记

- “隐形”的代理型别可以导致auto根据初始化表达式推导出“错误的”型别
- 带显式型别的初始化习惯用法强制auto推导出你想要的型别