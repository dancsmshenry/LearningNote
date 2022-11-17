# 操作符重载与临时对象

- operator overloading(操作符重载-1，成员函数) this

  - 任何非静态的成员函数都有一个隐藏的this指针

- return by reference语法分析

  - 传递者不需要知道接收者是以reference形式接收（特别是返回引用，在链式编程上特别好使）

- temp object（临时对象）

  - 需要以值返回，但是又不能返回local object的时候，就用temp object

  - ```cpp
    inline complex operator + (const complex& x, const complex& y){
        return complex(real(x) + real(y), imag(x) + imag(y));
    }
    ```

  - 没有名字的对象就是临时对象，它存在于完整的表达式的生存期间。也就是说，当表达式计算结束后就会被释放（即不会像临时对象一样）

  - 返回临时对象的话要以值传递，不能是引用传递

- 接下来就是无聊的操作符重载：+，-，==

- 不要把<<写作成员函数，要变为全局函数

  - 注意，传入ostream的cout的时候，不要把它设为const，因为cout的状态一直都在改变