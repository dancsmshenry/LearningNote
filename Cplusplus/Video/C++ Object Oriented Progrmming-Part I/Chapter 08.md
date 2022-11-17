# 堆、栈与内存管理

- String的output函数（写成成员函数）

- 栈（stack）

  - 存在于某个作用域（scope）的一块内存空间，例如当你调用函数，函数本身即会形成一个stack用来放置它所接收的参数，以及返回地址
    - 在函数本体内声明的任何变量，其所使用的内存块都取自上述stack

- 堆（heap）

  - 是指由操作系统提供的一块global内存空间，程序可动态分配（dynamic allocated）从某中获得若干区域（blocks）

- stack的生命期：离开了作用域就会消失

  - 但是static的生命会在作用域结束后仍然存在，直到整个程序结束
  - global object也是一样，作用域是整个程序

- heap的生命期：其生命在它被delete之际结束

  - 如果不delete，就会造成内存泄漏

  - ```cpp
    //可以这样创建对象的啊！！
    Complex* p = new Complex;
    ```

- new，先分配memory，再调用ctor

  - ```cpp
    Complex* pc = new Complex(1, 2);
    
    //在编译器内部会转化为
    Complex *pc;
    void* mem = operator new(sizeof(Complex));//分配内存，其中operator new调用的是malloc(n)的内存分配函数
    pc = static_cast<Complex*>(mem);//转型
    pc -> Complex::Complex(1, 2);//构造函数
    ```

- delete，先调用dtor，再释放memory

  - ```cpp
    delete pc;
    
    //在编译器内部会转化为
    Complex::~Complex(pc);//析构函数
    operator delete(pc);//释放内存，在delete的内部调用free(pc)
    ```

- 动态分配所得的内存块（memory block）

  - 对象所占用的内存：对象自己的大小，padding（结构体对齐），以及两个cookie（？，一共8个字节的cookie）

- 动态分配的array

  - 对象所占用的内存：一个记录数组长度的大小，对象自己的大小乘以长度，padding，以及两个cookie（？，一共8个字节的cookie）

- array new一定要搭配array delete

  - 如果对于数组对象，没有delete[]，就会造成只释放了第一个对象，后面的对象都没能被释放，造成内存泄漏