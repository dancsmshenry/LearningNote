# 关于new、delete

- 参考 I 的chapter08
  - new：先分配memory，再调用ctor
  - delete：先调用dtor，再分配memory
  - 动态分配所得的内存块
  - array new一定要搭配array delete
- class可以重载new和delete，用来设计内存池