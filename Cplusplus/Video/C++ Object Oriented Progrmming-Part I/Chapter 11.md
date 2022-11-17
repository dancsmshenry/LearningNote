# 组合与继承

类与类之间的关系：

- composition（复合），表示has-a
  - 在stl源码里面，queue的底层大多数都是套用deque来实现的，即queue中有一个deque
  - queue的很多功能都是通过调用deque的函数来实现的
  - 构造函数是由内而外的，先构造里面的component，再构造外面的container
  - 析构函数是由外而内的，先析构外面的container，再析构里面的component
- delegation（委托）
  - 对象里面维护一个指针，指向另一个对象
  - 和复合的区别是，复合里面是真的有这个对象，但是委托指针拥有这个对象的指针而已
  - 不过设计指针，就一定要注意深拷贝和浅拷贝的关系
  - copy on write，即多个指针指向同一个目标，如果有一个指针要修改其指向的对象，就单独拎一个出来进行修改
- inheritance（继承），表示is-a
  - 涉及三种继承：public，private，protected
  - 构造函数是由内而外的，先构造里面的base，再构造外面的derived
  - 析构函数是由外而内的，先析构外面的derived，再析构里面的base