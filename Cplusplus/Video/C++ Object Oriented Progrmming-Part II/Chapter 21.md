# Operator new，Operator delete

- 重载operator new（用来分配内存空间，效果上应该等价于malloc），重载operator delete（用来删除掉空间，效果上应该等价于free）
  - 重载全局的这个函数
  - 重载成员的这个函数
  - 为什么要接管这些函数：做内存池