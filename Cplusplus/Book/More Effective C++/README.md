# 有关本书的一些特殊用于的扫盲

- placement new
  - 是指在特定的内存空间为准备创建的对象分配内存（而传统的new是调用operator new来分配内存）
  - 例：先分配一个空的数组（特定的内存空间），然后用new创建一个对象，指定是在这个空数组的内存上创建