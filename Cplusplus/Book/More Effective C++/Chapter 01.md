# 条款1：指针与引用的区别

- 区别：
  - 指针用操作符“*”和“->”，引用使用操作符“. ”
  - 任何情况下都不能使用指向空值的引用，引用应该被初始化
  - 如果你使用一个变量并让它指向一个对象，但是该变量在某些时候也可能不指向任何对象，这时你应该把变量声明为**指针**，因为这样你可以赋空值给该变；相反，如果变量肯定指向一个对象，例如你的设计不允许变量为空，这时你就可以把变量声明为**引用**
    - 总结为：指针可以被重新赋值以指向另一个不同的对象，而引用则总是指向在初始化时被指定的对象，以后不能改变
  - 不存在指向空值的引用。这意味着使用引用的代码效率比使用指针的要高，因为在使用引用之前不需要测试它的合法性
- 使用指针的情况：
  - 存在不指向任何对象的时候（在这种情况下，指针可设为空）
  - 需要能够在不同的时刻指向不同的对象（在这种情况下，你能改变指针的指向）
- 使用引用的情况：
  - 总是指向一个对象，并且一旦指向一个对象后就不会改变指向
  - 重载某个操作符的时候

<br/>

<br/>

# 条款2：尽量使用c++风格的类型转换

- 原因：
  - c风格的强制转换在代码上难以识别
    - 在语法上，类型转换由圆括号和标识符组成，而这些可以用在 C++ 中的任何地方
  - 过于粗鲁，允许你在任何类型之间进行转换
- 所以，最好使用以下四种cpp的强制转换类型
  - static_cast
    - 不能去掉 const 
    - 只能转相同类型的类型
  - const_cast
    - 用于类型转换掉表达式的 const 或 volatileness 属性
  - dynamic_cast
    - 被用于安全地沿着类的继承关系向下进行类型转换
    - 把指向基类的指针或引用转换成指向其派生类或其兄弟类的指针或引用，而且你能知道转换是否成功
    - 失败的转换将返回空指针（当对指针进行类型转换时）或者抛出异常（当对引用进行类型转换时）
    - 在浏览继承层次上是有限制的，不能被用于缺乏虚函数的类型上，也不能用来去掉constness
  - reinterpret_cast
    - 相当于是一个强制转换的过程
    - 最普遍的用途就是在函数指针类型之间进行转换
    - 而转换函数指针的代码时不可移植的，所以应该避免转换函数指针类型

<br/>

<br/>

# 条款3：不要对数组使用多态

- 比如说B类是继承A类的，写了一个函数是操作A类的，但此时传入了一个B类的数据到这个函数，就会出现问题
  - 因为数组的操作实际上是指针在移动，操作A类的函数，指针移动的位移大小是A类对象的大小，而明显B类的大小是大于A类的
- 这里探回数组的本质
  - array[i]其实只是一个指针算法的缩写，所代表的是*（array），即array是一个指向数组起始地址的指针，其中每个元素的地址之间的间隔都是一个在数组里的对象的大小
  - 而编译器为了建立正确遍历数组的执行代码，它必须能够确定数组中对象的大小
  - 很明显，如果我实际传进来的数组元素的大小比这个大，就会出现错误
- 因此：通过一个基类指针来删除一个含有派生类对象的数组，结果是不对的

<br/>

<br/>

# 条款4：避免无用的缺省构造函数

- 缺省构造函数（指没有参数的构造函数）
- 对于很多对象来说，不利用外部数据进行完全的初始化是不合理的。比如一个没有输入姓名的地址簿对象，就没有任何意义
- 如果没有缺省构造函数
  - 就不能直接构造该对象的数组（要构建的话需要逐个逐个的传参构建），也不能通过指针来构造该对象的数组（需要的话需要创建指针数组；不过有两个缺点：第一：必须删除数组里每个指针所指向的对象，否则会发生内存泄漏；第二：增加了内存分配量，因为还要预留空间来存指针）