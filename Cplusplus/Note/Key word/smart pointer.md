# Shared_ptr

## 概念

- 在任何地方都不使用时自动删除相关指针

- 它遵循共享所有权的概念，即不同的 shared_ptr 对象可以与相同的指针相关联（使用引用计数机制实现)



- 每个 shared_ptr 对象在内部指向两个内存位置，即在栈上建立两个指针，分别指向堆上的两个内存位置
  - 指向对象的指针（存储对象）
  - 用于控制引用计数数据的指针（用于引用计数的内存，管理附加此内存的 shared_ptr 对象的计数，最初计数将为1）



- 如何实现引用计数
  - 当新的 shared_ptr 对象与指针关联时，则在其构造函数中，将与此指针关联的引用计数增加1
  - 即只要调用构造函数、赋值运算符、拷贝构造函数，以及调用reset()函数，拷贝的智能指针shared_ptr声明周期结束，都会影响到计数器的变化
  - 当任何 shared_ptr 对象超出作用域时，则在其析构函数中，它将关联指针的引用计数减1
  - 如果引用计数变为0，则表示没有其他 shared_ptr 对象与此内存关联，在这种情况下，它使用`delete`函数删除该内存
  - 所以绝不可能是static存储
- 引发引用计数改变的原因：
  - 构造函数，赋值运算符，拷贝构造函数，以及调用reset()函数，拷贝的智能指针shared_ptr声明周期结束



- shared_ptr修改指向的时候，分析一下过程，性能开销如何？

  - 这个很多人咋一看会以为，这个修改指向的操作只是修改shared_ptr内部的指针而已。因为指针的修改开销并不大，故而感觉这个操作不会有什么性能问题

  - 其实还包括旧计数的减法和新计数的加法

  - 有的同学可能会说到这，但是会忘记，在旧计数减成0的时候，要对原先执行的堆对象做析构

  - 而这个析构可能会成为主要的开销来源。当然仅仅是可能。和具体存储的对象的析构成本相关



- shared_ptr是否为线程安全
  - https://zhuanlan.zhihu.com/p/416289479





## 用法

### 创建shared_ptr

- 因为带有参数的 shared_ptr 构造函数是 explicit 类型的，所以不能像这样`std::shared_ptr<int> p1 = new int();`隐式调用它构造函数
- 创建新的shared_ptr对象的最佳方法是使用**std :: make_shared**

  - **std::make_shared** 一次性为`int`对象和用于引用计数的数据都分配了内存，而`new`操作符只是为`int`分配了内存

```cpp
#include <memory>//头文件
std::shared_ptr<int> p1(new int());

std::shared_ptr<int> p2(p1);//两个指针指向同一个对象

std::shared_ptr<int> p1 = std::make_shared<int>();//创建空对象
```



### 返回shared_ptr的引用计数

```cpp
p1.use_count();
```



### 分离关联的原始指针

```cpp
p1.reset();//不带参数的reset()，使得引用计数减一

p1.reset(new int(34));//它将在内部指向新指针，因此其引用计数将再次变为1

p1 = nullptr;//重置指针
```



### 重载符号

```cpp
//shared_ptr充当普通指针，我们可以将`*`和`->`与 shared_ptr 对象一起使用，也可以像其他 shared_ptr 对象一样进行比较;
int main() {	
	std::shared_ptr<int> p1 = std::make_shared<int>();
	*p1 = 78;
    // 输出78
	std::cout << "p1 = " << *p1 << std::endl; 

	// 比较智能指针，p1 等于 p2
	if (p1 == p2) {
		std::cout << "p1 and p2 are pointing to same pointer\n";
	}
}
```



### 删除器 Deleter

**背景**

- 当 shared_ptr 对象超出范围时，将调用其析构函数。在其析构函数中，它将引用计数减1
- 如果引用计数的新值为0，则删除关联的原始指针
- 析构函数中删除内部原始指针，默认调用的是`delete`函数
- 有些时候在析构函数中，delete函数并不能满足我们的需求，可能还想加其他的处理

比如说，当 shared_ptr 对象指向数组

```cpp
// 需要添加自定义删除器的使用方式
std::shared_ptr<int> p3(new int[12]);   // 仅用于演示自定义删除器

// 指向数组的智能指针可以使用这种形式
std::shared_ptr<int[]> p3(new int[12]);  // 正确使用方式
```

像这样申请的数组，应该调用`delete []`释放内存

而`shared_ptr<int>`析构函数中默认`delete`并不能满足需求，可以使用`shared_ptr<int[]>`形式或者添加自定义删除器



**使用函数，函数对象，Lambda表达式作为删除器**

