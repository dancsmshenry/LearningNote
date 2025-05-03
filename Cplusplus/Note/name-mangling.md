# 背景

- C++函数重载底层原理是基于编译器的 `name mangling` 机制，即给函数重命名
- 编译器需要为C++中的所有函数，在符号表中生成唯一的标识符，来区分不同的函数。而对于同名不同参的函数，编译器在进行`name mangling`操作时，会依赖于函数名和其参数类型生成唯一标识符，来支持函数重载

- **注意**：`name mangling` 操作后得到的函数标识符与返回值类型是无关的，因此函数重载与返回值类型无关
  - PS：函数的重载不能用返回值做以区别







# 类成员函数重载

- 为什么有些类函数的函数重载返回值可以有所不同？

  - ```cpp
    class Number { 
    public:
      Number(int val=0):val_{0} {};
    
      int       val()      {return val_;}
      int val() const      {return val_;}
    private:
      int val_{0};
    };
    ```

- 因为对于类成员函数，编译的时候会在第一个参数前插入一个this指针，将成员函数转换为非成员函数

- 同时函数的名字经过了`name mangling`的转换一个后会变名，即后面得到的函数名只与一开始的函数名和函数参数类型有关

- 而这里，后面加上const后表示传入的this指针便是const的了，所以这里的函数重载仍然是依赖于参数类型的不同

  - ```cpp
    // _ZN6Number3valEv 是 val 经过 name mangling 后的唯一标识符
     _ZN6Number3valEv(Number* this);
     _ZNK6Number3valEv(const Number* this);
    ```







# 为什么c不支持函数重载

- 因为c的`name mangling`只依赖于函数名，与函数参数类型无关







# 总结

- 函数的重载只依赖于函数名及其参数类型，与返回值类型无关





# 参考

- https://mp.weixin.qq.com/s?__biz=MzkyMjIxMzIxNA==&mid=2247485446&idx=1&sn=ddfa5f808fc229e854f4b0512c78b28c&scene=19#wechat_redirect