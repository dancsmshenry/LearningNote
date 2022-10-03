# shared_ptr

## 定义

- 遵循共享所有权的概念，即不同的 shared_ptr 对象可以与相同的指针相关联
- 在任何地方都不使用时自动删除相关指针



## 实现

- 每个 shared_ptr 对象在内部指向两个内存位置，即在栈上建立两个指针，分别指向堆上的两个内存位置
  - 指向对象的指针（存储对象）
  - 用于控制引用计数数据的指针（用于引用计数的内存，最初计数将为1；不可能是static存储）

- 如何实现引用计数
  - 当新的 shared_ptr 对象与指针关联时，则在其构造函数中，将与此指针关联的引用计数增加1
  - 即只要调用构造函数、赋值运算符、拷贝构造函数，以及调用reset()函数，拷贝的智能指针shared_ptr声明周期结束，都会影响到计数器的变化
  - 当任何 shared_ptr 对象超出作用域时，则在其析构函数中，它将关联指针的引用计数减1
  - 如果引用计数变为0，则表示没有其他 shared_ptr 对象与此内存关联，在这种情况下，它使用`delete`函数删除该内存
- 导致引用计数改变的原因：
  - 构造函数，赋值运算符，拷贝构造函数，以及调用reset()函数，拷贝的智能指针shared_ptr声明周期结束
- 因此shared_ptr修改指向的消耗，一方面要注意计数的增减，另一方面要注意对象的析构



## 语法

```cpp
#include <memory>	//	头文件

//	创建shared_ptr
//	PS：因为带有参数的 shared_ptr 构造函数是 explicit 类型的，所以不能像这样std::shared_ptr<int> p1 = new int();隐式调用它构造函数
std::shared_ptr<int> p1(new int());
std::shared_ptr<int> p2(p1);	//	两个指针指向同一个对象

//	创建新的shared_ptr对象的最佳方法是使用std :: make_shared
//	std::make_shared 一次性为int对象和用于引用计数的数据都分配了内存，而new操作符只是为int分配了内存
std::shared_ptr<int> p1 = std::make_shared<int>();	//	创建空对象


// 返回shared_ptr的引用计数
int count = p1.use_count();


//	分离原始指针
p1.reset();	//	使引用计数减一
p1.reset(new int(34));	//	指针指向新的数据，引用计数重置为1
p1 = nullptr; // 重置指针


//	shared_ptr充当普通指针，我们可以将*和->与shared_ptr对象一起使用，也可以和其他shared_ptr对象一样进行比较
*p1 = 78; // 指针的*运算
//	指针间的比较
if (p1 == p2) {
	std::cout << "p1 and p2 are pointing to same pointer\n";
}


//	三种不同的删除器
	//	使用的背景：
	//	需要添加自定义删除器的使用方式
std::shared_ptr<int> p3(new int[12]);	//	仅用于演示自定义删除器（这里的delete不能满足需求，所以需要自定义删除器或shared_ptr<int[]>）

	//	指向数组的智能指针可以使用这种形式
std::shared_ptr<int[]> p3(new int[12]);	//	正确使用方式

	//	函数作为删除器
void deleter(Sample * x) {
	std::cout << "DELETER FUNCTION CALLED" << std::endl;
	delete[] x;
}
std::shared_ptr<Sample> p3(new Sample[12], deleter);

	//	函数对象作为删除器
class Deleter {
	public:
	void operator() (Sample * x) { // 重载()运算符
		std::cout << "DELETER FUNCTION CALLED" << std::endl;
		delete[] x;
	}
};
std::shared_ptr<Sample> p3(new Sample[3], Deleter());

	//	Lambda表达式作为删除器
std::shared_ptr<Sample> p4(new Sample[3], [](Sample * x) {
	std::cout <<"DELETER FUNCTION CALLED" << std::endl;
	delete[] x;
});


//	const和shared_ptr
const shared_ptr<int> a;	//	相当于 T *const a，顶层const不能改变指针的值
shared_ptr<const int> a;	//	相当于 const T* a，底层const不能改变指针所指对象的值
```