在上面在这种情况下，我们可以将回调函数传递给 shared_ptr 的构造函数，该构造函数将从其析构函数中调用以进行删除

```cpp
// 函数作为删除器
void deleter(Sample * x)
{
	std::cout << "DELETER FUNCTION CALLED\n";
	delete[] x;
}
std::shared_ptr<Sample> p3(new Sample[12], deleter);

class Deleter
{
	public:
	void operator() (Sample * x) {
		std::cout<<"DELETER FUNCTION CALLED\n";
		delete[] x;
	}
};

// 函数对象作为删除器
std::shared_ptr<Sample> p3(new Sample[3], Deleter());

// Lambda表达式作为删除器
std::shared_ptr<Sample> p4(new Sample[3], [](Sample * x){
	std::cout<<"DELETER FUNCTION CALLED\n";
	delete[] x;
});
```







## 优缺点

- 与普通指针相比，shared_ptr仅提供`->` 、`*`和`==`运算符，没有`+`、`-`、`++`、`--`、`[]`等运算符

```cpp
#include <iostream>
#include <memory>

struct Sample
{
    void dummyFunction()
    {
        std::cout << "dummyFunction" << std::endl;
    }
};

int main()
{
    std::shared_ptr<Sample> ptr = std::make_shared<Sample>();

    (*ptr).dummyFunction(); // 正常
    ptr->dummyFunction();   // 正常

    // ptr[0]->dummyFunction(); // 错误方式
    // ptr++;  // 错误方式
    // ptr--;  // 错误方式

    std::shared_ptr<Sample> ptr2(ptr);
    if (ptr == ptr2) // 正常
        std::cout << "ptr and ptr2 are equal" << std::endl;
    return 0;
}
```



- NULL检测

  - 当我们创建 shared_ptr 对象而不分配任何值时，它就是空的

  - 普通指针不分配空间的时候相当于一个野指针，指向垃圾空间，且无法判断指向的是否是有用数据

```cpp
std::shared_ptr<Sample> ptr3;
if (!ptr3) std::cout << "Yes, ptr3 is empty" << std::endl;
if (ptr3 == NULL) std::cout << "ptr3 is empty" << std::endl;
if (ptr3 == nullptr) std::cout << "ptr3 is empty" << std::endl;
```



## 注意事项

不要使用同一个原始指针构造 shared_ptr

- 使用多个shared_ptr指向同一个对象的正常方法是使用一个已存在的shared_ptr进行创建，而不是使用同一个原始指针进行创建（因为不会增加引用计数）

```cpp
    int *num = new int(23);
    std::shared_ptr<int> p1(num);
    
    std::shared_ptr<int> p2(p1);  // 正确使用方法
    std::shared_ptr<int> p3(num); // 不推荐

    std::cout << "p1 Reference = " << p1.use_count() << std::endl; // 输出 2
    std::cout << "p2 Reference = " << p2.use_count() << std::endl; // 输出 2
    std::cout << "p3 Reference = " << p3.use_count() << std::endl; // 输出 1
```

- 假如使用原始指针`num`创建了p1，又同样方法创建了p3，当p1超出作用域时会调用`delete`释放`num`内存，此时num成了悬空指针，当p3超出作用域再次`delete`的时候就可能会出错



不要用栈中的指针构造 shared_ptr 对象

- shared_ptr 默认的构造函数中使用的是`delete`来删除关联的指针，所以构造的时候也必须使用`new`出来的堆空间的指针。

```cpp
#include<iostream>
#include<memory>

int main()
{
   int x = 12;
   std::shared_ptr<int> ptr(&x);
   return 0; // 当 shared_ptr 对象超出作用域调用析构函数`delete` 指针`&x`时会出错
}
```

- 为了避免以上两种情形，建议使用`make_shared()<>`创建 shared_ptr 对象，而不是使用默认构造函数创建

- 另外不建议使用`get()`函数获取 shared_ptr 关联的原始指针，因为如果在 shared_ptr 析构之前手动调用了`delete`函数，同样会导致类似的错误



const和shared_ptr踩坑

- ```cpp
  const shared_ptr<T> a;// 相当于 T *const a，顶层const不能改变指针的值
  shared_ptr<const T> a;// 相当于 const T* a，底层const不能改变指针所指对象的值
  ```









# Unique_ptr

## 概念

- unique_ptr 独享所有权
  - unique_ptr对象始终是关联的原始指针的唯一所有者。我们无法复制unique_ptr对象，它只能移动（move）
  - 由于每个unique_ptr对象都是原始指针的唯一所有者，因此在其析构函数中它直接删除关联的指针，不需要任何参考计数



