# Alias Template

- ```cpp
  template <typename T>
  using Vec = std::vector<T, MyAlloc<T>>;
  
  //模板化名不能用define来实现
  #define Vec<T> template<typename T> std::vector<T, MyAlloc<T>>;
  //否则就会变为这样
  Vec<int> coll;
  
  template<typename int> std::vector<int, MyAlloc<int>>;//这就变为了定义一个模板了，但却不是我们想要的那一个
  ```

- 不能对化名做全特化或偏特化

- 用模板化名实现萃取（把变量中的类型给提取出来）

  - ```cpp
    template<typename Container>
    void test_moveable(Container c){
        typedef typename iterator_traits<typename Container::iterator>::value_type Valtype;
        //先是获取容器的迭代器，再通过迭代器获取具体的值，最后通过萃取机（iterator_traits）获取该数值的类型，最后赋值给Valtype
        //这种方法可以把容器里面的对象的类型给拿出来
    }
    ```

