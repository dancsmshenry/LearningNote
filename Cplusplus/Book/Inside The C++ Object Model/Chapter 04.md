# 第四章 Funciton 语意学

## 4.1 Member 的各种调用方式

- Nonstatic Member Functions（非静态成员函数）

  - 要和 nonmember function由相同的效率
  - 编译器内部的转化动作：
    - 改写函数原型，以安插一个额外的参数到 member function 中，该额外参数是 this 指针
    - 将每一个”对 nonstatic data member 的存取操作“改为经由 this 指针来存取
    - 将 member function 重新写成一个外部函数，将函数名称经过” mangling “处理，使它在程序中成为独一无二的语汇
  - 名称的特殊化处理：
    - 一般，member的名称钱买你会加上class名称，形成独一无二的命名

- Virtual Member Functions（虚拟成员函数）

  - ```cpp
    ptr -> normalize();//源代码，normalize为一个虚函数
    (* ptr -> vptr[1])(ptr);//会被转化为这样
    ```

  - tips:每一个类只有一个虚函数表

  - vptr表示由编译器产生的指针，指向virtual table

  - 1 是virtual table slot的索引值，关联到 normalize() 函数

  - 第二个 ptr 表示 this 指针

- Static Member Functions （静态成员函数）

  - ```cpp
    obj.normalize();//都是静态函数
    ptr->normalize();
    //都会被转化为下列代码
    normalize_7Point3dSFv();
    normalize_7Point3dSFv();
    ```

  - 一个思路：其实，如果对象的函数没有涉及到对象的数据的处理更改的话，是可以不通过对象来调用函数

  - 静态成员函数的特性：

    - 不能直接存取 class 中的 nonstatic members
    - 不能够被声明为 const，volatile 或 virtual
    - 不需要经由class 才被调用