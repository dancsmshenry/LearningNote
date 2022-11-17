# decltype

- ```cpp
  map<string, float> coll;
  map<string, float>::value_type elem;//cpp11之前的写法
  decltype(coll)::value_type elem;//cpp11之后的写法，decltype可以自动推导出类型
  //defines a type equivalent to the type of an expression
  ```

- 作用一：

  - ```cpp
    //used to declare return types
    template<typename T1, typename T2>
    decltype(x + y) add(T1 x, T2 y);
    auto add(T1 x, T2 y);//等价于这个
    ```

- 作用二：

  - ```cpp
    //in metaprogramming
    template<typename T>
    void test(T obj){
        typedef typename decltype(obj)::iterator iType;
        //等价于typedef typename T::itreator iType;
        //模板只是半成品，编译通过不代表使用的时候也会通过
    }
    
    test(complex<int>());//编译失败，因为复数是没有迭代器的
    ```

- 作用三：

  - ```cpp
    //used to pass the type of a lambda
    auto cmp = [](const Person& p1, const Person& p2){
        return p1.lastname() < p2.lastname();
    }
    
    std::set<Person,decltype(cmp)> coll(cmp);
    ```

