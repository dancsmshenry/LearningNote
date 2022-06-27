https://www.zhihu.com/question/419304773/answer/1453712022



constexpr是C++11中新增的关键字，其语义是“常量表达式”，也就是在编译期可求值的表达式。最基础的常量表达式就是字面值或全局变量/函数的地址或sizeof等关键字返回的结果，而其它常量表达式都是由基础表达式通过各种确定的运算得到的。constexpr值可用于enum、switch、数组长度等场合。

constexpr所修饰的变量一定是编译期可求值的，所修饰的函数在其所有参数都是constexpr时，一定会返回constexpr。

- ```cpp
  constexpr int Inc(int i) {
  return i + 1;
  }
  constexpr int a = Inc(1);// ok
  constexpr int b = Inc(cin.get());// !error
  constexpr int c = a * 2 + 1;// ok
  ```

- 



constexpr还能用于修饰类的构造函数，即保证如果提供给该构造函数的参数都是constexpr，那么产生的对象中的所有成员都会是constexpr，该对象也就是constexpr对象了，可用于各种只能使用constexpr的场合。注意，constexpr构造函数必须有一个空的函数体，即所有成员变量的初始化都放到初始化列表中。

- ```cpp
  struct A {
  constexpr A(int xx,int yy): x(xx), y(yy) {}
  int x, y;
  };
  constexpr A a(1, 2);
  enum {SIZE_X = a.x, SIZE_Y = a.y};
  /constexpr的好处：
  ```

- 



1. 是一种很强的约束，更好地保证程序的正确语义不被破坏。
2. 编译器可以在编译期对constexpr的代码进行非常大的优化，比如将用到的constexpr表达式都直接替换成最终结果等。
3. 相比宏来说，没有额外的开销，但更安全可靠