## 优点

创建 shared_ptr 对象而不分配任何值时，它就是空的

- 普通指针不分配空间的时候相当于一个野指针，而smart point则自动指向空值

```cpp
std::shared_ptr<int> ptr3;
if (!ptr3)
    std::cout << "Yes, ptr3 is empty" << std::endl;
if (ptr3 == NULL)
    std::cout << "ptr3 is empty" << std::endl;
if (ptr3 == nullptr)
    std::cout << "ptr3 is empty" << std::endl;
```



## 缺点

与普通指针相比，shared_ptr仅提供`->` 、`*`和`==`运算符，没有`+`、`-`、`++`、`--`、`[]`等运算符

```cpp
#include <iostream>
#include <memory>

struct Sample {
    void dummyFunction() {
        std::cout << "dummyFunction" << std::endl;
    }
};

int main() {
    std::shared_ptr<Sample> ptr = std::make_shared<Sample>();

    (*ptr).dummyFunction(); // ok
    ptr->dummyFunction();   // ok

    // ptr[0]->dummyFunction(); // error
    // ptr++;  // error
    // ptr--;  // error

    std::shared_ptr<Sample> ptr2(ptr);
    if (ptr == ptr2) // ok
        std::cout << "ptr and ptr2 are equal" << std::endl;
    return 0;
}
```



使用不当导致死锁，从而出现内存泄漏

- 解决办法：使用weak_ptr防止死锁

```cpp
// 一段内存泄露的代码
struct Son;
struct Father　{
    shared_ptr<Son> son_;
};
struct Son {
    shared_ptr<Father> father_;
};
int main() {
    auto father = make_shared<Father>();
    auto son = make_shared<Son>();
    father->son_ = son;
    son->father_ = father;
  
    return 0;
}
```





## 使用细则

不要使用raw pointer构建smart pointer

- 缺点就是生命周期的错乱，可能某一方的smart pointer把资源释放了，而另一方raw pointer还觉得资源正常，从而有意想不到的error

- ```cpp
  //	会造成资源的二次释放，从而coredump
  int main() {
  	int *p = new int{10};
  	std::shared_ptr<int> ptr2{p};
  	std::cout << "count ptr2:" << ptr2.use_count() << std::endl; // 1
      {
          std::shared_ptr<int> ptr1{p};
          std::cout << "count ptr1:" << ptr1.use_count() << std::endl; // 1
      }
      //	这里的p和ptr2都是悬空指针...
  }
  
  //	同样是将raw pointer放入smart point中
  class Student {
  public:
      Student(const string &name) : name_(name) {}
      void addToGroup(vector<shared_ptr<Student>> &group) {
          group.push_back(shared_ptr<Student>(this)); //	error
      }
  
  private:
      string name_;
  };
  
  //	同样是raw pointer造成的问题
  void test() {
      std::shared_ptr<int> p(new int(13));
      int *p1 = p.get();
      int count = p.use_count(); // 1
      {
          std::shared_ptr<int> pp(p1);
          (*pp) -- ;
      }
      int ret = (*p) ++ ;
      //	此时，数据就会被删除掉了（因为在p1在{}中认为只有它自己拿到了这个数据，那么出来的时候就会把数据给销毁掉，造成的结果就是访问到未知的数据.）
  }
  ```

- 解决办法：杜绝使用raw pointer的做法；使用enable_shared_from_this解决类指针this放入smart pointer的问题

- ```cpp
  class Student: public std::enable_shared_from_this<Student> {
  public:
      Student(const string &name) : name_(name) {}
      void addToGroup(vector<shared_ptr<Student>> &group) {
          group.push_back(shared_from_this());
      }
  
  private:
      string name_;
  };
  ```



