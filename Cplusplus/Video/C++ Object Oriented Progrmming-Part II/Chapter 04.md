# pointer-like classes

- 有关智能指针

  - 把对象放到智能指针里面，操控指针就像操控对象本身一样（因为智能指针的底层对操作符做了很多的重载）

- 有关迭代器

  - 感觉也有点像智能指针

- ```cpp
  template <class T>
  class shared_ptr{
      public:
      	T& operator*() const{
              return *px;
          }//智能指针模拟*的重载
      	
      	T* operator->() const{
              return px;
          }//智能指针模拟->的重载
      	
      	shared_ptr(T* p):px(p){}
      private:
      	T* px;
      	long* pn;
  }
  
  shared_ptr<Foo> sp(new Foo);
  Foo f(*sp);
  sp->method();
  ```

- 感觉，要让一个类像一个指针，主要就是重载好它的*运算符和->运算符