- unique_ptr是C++ 11提供的用于防止内存泄漏的智能指针中的一种实现，独享被管理对象指针所有权的智能指针
- unique_ptr对象包装一个原始指针，并负责其生命周期。当该对象被销毁时，会在其析构函数中删除关联的原始指针
- unique_ptr具有`->`和`*`运算符重载符，因此它可以像普通指针一样使用



- unique_ptr是不可复制的，但是可以移动...（所以它不能用于函数参数的值传递，只能用引用传递）

- ```cpp
  std::unique_ptr<Task> taskPtr3 = taskPtr2; // Compile error
  
  taskPtr = taskPtr2; //compile error
  ```



## 用法

### 创建unique_ptr

```cpp
#include <memory>

// 通过原始指针创建 unique_ptr 实例
std::unique_ptr<int> taskPtr(new int(23));

std::unique_ptr<Task> taskPtr(new std::unique_ptr<Task>::element_type(23));//或者这种

//通过 unique_ptr 访问其成员
int id = *taskPtr;

std::unique_ptr<Task> taskPtr = std::make_unique<Task>(34);//std::make_unique<>() 是C++ 14 引入的新函数

std::unique_ptr<int> ptr1;//创建空指针

std::unique_ptr<Task> taskPtr2 = new Task(); // 编译错误，不能通过赋值的方法创建对象（其构造函数是explicit）

//	拥有一组堆对象
std::unique_ptr<int[]> sp1(new int[10]);

std::unique_ptr<int[]> sp2;
sp2.reset(new int[10]);

std::unique_ptr<int[]> sp3(std::make_unique<int[]>(10));
```



### 指定删除器

- https://blog.csdn.net/hp_cpp/article/details/103210135



### 释放关联的指针

使用 `release()`将释放其关联的原始指针的所有权，并返回原始指针

这里是释放所有权，并没有delete原始指针，`reset()`会delete原始指针

```cpp
std::unique_ptr<Task> taskPtr5(new Task(55));
Task *ptr = taskPtr5.release();
```



### 获取被管理对象的指针

使用`get()`函数获取管理对象的指针

```cpp
Task *p1 = taskPtr.get();
```



### 重置指针

在 unique_ptr 对象上调用`reset()`函数将重置它，即它将释放delete关联的原始指针并使unique_ptr 对象为空。

```cpp
taskPtr.reset();
```



### 检查unique_ptr是否为空

有两种方法可以检查 unique_ptr 对象是否为空或者是否有与之关联的原始指针

```cpp
if(!ptr1) std::cout<<"ptr1 is empty"<<std::endl;
if(ptr1 == nullptr) std::cout<<"ptr1 is empty"<<std::endl;
```



### 转移unique_ptr所有权

我们无法复制 unique_ptr 对象，但我们可以转移它们

这意味着 unique_ptr 对象可以将关联的原始指针的所有权转移到另一个 unique_ptr 对象

```cpp
// 通过原始指针创建 taskPtr2
std::unique_ptr<Task> taskPtr2(new Task(55));
// 把taskPtr2中关联指针的所有权转移给taskPtr4
std::unique_ptr<Task> taskPtr4 = std::move(taskPtr2);
// 现在taskPtr2关联的指针为空
if (taskPtr2 == nullptr)
    std::cout << "taskPtr2 is  empty" << std::endl;

// taskPtr2关联指针的所有权现在转移到了taskPtr4中
if (taskPtr4 != nullptr)
    std::cout << "taskPtr4 is not empty" << std::endl;

// 会输出55
std::cout << taskPtr4->mId << std::endl;
```



- 再或者函数值返回一个unique_ptr指针，或者move一个指针

- ```cpp
  #include <memory>
  
  //	函数返回指针
  std::unique_ptr<int> func(int val)
  {
      std::unique_ptr<int> up(new int(val));
      return up;
  }
  
  int main()
  {
      std::unique_ptr<int> sp4 = func(123);
      
      //	move指针
      std::unique_ptr<int> sp1(std::make_unique<int>(123));
  
      std::unique_ptr<int> sp2(std::move(sp1));
  
      std::unique_ptr<int> sp3;
      sp3 = std::move(sp2);
  }
  ```

- 





### 总结

new出来的对象是位于堆内存上的，必须调用delete才能释放其内存

unique_ptr 是一个装指针的容器，且拥有关联指针的唯一所有权

作为普通变量使用时系统分配对象到栈内存上，超出作用域时会自动析构

unique_ptr对象的析构函数中会delete其关联指针，这样就相当于替我们执行了delete堆内存上的对象