不要使用栈中的指针构建smart pointer

- shared_ptr 默认的构造函数中使用的是`delete`来删除关联的指针，所以构造的时候也必须使用`new`出来的堆空间的指针

```cpp
//	coredump
#include <memory>

int main() {
    int x = 12;
    std::shared_ptr<int> ptr(&x);
    return 0; // 当 shared_ptr 对象超出作用域调用析构函数delete指针&x时会出错
}
```

- 解决办法：使用`make_shared()<>`创建 shared_ptr 对象，而不是使用默认构造函数创建



不要随意用get()获取原始指针

- 因为如果在 shared_ptr 析构之前手动调用了`delete`函数，同样会导致悬空指针
- 不要保存sp.get()的返回值，无论是保存为裸指针还是shared_ptr都是错误的，保存为裸指针不知什么时候就会变成空悬指针，保存为shared_ptr则产生了独立指针
- 不要delete sp.get()的返回值，会导致对一块内存delete两次的错误







# unique_ptr

## 定义

- unique_ptr是C++ 11提供的用于防止内存泄漏的智能指针中的一种实现，独享被管理对象指针所有权的智能指针
  - unique_ptr对象始终是关联的原始指针的唯一所有者。我们无法复制unique_ptr对象，它只能移动（move）
  - 由于每个unique_ptr对象都是原始指针的唯一所有者，因此在其析构函数中它直接删除关联的指针（所以unique_ptr的组成就单单是一个指针）

- unique_ptr具有`->`和`*`运算符重载符，因此它可以像普通指针一样使用



## 语法

```cpp
#include <memory>

//  创建unique_ptr对象
std::unique_ptr<int> taskPtr(new int(23));
//  或者以下方法
std::unique_ptr<int> taskPtr(new std::unique_ptr<int>::element_type(23));
//  std::make_unique<>()是C++14引入的
std::unique_ptr<int> taskPtr = std::make_unique<int>(34);
//  创建空指针
std::unique_ptr<int> taskPtr;
//  因为smart pointer的构造函数时explicit，所以不能赋值构造
std::unique_ptr<int> taskPtr = new int(); // error
//  构建数组对象
std::unique_ptr<int[]> taskPtr(new int[10]);
//  或者以下方法
std::unique_ptr<int[]> taskPtr(std::make_unique<int[]>(10));


//  释放关联指针并释放原始指针的所有权，然后返回原始指针（不会delete原始指针）
std::unique_ptr<int> taskPtr(new int(55));
int *ptr = taskPtr.release();


//	想操作原始指针一样操作smart pointer
int *p1 = taskPtr.get();
if (!taskPtr || taskPtr == nullptr)
    std::cout << "ptr1 is empty" << std::endl;


//  重置指针，delete其关联的指针，重置当前指针为空
taskPtr.reset();


//  所有权的转移：unique_ptr不能复制，但是可以通过move进行移动（move后原指针变为空）
//  因此unique_ptr不能用于函数参数的值传递，只能用引用传递（但是可以作为返回值使用）
std::unique_ptr<int> taskPtr2(new int(55));
std::unique_ptr<int> taskPtr4 = std::move(taskPtr2);
//	函数返回unique_ptr
std::unique_ptr<int> func(int val) {
    std::unique_ptr<int> up(new int(val));
    return up;
}


//	指定删除器，https://blog.csdn.net/hp_cpp/article/details/103210135
```







# weak_ptr

## 背景

- shared_ptr强引用导致循环引用，最后资源泄漏

