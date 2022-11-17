# Unifrom Initialization

- uniform initialization（一致性的初始化，设初值）

  - 在cpp11以前，对象类型的初始化可以用大括号，中括号，以及重载的标识符来进行初始化

  - 而在cpp11以后，都可以用大括号来初始化

    - ```cpp
      int values[] {1,2,3};
      vector<int> v{1,2,3,4,5,6,7};
      vector<string> cities{"","",""};
      complex<double> c{4.0,3.0};
      ```

  - 深究其本质：

    - 即编译器看到{t1,t2...tn}便做出`initializer_list<T>`，它关联到一个array<T,n>。调用 函数（例如ctor构造函数）时该array内的元素可被编辑器分解逐一传给函数

    - 但若函数参数是一个initializer_list<T>，调用者就不能给数个T参数然后以为它们会被自动转为一个initializer_list<T>传入

    - 例：

      - ```cpp
        vector<int> v{1,2,3,4,5,6,7};
        ```

      - 这里会形成一个initializer_list<int>，背后有个array<string>，调用vector<int>ctors时编译器找到了一个vector<int>ctor接收initializer_list<int>（即前面已经形成了一包东西，后面又找到一个函数来接收这一包东西，那就一包传给一包）

      - ```cpp
        complex<double> c{1.0, 4.0};
        ```

      - 这里形成一个initializer_list<double>，背后有个array<double, 2>。调用complex< double >的构造函数的时候，该array内的2个元素被分解传给构造函数（这里是前面把变量变成了一包东西，但是complex不接受一包东西的传递，只能逐个逐个的传递）

