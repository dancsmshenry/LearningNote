# 关于Dynamic Binding I

- 通过对象直接调用都不是多态！
- 通过汇编语言发现多态是如何实现的



# 关于Dynamic Binding II

- 浅谈const

  - 当成员函数的const和non-const版本同时存在时

    - const object只会（只能）调用const版本
    - non-const object 只会（只能）调用non-const 版本

  - |                                               | const object(数据不得变动) | non-const object(数据可变动) |
    | --------------------------------------------- | -------------------------- | ---------------------------- |
    | const member functions(保证不修改成员数据)    | ok（可以调用）             | ok（可以调用）               |
    | non-const member function(不保证成员数据不变) | no（不可以调用）           | ok（可以调用）               |

  - 再次强掉：const是可以作为函数的关键字的，用于区分函数

  - 所以应该培养大气正确的编程习惯，即如果函数不会修改对象的数据的话，就一定要加上const