- ```cpp
  #include <iostream>
  #include <memory>
  
  using namespace std;
  
  class parent;
  class children;
   
  typedef shared_ptr<parent> parent_ptr;
  typedef shared_ptr<children> children_ptr;
   
  class parent {
  public:
      ~parent() { std::cout << "destroying parent" << std::endl; }
   
  public:
      //weak_ptr<children>  children;
      children_ptr children;
  };
   
  class children {
  public:
      ~children() { std::cout << "destroying children" << std::endl; }
   
  public:
      parent_ptr parent;
      //weak_ptr<parent>  parent;
  };
   
  void test() {
      parent_ptr father(new parent());
      children_ptr son(new children());
   
      father -> children = son;
      cout << son.use_count() << endl;
  
      son -> parent = father;
      cout << father.use_count() << endl;
  }
   
  int main() {
      std::cout << "begin test..." << std::endl;
      test();
      std::cout << "end test..." << std::endl;
      cin.get();
  }
  ```



- 强引用：当被引用的对象活着的时候，这个引用也存在
- 弱引用：当引用的对象活的时候不一定存在 。仅仅是当它存在的时候的一个引用

  - 弱引用能检测到所管理的对象是否已经被释放，从而避免访问非法内存



## 定义

- weak_ptr类型指针并不会影响所指堆内存空间的引用计数（弱引用）
  - 当weak_ptr类型指针的指向和某一shared_ptr指针相同时，weak_ptr指针并不会使所指堆内存的引用计数加1
  - 当weak_ptr指针被释放时，之前所指堆内存的引用计数也不会因此而减1
- weak_ptr**没有重载*和->运算符**，因此weak_ptr类型指针只能访问某一shared_ptr指针指向的堆内存空间，无法对其进行修改
- 弱引用的存在周期一定要比主对象的存在周期要短（否则容易存在空悬指针的情况）



## 语法

- ```cpp
  //  创建一个空的weak_ptr指针
  std::weak_ptr<int> wp1;
  
  //  用已有的指针创建
  //  若wp1为空指针，则wp2也为空指针
  //  反之，如果wp1指向某一shared_ptr指针拥有的堆内存，则wp2也指向该块存储空间（可以访问，但无所有权）
  std::weak_ptr<int> wp2(wp1);
  
  //  指向一个shared_ptr指针拥有的堆内存
  std::shared_ptr<int> sp(new int);
  std::weak_ptr<int> wp3(sp);
  //  只能由weak_ptr和shared_ptr演变而来
  
  //	可以用=赋值weak_ptr
  std::weak_ptr<int> pb4 = wp3;
  std::weak_ptr<int> pb5 = sp;
  
  //	将当前指针重置为空
  pb5.reset();
  
  //	查看当前引用对象的引用计数(weak_ptr是不计数的)
  int count = pb5.use_count();
  
  //	因为没有重载*等符号，所以如果要判断当前指针是否为空，就得用expired()（返回true表示资源不存在了，返回false表示资源依然存在）
  if (!p1.expired()) std::cout << "live!" << std::endl;
  
  //	交换两个指针的指向
  pb4.swap(pb5);
  
  //	如果当前weak_ptr已经过期，则该函数会返回一个空的shared_ptr；反之，该函数返回一个和当前weak_ptr指向相同的shared_ptr
  std::shared_ptr<int> co = pb4.lock();
  ```







# auto_ptr

## 背景

- c++早期都是raw pointer，所以希望有一个smart pointer能够自动管理资源，不用手动释放

- auto_ptr的缺点便是拷贝构造或者赋值的时候，auto_ptr会把原有的指针赋给对方，导致自身变为空指针，从而出现问题

  - 比如说在容器中，很难避免不对容器中的元素实现赋值传递，这样便会使容器中多个元素被置为空指针
  - 再或者说，auto_ptr作为值传递的时候，auto_ptr就会把值传给函数，使得本身变为空指针，然后作为函数参数的指针就会在函数的周期中消失，不仅使得auto_ptr始终是一个空指针，还使得原来的对象被销毁

- 由此引发了两种类型的指针：

  - shared_ptr（值传递的时候会创建新的指针指向原来的值，而不会使得原来的指针变为空指针）
  - unique_ptr（不能用于值传递，只能用引用传递和move）



## 用法

