# Range - based for statement

- ```cpp
  for (decl : coll){
      statement;
  }
  
  vector<doublie> vec;
  for (auto elem: vec){
      cout << elem << endl;//这个只是拷贝
  }
  
  for (auto& elem: vec){
      elem *= 3;//这个是实体
  }
  ```

- 关联式容器（hash set等）不能通过迭代器来修改元素，序列式是可以的

- ```cpp
  class C{
      public:
      	explict C(const string& s);
  };
  
  vector<string> vs;
  for (const C& elem:vs){
      cout << elem << endl;//这里会出错：因为explicit不允许将string隐式转换为C
  }
  ```

