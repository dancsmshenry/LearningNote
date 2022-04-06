- auto&&以及模板函数里面的T&&都是万能引用

- 万能引用只有在模板函数里，参数是左值还是右值无法确定的时候，才是不可替代的

- 如果只是move变量而没有左值接收它的话，那么该变量是不会变化的

  - ```cpp
    string s1 = "sdf";
    move(s1);
    //s1的值还是sdf
    //仅仅进行的是类型擦除的动作，
    ```



- 只能说在某个特定的实现中，移动后的对象会变为空，但是cpp标准没有规定被移动后的对象为空，所以使用标准库的程序不应当依赖有这些行为的代码
  - 比如说int的move，原来的对象还是没有改变值；而string经过move之后就会变为nullptr
  - 修正：unique_ptr经过move之后变为nullptr



- 单纯的move只是一个强制类型转换罢了，所以无事发生

- 数据和所有权的移动是在某个参数为右值引用的函数中完成的（最常见的就是类似于a=move(b)会匹配到移动构造函数上）

  - 所以move真的是类型擦除，实际上发生移动是move得到的右值，触发了类对象的 operator = (T&& a)函数的时候，才会有数据和所有权的转移

- 所以std::move的变更所有权其实是通过移动构造函数或者移动赋值函数实现的

  - ```cpp
    //查看源码
    /**
      *  @brief  Convert a value to an rvalue.
      *  @param  __t  A thing of arbitrary type.
      *  @return The parameter cast to an rvalue-reference to allow moving it.
    */
    template<typename _Tp>
    _GLIBCXX_NODISCARD
    constexpr typename std::remove_reference<_Tp>::type&& move(_Tp&& __t) noexcept {
        return static_cast<typename std::remove_reference<_Tp>::type&&>(__t);
    }
    ```

- move本身没啥意义，它的意义在于将左值转换成右值，如果转换后的值在一个构造或者赋值的context内，就会调用对应的移动构造或者赋值的函数

- 可以用引申一下为什么stl扩容的时候没有用到移动构造

- move是不会改变原来的const属性的

- 一些例子

  - `bb` 的类型是 `Foo&`，`move` 之后变为 `Foo&&`，会调用移动赋值函数；
  - `cc` 的类型是 `const Foo`，`move` 之后变为 `const Foo&&`，会调用拷贝赋值函数；
  - `bb` 的类型是 `const Foo&`，`move` 之后变为 `const Foo&&`，会调用拷贝赋值函数。



- auto&&可以绑定左值或者右值，并且保留const属性（写代码的人偷懒）
- 不是同时啊



- `for(auto x : range)`
  创建拷贝，无法修改range中的元素
- `for(auto& x : range)`
  可以修改range中的元素，但一般用以下这种

```scss
for(auto&& x : range)
```

1. `for(const auto & x : range)`
   只读range中的元素



- 无论左值引用还是右值引用，其返回的结果都是左值
- 左值引用的对象是变量，右值引用的对象是常量