- ```cpp
  #include <iostream>
  #include <memory>
  
  int main() {
      //测试拷贝构造
      std::auto_ptr<int> sp1(new int(8));
      std::auto_ptr<int> sp2(sp1);
      if (sp1.get() != NULL) {
          std::cout << "sp1 is not empty." << std::endl;
      } else {
          std::cout << "sp1 is empty." << std::endl;
      }
  
      if (sp2.get() != NULL) {
          std::cout << "sp2 is not empty." << std::endl;
      } else {
          std::cout << "sp2 is empty." << std::endl;
      }
  
      //测试赋值构造
      std::auto_ptr<int> sp3(new int(8));
      std::auto_ptr<int> sp4;
      sp4 = sp3;
      if (sp3.get() != NULL) {
          std::cout << "sp3 is not empty." << std::endl;
      } else {
          std::cout << "sp3 is empty." << std::endl;
      }
  
      if (sp4.get() != NULL) {
          std::cout << "sp4 is not empty." << std::endl;
      } else {
          std::cout << "sp4 is empty." << std::endl;
      }
  
      return 0;
  }
  /**
  sp1 is empty.
  sp2 is not empty.
  sp3 is empty.
  sp4 is not empty.
  **/
  ```








# enable_shared_from_this

## 背景

- 在实际开发中，有时需要在类中返回包裹当前对象的shared_ptr指针给外部使用

- ```cpp
  #include <iostream>
  #include <memory>
  
  class A : public std::enable_shared_from_this<A> {
  public:
      A() {
          std::cout << "A constructor" << std::endl;
      }
  
      ~A() {
          std::cout << "A destructor" << std::endl;
      }
  
      std::shared_ptr<A> getSelf() {
          return shared_from_this(); // 调用该函数可以返回一个包裹A对象的shared_ptr
      }
  };
  
  int main() {
      std::shared_ptr<A> sp1(new A());
      std::shared_ptr<A> sp2 = sp1 -> getSelf();
      std::cout << "use count: " << sp1.use_count() << std::endl;
      return 0;
  }
  ```



## 缺点

共享栈对象的 this 给智能指针对象导致coredump

- ```cpp
  int main() {
      A a;
      std::shared_ptr<A> sp2 = a.getSelf();
      std::cout << "use count: " << sp2.use_count() << std::endl;
      return 0;
  } //	coredump，因为smart pointer默认对象是存储在堆上的，而这里的a是在栈上存储的
  ```



循环引用

- ```cpp
  #include <iostream>
  #include <memory>
  
  class A : public std::enable_shared_from_this<A> {
  public:
      A() {
          m_i = 9;
          //注意:
          //比较好的做法是在构造函数里面调用shared_from_this()给m_SelfPtr赋值
          //但是很遗憾不能这么做,如果写在构造函数里面程序会直接崩溃
  
          std::cout << "A constructor" << std::endl;
      }
  
      ~A() {
          m_i = 0;
          std::cout << "A destructor" << std::endl;
      }
  
      void func() {
          m_SelfPtr = shared_from_this();
      }
  
  public:
      int                 m_i;
      std::shared_ptr<A>  m_SelfPtr;
  
  };
  
  int main() {
      {
          std::shared_ptr<A> spa(new A());
          spa->func();
      }
      // 这里出界的时候，spa指向的对象的引用计数由2变为1，导致的情况就是A的引用计数是因为A里面有一个指针指向自身，而里面指针要销毁就需要把A给销毁，造成了死锁
  
      return 0;
  }
  ```





# 八股

## 智能指针的大小

- ```cpp
  #include <iostream>
  #include <memory>
  
  int main() {
    std::cout << "size of shared_ptr：" <<  sizeof(std::shared_ptr<int>) << std::endl;
    std::cout << "size of unique_ptr：" <<  sizeof(std::unique_ptr<int>) << std::endl;
    std::cout << "size of weak_ptr：" <<  sizeof(std::weak_ptr<int>) << std::endl;
    std::cout << "size of auto_ptr：" <<  sizeof(std::auto_ptr<int>) << std::endl;
  }
  /*
  size of shared_ptr：16
  size of unique_ptr：8
  size of weak_ptr：16
  size of auto_ptr：8
  */
  ```