| 成员函数  | 作用                                                         |
| --------- | ------------------------------------------------------------ |
| reset()   | 重置unique_ptr为空，delete其关联的指针。                     |
| release() | 不delete关联指针，并返回关联指针。释放关联指针的所有权，unique_ptr为空。 |
| get()     | 仅仅返回关联指针                                             |







# Weak_ptr

### 背景

- 下述代码因为引用计数都不为0，导致循环引用，最后资源就泄露了，解决办法：弱引用

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
      ~parent() { std::cout << "destroying parent\n"; }
   
  public:
      //weak_ptr<children>  children;
      children_ptr children;
  };
   
  class children {
  public:
      ~children() { std::cout << "destroying children\n"; }
   
  public:
      parent_ptr parent;
      //weak_ptr<parent>  parent;
  };
   
  void test() {
      parent_ptr father(new parent());
      children_ptr son(new children);
   
      father->children = son;
      cout << son.use_count() << endl;
   
   
      son->parent = father;
      cout << father.use_count() << endl;
  }
   
  void main() {
      std::cout << "begin test...\n";
      test();
      std::cout << "end test.\n";
      cin.get();
  }
  ```

- 强引用：当被引用的对象活着的时候，这个引用也存在

- 弱引用：当引用的对象活的时候不一定存在 。仅仅是当它存在的时候的一个引用

  - 弱引用能检测到所管理的对象是否已经被释放，从而避免访问非法内存



### 概念

- weak_ptr类型指针并不会影响所指堆内存空间的引用计数
  - 当weak_ptr类型指针的指向和某一shared_ptr指针相同时，weak_ptr指针并不会使所指堆内存的引用计数加1
  - 当weak_ptr指针被释放时，之前所指堆内存的引用计数也不会因此而减1
- weak_ptr<T>模板类没有重载*和->运算符，因此weak_ptr类型指针只能访问某一shared_ptr指针指向的堆内存空间，无法对其进行修改
- 弱引用的存在周期一定要比主对象的存在周期要短（否则容易存在空悬指针的情况）



### 用法

- ```cpp
  // 创建一个空的weak_ptr指针
  std::weak_ptr<int> wp1;
  
  // 用已有的指针创建
  std::weak_ptr<int> wp2(wp1);
  // 若wp1为空指针，则wp2也为空指针
  // 反之，如果wp1指向某一shared_ptr指针拥有的堆内存，则wp2也指向该块存储空间（可以访问，但无所有权）
  
  // 指向一个shared_ptr指针拥有的堆内存
  std::shared_ptr<int> sp(new int);
  std::weak_ptr<int> wp3(sp);
  
  // 总结：只能由weak_ptr和shared_ptr演变而来
  ```

- | 成员方法      | 功能                                                         |
  | ------------- | ------------------------------------------------------------ |
  | `operator=()` | 重载`=`赋值运算符，`weak_ptr`指针可以直接被`weak_ptr`或者`shared_ptr`类型指针赋值。 |
  | `swap(x)`     | 其中`x`表示一个同类型的`weak_ptr`类型指针，该函数可以互换2个共同类型`weak_ptr`指针的内容。 |
  | `reset()`     | 将当前`weak_ptr`指针置为空指针。                             |
  | `use_count()` | 查看指向和当前`weak_ptr`指针相同的`shared_ptr`指针的数量。   |
  | `expired()`   | 判断当前`weak_ptr`指针是否过期（指针为空，或者指向的堆内存已经被释放，返回true表示资源不存在了，返回false表示资源依然存在） |
  | `lock()`      | 如果当前`weak_ptr`已经过期，则该函数会返回一个空的`shared_ptr`指针；反之，该函数返回一个和当前`weak_ptr`指针指向相同的`shared_ptr`指针。`std::shared_ptr<TcpConnection> conn = tmpConn_.lock();`如果过期了，则conn就是一个空指针，否则就不是空指针 |

- 因为没有重载*或->等符号，所以不能用当作指针的方式`if (!ptr)`去判断是否为空指针，就必须用expitrd()







# Auto_ptr

### 背景

- ```cpp
  #include <iostream>
  #include <memory>
  
  int main()
  {
    //测试拷贝构造
    std::auto_ptr<int> sp1(new int(8));
    std::auto_ptr<int> sp2(sp1);
    if (sp1.get() != NULL)
    {
      std::cout << "sp1 is not empty." << std::endl;
    }
    else
    {
      std::cout << "sp1 is empty." << std::endl;
    }
  
    if (sp2.get() != NULL)
    {
      std::cout << "sp2 is not empty." << std::endl;
    }
    else
    {
      std::cout << "sp2 is empty." << std::endl;
    }
  
    //测试赋值构造
    std::auto_ptr<int> sp3(new int(8));
    std::auto_ptr<int> sp4;
    sp4 = sp3;
    if (sp3.get() != NULL)
    {
      std::cout << "sp3 is not empty." << std::endl;
    }
    else
    {
      std::cout << "sp3 is empty." << std::endl;
    }
  
    if (sp4.get() != NULL)
    {
      std::cout << "sp4 is not empty." << std::endl;
    }
    else
    {
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

- auto_ptr的缺点便是拷贝构造或者赋值的时候，auto_ptr会把原有的指针赋给对方，导致自身变为空指针，从而出现问题

  - 比如说在容器中，很难避免不对容器中的元素实现赋值传递，这样便会使容器中多个元素被置为空指针
  - 再或者说，auto_ptr作为值传递的时候，auto_ptr就会把值传给函数，使得本身变为空指针，然后作为函数参数的指针就会在函数的周期中消失，不仅使得auto_ptr始终是一个空指针，还使得原来的对象被销毁

- 由此引发了两种类型的指针：

  - shared_ptr（值传递的时候会创建新的指针指向原来的值，而不会使得原来的指针变为空指针）
  - unique_ptr（不能用于值传递，只能用引用传递和move）






# enable_shared_from_this

### 背景

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
      std::shared_ptr<A> sp2 = sp1->getSelf();
      std::cout << "use count: " << sp1.use_count() << std::endl;
      return 0;
  }
  ```



### 陷阱

- 不应该共享栈对象的 this 给智能指针对象

- ```cpp
  int main(){
      A a;
      std::shared_ptr<A> sp2 = a.getSelf();
      std::cout << "use count: " << sp2.use_count() << std::endl;
      return 0;
  }
  //	这里会崩溃，因为smart pointer默认对象是存储在堆上的，而这里的a是在栈上存储的
  ```



- 小心循环引用

- ```cpp
  #include <iostream>
  #include <memory>
  
  class A : public std::enable_shared_from_this<A>
  {
  public:
      A()
      {
          m_i = 9;
          //注意:
          //比较好的做法是在构造函数里面调用shared_from_this()给m_SelfPtr赋值
          //但是很遗憾不能这么做,如果写在构造函数里面程序会直接崩溃
  
          std::cout << "A constructor" << std::endl;
      }
  
      ~A()
      {
          m_i = 0;
  
          std::cout << "A destructor" << std::endl;
      }
  
      void func()
      {
          m_SelfPtr = shared_from_this();
      }
  
  public:
      int                 m_i;
      std::shared_ptr<A>  m_SelfPtr;
  
  };
  
  int main()
  {
      {
          std::shared_ptr<A> spa(new A());
          spa->func();
      }
      // 这里出界的时候，spa指向的对象的引用计数由2变为1，导致的情况就是A的引用计数是因为A里面有一个指针指向自身，而里面指针要销毁就需要把A给销毁，造成了死锁
  
      return 0;
  }
  ```





# 指针的大小

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





# 注意

- 一旦一个对象使用智能指针管理后，就不该再使用原始裸指针去操作
- 









# 手写shared_ptr

- 补充，还要写一个线程安全的pointer

- ```cpp
  template <typename T>
  class Shared_mptr
  {
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
          if (this->ptr_ && --*this->count == 0)
          {
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





# 手写unique_ptr

- ```cpp
  template <typename T>
  class UniquePtr
  {
  public:
      //构造函数
      UniquePtr(T *ptr = nullptr) : m_pResource(ptr){};
      //析构函数
      ~UniquePtr()
      {
          del();
      }
      //先删除源对象，而后复制
      void reset(T *pResource)
      {
          del();
          m_pResource = pResource;
      }
      //交给
      T *release()
      {
          T *tmp = m_pResource;
          m_pResource = nullptr;
          return tmp;
      }
  
      T *get()
      {
          return m_pResource;
      }
  
      operator bool() const
      {
          return m_pResource != nullptr;
      }
  
      T *operator->() { return m_pResource; }
      T &operator*() { return *m_pResource; }
  
  private:
      void del()
      {
          if (m_pResource == nullptr)
          {
              return;
          }
          delete m_pResource;
          m_pResource = NULL;
      }
  
      UniquePtr(UniquePtr<T> &other) = delete;
      UniquePtr &operator=(const UniquePtr &) = delete;
  
      T *m_pResource;
  };
  ```







# 参考

- https://zhuanlan.zhihu.com/p/150555165
- https://www.zhihu.com/question/319277442/answer/1517987598
- https://zhuanlan.zhihu.com/p/532215950