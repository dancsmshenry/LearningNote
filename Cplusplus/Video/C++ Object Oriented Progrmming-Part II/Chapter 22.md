# 示例

- ```cpp
  Foo* pf = new Foo;
  delete pf;//如果没有members重载，就用全局的
  
  Foo* pf = ::new Foo;
  ::delete pf;//用：：表示要使用全局的
  ```

- ```cpp
  void* Foo::operator new(size_t size){
      Foo* p = (Foo*)malloc(size);
      cout << ...;
      return p;//这是重载后的operator new(这是函数的全名)
  }
  
  void Foo::operator delete(void* pdead, size_t size){
      cout << ...;
      free(pdead);//这是重载后的operator delete(这是函数的全名)
  }
  ```

- 回归对象模型

  - 发现，如果一个对象的大小是12，那么五个对象的大小理应是60，但是实际操作的时候发现，却是64，因为这里还要多用一个变量来储存数组的大小