## 手写shared_ptr

- ```cpp
  template <typename T>
  class Shared_mptr {
  public:
      //空类构造，count，ptr均置空
      Shared_mptr() : count(0), ptr_((T *)0) {}
      //赋值构造，count返回int指针，必须new int，ptr指向值
      Shared_mptr(T *p) : count(new int(1)), ptr_(p) {}
      //拷贝构造，注意是&引用，此处注意的一点是，count需要+1
      Shared_mptr(Shared_mptr<T> &other) : count(&(++*other.count)), ptr_(other.ptr_) {}
      //重载->返回T*类型
      T *operator->() { return ptr_; }
      //重载*返回T&引用
      T &operator*() { return *ptr_; }
      //重载=，此处需要将源计数减一，并判断是否需要顺便析构源，然后将thiscount+1，注意最后返回*this
      Shared_mptr<T> &operator=(Shared_mptr<T> &other) {
          if (this == &other)
              return *this;
          ++*other.count;
          if (this->ptr_ && --*this->count == 0) {
              delete ptr_;
              delete count;
              cout << "delete from =" << endl;
          }
          this->count = other.count;
          this->ptr_ = other.ptr_;
          return *this;
      }
      //析构，当ptr_存在且在此次析构后count==0，真正析构资源
      ~Shared_mptr() {
          if (ptr_ && --*count == 0) {
              delete ptr_;
              delete count;
              cout << "delete from ~" << endl;
          }
      }
      //返回count
      int getRef() {
          return *count;
      }
  
  private:
      int *count; //注意此处是count*，因为计数其实是同一个count，大家都以指针来操作；
      T *ptr_;
  };
  ```



## 手写线程安全的shared_ptr



## 手写unique_ptr

- ```cpp
  template <typename T>
  class UniquePtr {
  public:
      //	构造函数
      UniquePtr(T *ptr = nullptr): m_pResource(ptr){};
      //	析构函数
      ~UniquePtr() {
          del();
      }
      //	先删除源对象，而后复制
      void reset(T *pResource) {
          del();
          m_pResource = pResource;
      }
      //	交给
      T* release() {
          T *tmp = m_pResource;
          m_pResource = nullptr;
          return tmp;
      }
  
      T* get() {
          return m_pResource;
      }
  
      operator bool() const {
          return m_pResource != nullptr;
      }
  
      T *operator->() { return m_pResource; }
      T &operator*() { return *m_pResource; }
  
  private:
      void del() {
          if (m_pResource == nullptr) return;
          delete m_pResource;
          m_pResource = nullptr;
      }
  
      UniquePtr(UniquePtr<T> &other) = delete;
      UniquePtr &operator=(const UniquePtr &) = delete;
  
      T *m_pResource;
  };
  ```



## unique_ptr和shared_ptr的转化

- unique_ptr是可以转换为shared_ptr的，因为unique_ptr的语义是唯一拥有ownership，那只要对他执行move操作就能把ownership转移出去给shared_ptr

  - ```cpp
    std::unique_ptr<Widget> a = std::make_unique<Widget>();
    std::shared_ptr<Widget> b = std::move(a);
    ```



- shared_ptr是不可以转化为unique_ptr的，因为shared_ptr的对象会被很多人拥有，不好直接转为unique_ptr





# reference

- https://zhuanlan.zhihu.com/p/150555165
- https://www.zhihu.com/question/319277442/answer/1517987598
- https://zhuanlan.zhihu.com/p/532215950
- https://zhuanlan.zhihu.com/p/416289479（shared_ptr是否线程安全）