#### Variadic templates VII & Cpp keywords

代码七（递归+复合）

- ```cpp
  template<typename... Values> class tup;
  template<> class tup<> {};
  
  template<typename Head, typename... Tail>
  class tup<Head, Tail...>{
      typedef tup<Tail...> composited;
      protected:
      	composited m_tail;
      	Head m_head;
      public:
      	tup(){}
      	tup(Head v, Tail... vtail):m_tail(vtail...), m_head(v){}
      	Head head(){return m_head;}
      	composited& tail(){return m_tail;}
  };
  ```
