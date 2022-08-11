# 定义

- 运行阶段类型识别（Run-Time Type Identification）

- 通过运行时类型信息程序能够使用基类的指针或引用来检查这些指针或引用所指的对象的实际派生类
- 面向对象的语言多少都支持
- 为程序在运行阶段确定对象的类型的一种方法



# 背景

- 假设有一个类层次结构，其中的类都是从一个基类派生而来的，则可以让基类指针指向其中任何一个类的对象。



- 有时候我们会想要知道指针具体指向的是哪个类的对象。因为：
  - 可能希望调用类方法的正确版本，而有时候派生对象可能包含不是继承而来的方法，此时，只有某些类的对象可以使用这种方法。
  - 也可能是出于调试目的，想跟踪生成的对象的类型



# 实现

### dynamic_cast

- 如果可能的话，`dynamic_cast`运算符将使用一个指向基类的指针来生成一个指向派生类的指针；否则，该运算符返回0（空指针）
- 可以理解为，得到一个基类指针，然后循环遍历它的派生类指针，一个一个试



### typeid

- 运算符返回一个指出对象的类型的值

- `typeid`运算符能够用于确定两个对象是否为同种类型。它与sizeof有些相像，可以接受两种参数：

  - 类名
  - 结果为对象的表达式

- 返回一个对`type_info`**对象的引用**，其中，`type_info`是在头文件`typeinfo`中定义的一个类，这个类重载了`==`和`!=`运算符，以便可以用于对类型进行比较

  - ```cpp
    // 判断pg指向的是否是ClassName类的对象
    typeid(ClassName) == typeid(*pg);
    //	返回两个类是不是同一个类型
    ```

  - 如果pg是一个空指针的话，就会出现异常



- 其实，`typeid`运算符就是指出或判断具体的类型，而`dynamic_cast`运算符主要用于判断是否能够转换，并进行类型转换（指针或引用）。





### type_info

- 存储了有关特定类型的信息