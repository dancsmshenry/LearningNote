```C++
class A {
public:
    class B;
    std::shared_ptr<B> b1; // normal
    // B b2; // error, because A should know the size of B
    B* b3; // normal, because size of a pointer is exactly
};
```

前置声明，更多的是为了声明这个变量是一个实体，是一个 class

但不能像上面一样将它为一个成员变量，这样当构建 A 时，就会构建不出来（因为此时并不知道它的实际大小和组成）