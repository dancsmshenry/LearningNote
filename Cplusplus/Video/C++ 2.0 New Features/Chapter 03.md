# Spaces in Template Expression、nullptr and str::nullptr_t、Automatic Type Deduction with auto

- spaces in template expressions

  - ```cpp
    vector<list<int> >;//ok in each cpp version
    vector<list<int>>;//ok, since cpp11
    //避免了编译器把其认为>>的情况
    ```

  - 在过去的cpp版本中，如果两个>>连在一起，编译器会认为那是操作符

- nullptr and std::nullptr_t

  - 在cpp11里面，用nullptr来表示空指针

  - 在cpp11以前，把一个指针设为空指针，设为NULL或0都是可以的

  - ```cpp
    void f(int);
    void f(void*);
    f(0);//calls f(int);
    f(NULL);//calls f(int)/f(void*),ambiguous otherwise
    f(nullptr);//calls f(void*);
    ```

  - nullptr的类型是nullptr_t

- automatic type deduction with auto

  - auto可以用来自动类型推导，即有些比较难写的类型，可以用这个类型的一个变量来表示，从而推导得出该类型并给一个变量

    - ```cpp
      auto i = 43;//i has type int
      double f();
      auto d = f();//d has type float
      
      auto l = [](int x) -> bool{
          //auto也可以用于lambda式
      }
      
      //以前
      list<string> c;
      list<string>::iterator ite;
      
      //现在
      list<string> c;
      auto ite = find(c.begin(), c.end(), target);
      ```

