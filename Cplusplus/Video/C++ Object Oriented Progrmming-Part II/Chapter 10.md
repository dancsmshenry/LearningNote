# specialization

- 模板特化

  - 泛化：模板有一个类型，要用的时候再去指定它即可
  - 特化：针对一个特殊的类型，进行特别的处理

- ```cpp
  template<class Key>//一般的泛化
  
  template<>//针对某种特定类型的特化，即如果类型是char类型的话，那么就会指定用这一串代码
  struct hash<char>{
      size_t operator()(char x) const{return x;}
  };
  ```

- 特化可以有任意版本

- 泛化又叫做全泛化，特化就又有偏特化