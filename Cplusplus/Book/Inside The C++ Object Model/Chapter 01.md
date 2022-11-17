# 第一章 关于对象

## 1.1 对象模式

- 加上封装后的布局成本
  - c++在布局以及存取时间上的主要额外负担是由virtual引起的
    - virtual function机制，用以执行一个有效率的”执行期绑定“
    - virtual base class机制，用以实现”多次出现在继承体系中的base class，有一个单一而被共享的实例“
- 在c++中，有两种class data members：static和nonstatic，以及三种class member functions：static，nonstatic和virtual
- 简单对象模型
  - 对象里有一个point table，指针指向对象的data和function
- 表格对象模型
  - 对象里还是一个point table，但是里面只有两个指针，一个指向member data table，另一个指向 function member table
  - member data table里面存放的就是具体的数据，function member table就存放函数地址
- C++对象模型
  - nonstatic data members被配置于每一个对象里面
  - static data members存放在个别的对象之外
  - member function也存放在个别的对象之外
  - 而virtual function则有以下两步：
    - 每一个class产生一堆指向virtual function的指针，存放在表格之中，这个表格称为virtual table（vtbl）
    - 每一个class object被安插一个指针，指向相关的virtual table，通常称为vptr
    - vptr的设定和重置都由class的构造函数，拷贝函数，赋值运算符决定
    - 每个class所关联的type_info也由vtbl决定，通常被放在表格的第一位
  - 在virtual 继承中，无论派生多少次，base class只有一个
- 对象模型如何影响程序
  - 这里后续肯定要放一张图片在这里的







## 1.2 关键词所带来的差异

- 







## 1.3 对象的差异

- cpp支持三种程序设计范式
  - 程序模型（和C一样，以面向过程为主）
  - 抽象数据模型（所谓的抽象是和一组表达式（接口）一起提供的）
  - 面向对象模型（类与类之间有了关系，出现了继承复合等关系）
- cpp通过以下方法实现多态
  - 经由一组隐式的转化操作，例如把一个derviced class指针转化为一个指向其public base type的指针
  - 经由