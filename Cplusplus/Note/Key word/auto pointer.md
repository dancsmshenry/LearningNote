# Shared_ptr

**shared_ptr** 是**C++11**提供的一种智能指针类，它足够智能，可以在任何地方都不使用时自动删除相关指针，从而帮助彻底消除内存泄漏和悬空指针的问题。
它遵循共享所有权的概念，即不同的 shared_ptr 对象可以与相同的指针相关联，并在内部使用引用计数机制来实现这一点。
**每个 shared_ptr 对象在内部指向两个内存位置：**
1、指向对象的指针。
2、用于控制引用计数数据的指针。
**共享所有权如何在参考计数的帮助下工作：**
1、当新的 shared_ptr 对象与指针关联时，则在其构造函数中，将与此指针关联的引用计数增加1。
2、当任何 shared_ptr 对象超出作用域时，则在其析构函数中，它将关联指针的引用计数减1。如果引用计数变为0，则表示没有其他 shared_ptr 对象与此内存关联，在这种情况下，它使用`delete`函数删除该内存





- 创建 shared_ptr 对象

使用原始指针创建 shared_ptr 对象

```cpp
std::shared_ptr<int> p1(new int());
```

上面这行代码在堆上创建了两块内存：1：存储`int`。2：用于引用计数的内存，管理附加此内存的 shared_ptr 对象的计数，最初计数将为1。



检查 shared_ptr 对象的引用计数

```cpp
p1.use_count();
```



创建空的 shared_ptr 对象

因为带有参数的 shared_ptr 构造函数是 explicit 类型的，所以不能像这样`std::shared_ptr<int> p1 = new int();`隐式调用它构造函数。创建新的shared_ptr对象的最佳方法是使用**std :: make_shared**：

```cpp
std::shared_ptr<int> p1 = std::make_shared<int>();
```

**std::make_shared** 一次性为`int`对象和用于引用计数的数据都分配了内存，而`new`操作符只是为`int`分配了内存。



- 分离关联的原始指针

要使 shared_ptr 对象取消与相关指针的关联，可以使用`reset()`函数：
**不带参数的reset()：**

```cpp
p1.reset();
```

它将引用计数减少1，如果引用计数变为0，则删除指针。
**带参数的reset()：**

```cpp
p1.reset(new int(34));
```

在这种情况下，它将在内部指向新指针，因此其引用计数将再次变为1。
**使用nullptr重置：**

```cpp
p1 = nullptr; 
```



- shared_ptr是一个伪指针

shared_ptr充当普通指针，我们可以将`*`和`->`与 shared_ptr 对象一起使用，也可以像其他 shared_ptr 对象一样进行比较;

完整示例

```cpp
#include <iostream>
#include  <memory> // 需要包含这个头文件

int main()
{
	// 使用 make_shared 创建空对象
	std::shared_ptr<int> p1 = std::make_shared<int>();
	*p1 = 78;
	std::cout << "p1 = " << *p1 << std::endl; // 输出78

	// 打印引用个数：1
	std::cout << "p1 Reference count = " << p1.use_count() << std::endl;

	// 第2个 shared_ptr 对象指向同一个指针
	std::shared_ptr<int> p2(p1);

	// 下面两个输出都是：2
	std::cout << "p2 Reference count = " << p2.use_count() << std::endl;
	std::cout << "p1 Reference count = " << p1.use_count() << std::endl;

	// 比较智能指针，p1 等于 p2
	if (p1 == p2) {
		std::cout << "p1 and p2 are pointing to same pointer\n";
	}

	std::cout<<"Reset p1 "<<std::endl;

	// 无参数调用reset，无关联指针，引用个数为0
	p1.reset();
	std::cout << "p1 Reference Count = " << p1.use_count() << std::endl;
	
	// 带参数调用reset，引用个数为1
	p1.reset(new int(11));
	std::cout << "p1  Reference Count = " << p1.use_count() << std::endl;

	// 把对象重置为NULL，引用计数为0
	p1 = nullptr;
	std::cout << "p1  Reference Count = " << p1.use_count() << std::endl;
	if (!p1) {
		std::cout << "p1 is NULL" << std::endl; // 输出
	}
	return 0;
}
12345678910111213141516171819202122232425262728293031323334353637383940414243
```

自定义删除器 Deleter

下面将讨论如何将自定义删除器与 std :: shared_ptr 一起使用。
当 shared_ptr 对象超出范围时，将调用其析构函数。在其析构函数中，它将引用计数减1，如果引用计数的新值为0，则删除关联的原始指针。
析构函数中删除内部原始指针，默认调用的是`delete()`函数。

```cpp
delete Pointer;
1
```

有些时候在析构函数中，delete函数并不能满足我们的需求，可能还想加其他的处理。

当 shared_ptr 对象指向数组

```cpp
// 需要添加自定义删除器的使用方式
std::shared_ptr<int> p3(new int[12]);   // 仅用于演示自定义删除器

// 指向数组的智能指针可以使用这种形式
std::shared_ptr<int[]> p3(new int[12]);  // 正确使用方式
12345
```

像这样申请的数组，应该调用`delete []`释放内存，而`shared_ptr<int>`析构函数中默认`delete`并不能满足需，可以使用`shared_ptr<int[]>`形式或者添加自定义删除器。

给shared_ptr添加自定义删除器

在上面在这种情况下，我们可以将回调函数传递给 shared_ptr 的构造函数，该构造函数将从其析构函数中调用以进行删除，即

```cpp
// 自定义删除器
void deleter(Sample * x)
{
	std::cout << "DELETER FUNCTION CALLED\n";
	delete[] x;
}
// 构造函数传递自定义删除器指针
std::shared_ptr<Sample> p3(new Sample[12], deleter);
12345678
```

下面看一个完整的示例：

```cpp
#include <iostream>
#include <memory>

struct Sample
{
    Sample() {
        std::cout << "Sample\n";
    }
    ~Sample() {
        std::cout << "~Sample\n";
    }
};

void deleter(Sample * x)
{
    std::cout << "Custom Deleter\n";
    delete[] x;
}

int main()
{
    std::shared_ptr<Sample> p3(new Sample[3], deleter);
    return 0;
}
123456789101112131415161718192021222324
```

输出：

```txt
Sample
Sample
Sample
Custom Deleter
~Sample
~Sample
~Sample
1234567
```

使用Lambda 表达式 / 函数对象作为删除器

```cpp
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
1234567891011121314151617
```

shared_ptr 相对于普通指针的优缺点

缺少 ++, – – 和 [] 运算符

与普通指针相比，shared_ptr仅提供`->` 、`*`和`==`运算符，没有`+`、`-`、`++`、`--`、`[]`等运算符。
示例：

```cpp
#include<iostream>
#include<memory>

struct Sample {
	void dummyFunction() {
		std::cout << "dummyFunction" << std::endl;
	}
};

int main()
{

	std::shared_ptr<Sample> ptr = std::make_shared<Sample>();

	(*ptr).dummyFunction(); // 正常
	ptr->dummyFunction(); // 正常

	// ptr[0]->dummyFunction(); // 错误方式
	// ptr++;  // 错误方式
	//ptr--;  // 错误方式

	std::shared_ptr<Sample> ptr2(ptr);
	if (ptr == ptr2) // 正常
		std::cout << "ptr and ptr2 are equal" << std::endl;
	return 0;
}
1234567891011121314151617181920212223242526
```

NULL检测

当我们创建 shared_ptr 对象而不分配任何值时，它就是空的；普通指针不分配空间的时候相当于一个野指针，指向垃圾空间，且无法判断指向的是否是有用数据。
**shared_ptr 检测空值方法**

```cpp
std::shared_ptr<Sample> ptr3;
if(!ptr3)
	std::cout<<"Yes, ptr3 is empty" << std::endl;
if(ptr3 == NULL)
	std::cout<<"ptr3 is empty" << std::endl;
if(ptr3 == nullptr)
	std::cout<<"ptr3 is empty" << std::endl;
```

创建 shared_ptr 时注意事项

不要使用同一个原始指针构造 shared_ptr

创建多个 shared_ptr 的正常方法是使用一个已存在的shared_ptr 进行创建，而不是使用同一个原始指针进行创建。
示例：

```cpp
    int *num = new int(23);
    std::shared_ptr<int> p1(num);
    
    std::shared_ptr<int> p2(p1);  // 正确使用方法
    std::shared_ptr<int> p3(num); // 不推荐

    std::cout << "p1 Reference = " << p1.use_count() << std::endl; // 输出 2
    std::cout << "p2 Reference = " << p2.use_count() << std::endl; // 输出 2
    std::cout << "p3 Reference = " << p3.use_count() << std::endl; // 输出 1
```

假如使用原始指针`num`创建了p1，又同样方法创建了p3，当p1超出作用域时会调用`delete`释放`num`内存，此时num成了悬空指针，当p3超出作用域再次`delete`的时候就可能会出错。

不要用栈中的指针构造 shared_ptr 对象

shared_ptr 默认的构造函数中使用的是`delete`来删除关联的指针，所以构造的时候也必须使用`new`出来的堆空间的指针。
示例：

```cpp
#include<iostream>
#include<memory>

int main()
{
   int x = 12;
   std::shared_ptr<int> ptr(&x);
   return 0;
}
```

当 shared_ptr 对象超出作用域调用析构函数`delete` 指针`&x`时会出错。

建议使用 make_shared

为了避免以上两种情形，建议使用`make_shared()<>`创建 shared_ptr 对象，而不是使用默认构造函数创建。

```cpp
std::shared_ptr<int> ptr_1 = make_shared<int>();
std::shared_ptr<int> ptr_2 (ptr_1);
```

另外不建议使用`get()`函数获取 shared_ptr 关联的原始指针，因为如果在 shared_ptr 析构之前手动调用了`delete`函数，同样会导致类似的错误。





# Unique_ptr

- **unique_ptr** 是 **C++ 11** 提供的用于防止内存泄漏的智能指针中的一种实现，独享被管理对象指针所有权的智能指针。unique_ptr对象包装一个原始指针，并负责其生命周期。当该对象被销毁时，会在其析构函数中删除关联的原始指针。
  unique_ptr具有`->`和`*`运算符重载符，因此它可以像普通指针一样使用。
  查看下面的示例：

  ```cpp
  #include <iostream>
  #include <memory>
  
  struct Task {
      int mId;
      Task(int id ) :mId(id) {
          std::cout << "Task::Constructor" << std::endl;
      }
      ~Task() {
          std::cout << "Task::Destructor" << std::endl;
      }
  };
  
  int main()
  {
      // 通过原始指针创建 unique_ptr 实例
      std::unique_ptr<Task> taskPtr(new Task(23));
  
      //通过 unique_ptr 访问其成员
      int id = taskPtr->mId;
      std::cout << id << std::endl;
  
      return 0;
  }
  123456789101112131415161718192021222324
  ```

  输出：

  ```txt
  Task::Constructor
  23
  Task::Destructor
  123
  ```

  `unique_ptr <Task>` 对象 `taskPtr` 接受原始指针作为参数。现在当main函数退出时，该对象超出作用范围就会调用其析构函数，在`unique_ptr`对象`taskPtr` 的析构函数中，会删除关联的原始指针，这样就不用专门delete Task对象了。
  这样不管函数正常退出还是异常退出（由于某些异常），也会始终调用taskPtr的析构函数。因此，原始指针将始终被删除并防止内存泄漏。

  ### unique_ptr 独享所有权

  unique_ptr对象始终是关联的原始指针的唯一所有者。我们无法复制unique_ptr对象，它只能移动。
  由于每个unique_ptr对象都是原始指针的唯一所有者，因此在其析构函数中它直接删除关联的指针，不需要任何参考计数。

  #### 创建一个空的 unique_ptr 对象

  创建一个空的`unique_ptr<int>`对象，因为没有与之关联的原始指针，所以它是空的。

  ```
  std::unique_ptr<int> ptr1;
  1
  ```

  #### 检查 unique_ptr 对象是否为空

  有两种方法可以检查 unique_ptr 对象是否为空或者是否有与之关联的原始指针。

  ```cpp
  // 方法1
  if(!ptr1)
  	std::cout<<"ptr1 is empty"<<std::endl;
  // 方法2
  if(ptr1 == nullptr)
  	std::cout<<"ptr1 is empty"<<std::endl;
  123456
  ```

  #### 使用原始指针创建 unique_ptr 对象

  要创建非空的 unique_ptr 对象，需要在创建对象时在其构造函数中传递原始指针，即：

  ```cpp
  std::unique_ptr<Task> taskPtr(new Task(22));
  1
  ```

  或者（这种新学到的）

  ```cpp
  std::unique_ptr<Task> taskPtr(new std::unique_ptr<Task>::element_type(23));
  1
  ```

  不能通过赋值的方法创建对象，下面的这句是错误的

  ```cpp
  // std::unique_ptr<Task> taskPtr2 = new Task(); // 编译错误
  1
  ```

  #### 使用 std::make_unique 创建 unique_ptr 对象 / C++14

  std::make_unique<>() 是C++ 14 引入的新函数

  ```cpp
  std::unique_ptr<Task> taskPtr = std::make_unique<Task>(34);
  1
  ```

  #### 获取被管理对象的指针

  使用`get()`·函数获取管理对象的指针。

  ```cpp
  Task *p1 = taskPtr.get();
  1
  ```

  #### 重置 unique_ptr 对象

  在 unique_ptr 对象上调用`reset()`函数将重置它，即它将释放delete关联的原始指针并使unique_ptr 对象为空。

  ```cpp
  taskPtr.reset();
  1
  ```

  #### unique_ptr 对象不可复制

  由于 unique_ptr 不可复制，只能移动。因此，我们无法通过复制构造函数或赋值运算符创建unique_ptr对象的副本。

  ```cpp
  // 编译错误 : unique_ptr 不能复制
  std::unique_ptr<Task> taskPtr3 = taskPtr2; // Compile error
  
  // 编译错误 : unique_ptr 不能复制
  taskPtr = taskPtr2; //compile error
  12345
  ```

  #### 转移 unique_ptr 对象的所有权

  我们无法复制 unique_ptr 对象，但我们可以转移它们。这意味着 unique_ptr 对象可以将关联的原始指针的所有权转移到另一个 unique_ptr 对象。让我们通过一个例子来理解：

  ```cpp
  // 通过原始指针创建 taskPtr2
  std::unique_ptr<Task> taskPtr2(new Task(55));
  // 把taskPtr2中关联指针的所有权转移给taskPtr4
  std::unique_ptr<Task> taskPtr4 = std::move(taskPtr2);
  // 现在taskPtr2关联的指针为空
  if(taskPtr2 == nullptr)
  	std::cout<<"taskPtr2 is  empty"<<std::endl;
  
  // taskPtr2关联指针的所有权现在转移到了taskPtr4中
  if(taskPtr4 != nullptr)
  	std::cout<<"taskPtr4 is not empty"<<std::endl;
  
  // 会输出55
  std::cout<< taskPtr4->mId << std::endl;
  1234567891011121314
  ```

  `std::move()` 将把 `taskPtr2` 转换为一个右值引用。因此，调用 unique_ptr 的移动构造函数，并将关联的原始指针传输到 `taskPtr4`。在转移完原始指针的所有权后， `taskPtr2`将变为空。

  #### 释放关联的原始指针

  在 unique_ptr 对象上调用 `release()`将释放其关联的原始指针的所有权，并返回原始指针。这里是释放所有权，并没有delete原始指针，`reset()`会delete原始指针。

  ```cpp
  std::unique_ptr<Task> taskPtr5(new Task(55));
  // 不为空
  if(taskPtr5 != nullptr)
  	std::cout<<"taskPtr5 is not empty"<<std::endl;
  // 释放关联指针的所有权
  Task * ptr = taskPtr5.release();
  // 现在为空
  if(taskPtr5 == nullptr)
  	std::cout<<"taskPtr5 is empty"<<std::endl;
  123456789
  ```

  ### 完整示例程序

  ```cpp
  #include <iostream>
  #include <memory>
  
  struct Task {
      int mId;
      Task(int id ) :mId(id) {
          std::cout<<"Task::Constructor"<<std::endl;
      }
      ~Task() {
          std::cout<<"Task::Destructor"<<std::endl;
      }
  };
  
  int main()
  {
      // 空对象 unique_ptr
      std::unique_ptr<int> ptr1;
  
      // 检查 ptr1 是否为空
      if(!ptr1)
          std::cout<<"ptr1 is empty"<<std::endl;
  
      // 检查 ptr1 是否为空
      if(ptr1 == nullptr)
          std::cout<<"ptr1 is empty"<<std::endl;
  
      // 不能通过赋值初始化unique_ptr
      // std::unique_ptr<Task> taskPtr2 = new Task(); // Compile Error
  
      // 通过原始指针创建 unique_ptr
      std::unique_ptr<Task> taskPtr(new Task(23));
  
      // 检查 taskPtr 是否为空
      if(taskPtr != nullptr)
          std::cout<<"taskPtr is  not empty"<<std::endl;
  
      // 访问 unique_ptr关联指针的成员
      std::cout<<taskPtr->mId<<std::endl;
  
      std::cout<<"Reset the taskPtr"<<std::endl;
      // 重置 unique_ptr 为空，将删除关联的原始指针
      taskPtr.reset();
  
      // 检查是否为空 / 检查有没有关联的原始指针
      if(taskPtr == nullptr)
          std::cout<<"taskPtr is  empty"<<std::endl;
  
      // 通过原始指针创建 unique_ptr
      std::unique_ptr<Task> taskPtr2(new Task(55));
  
      if(taskPtr2 != nullptr)
          std::cout<<"taskPtr2 is  not empty"<<std::endl;
  
      // unique_ptr 对象不能复制
      //taskPtr = taskPtr2; //compile error
      //std::unique_ptr<Task> taskPtr3 = taskPtr2;
  
      {
          // 转移所有权（把unique_ptr中的指针转移到另一个unique_ptr中）
          std::unique_ptr<Task> taskPtr4 = std::move(taskPtr2);
          // 转移后为空
          if(taskPtr2 == nullptr)
              std::cout << "taskPtr2 is  empty" << std::endl;
          // 转进来后非空
          if(taskPtr4 != nullptr)
              std::cout<<"taskPtr4 is not empty"<<std::endl;
  
          std::cout << taskPtr4->mId << std::endl;
  
          //taskPtr4 超出下面这个括号的作用于将delete其关联的指针
      }
  
      std::unique_ptr<Task> taskPtr5(new Task(66));
  
      if(taskPtr5 != nullptr)
          std::cout << "taskPtr5 is not empty" << std::endl;
  
      // 释放所有权
      Task * ptr = taskPtr5.release();
  
      if(taskPtr5 == nullptr)
          std::cout << "taskPtr5 is empty" << std::endl;
  
      std::cout << ptr->mId << std::endl;
  
      delete ptr;
  
      return 0;
  }
  1234567891011121314151617181920212223242526272829303132333435363738394041424344454647484950515253545556575859606162636465666768697071727374757677787980818283848586878889
  ```

  输出：

  ```txt
  ptr1 is empty
  ptr1 is empty
  Task::Constructor
  taskPtr is  not empty
  23
  Reset the taskPtr
  Task::Destructor
  taskPtr is  empty
  Task::Constructor
  taskPtr2 is  not empty
  taskPtr2 is  empty
  taskPtr4 is not empty
  55
  Task::Destructor
  Task::Constructor
  taskPtr5 is not empty
  taskPtr5 is empty
  66
  Task::Destructor
  12345678910111213141516171819
  ```

  ### 总结

  new出来的对象是位于堆内存上的，必须调用delete才能释放其内存。
  unique_ptr 是一个装指针的容器，且拥有关联指针的唯一所有权，作为普通变量使用时系统分配对象到栈内存上，超出作用域时会自动析构，unique_ptr对象的析构函数中会delete其关联指针，这样就相当于替我们执行了delete堆内存上的对象。

  | 成员函数  | 作用                                                         |
  | --------- | ------------------------------------------------------------ |
  | reset()   | 重置unique_ptr为空，delete其关联的指针。                     |
  | release() | 不delete关联指针，并返回关联指针。释放关联指针的所有权，unique_ptr为空。 |
  | get()     | 仅仅返回关联指针                                             |

  unique_ptr不能直接复制，必须使用`std::move()`转移其管理的指针，转移后原 unique_ptr 为空。`std::unique_ptr<Task> taskPtr4 = std::move(taskPtr2);`

  创建unique_ptr对象有两种方法：

  ```cpp
  //C++11: 
  std::unique_ptr<Task> taskPtr(new Task(23));
  //C++14: 
  std::unique_ptr<Task> taskPtr = std::make_unique<Task>(34);
  ```



- 但是unique_ptr指定删除函数的方法和shared_ptr的方法不一样
  - https://blog.csdn.net/hp_cpp/article/details/103210135





# Weak_ptr

- 弱引用解决循环引用https://blog.csdn.net/zgaoq/article/details/80183910
- 只能由weak_ptr和shared_ptr演变而来
- 是弱引用，只有对象的使用权，不会导致堆内存空间的引用计数增加或减少





# Auto_ptr



# 手写shared_ptr

- ```cpp
  class Shared_mptr {
  public:
  	//空类构造，count，ptr均置空
  	Shared_mptr() :count(0), ptr_((T*)0) {}
  	//赋值构造，count返回int指针，必须new int，ptr指向值
  	Shared_mptr(T* p) :count(new int(1)), ptr_(p) {}
  	//拷贝构造，注意是&引用，此处注意的一点是，count需要+1
  	Shared_mptr(Shared_mptr<T> &other) :count(&(++ *other.count)), ptr_(other.ptr_) {}
  	//重载->返回T*类型
  	T* operator->() { return ptr_; }
  	//重载*返回T&引用
  	T& operator*() { return *ptr_; }
  	//重载=，此处需要将源计数减一，并判断是否需要顺便析构源，然后将thiscount+1，注意最后返回*this
  	Shared_mptr<T>& operator=(Shared_mptr<T>& other) 
  	{
  		if (this == &other)
  			return *this;
  		++*other.count;
  		if (this->ptr_&&--*this->count == 0)
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
  	~Shared_mptr()
  	{
  		if (ptr_&&--*count == 0)
  		{
  			delete ptr_;
  			delete count;
  			cout << "delete from ~" << endl;
  		}
  	}
  	//返回count
  	int getRef()
  	{
  		return *count;
  	}
  
  private:
  	int *count;//注意此处是count*，因为计数其实是同一个count，大家都以指针来操作；
  	T* ptr_;
  };
  
  ```



# 手写unique_ptr

- ```cpp
  #include <string>
  #include <iostream>
  using namespace std;
  
  template <typename T>
  class UniquePtr
  {
  public:
  	//构造函数
  	UniquePtr(T* ptr = nullptr) :m_pResource(ptr) {};
  	//析构函数
  	~UniquePtr()
  	{
  		del();
  	}
  	//先删除源对象，而后复制
  	void reset(T* pResource)
  	{
  		del();
  		m_pResource = pResource;
  	}
  	//交给
  	T* release()
  	{
  		T* tmp = m_pResource;
  		m_pResource = nullptr;
  		return tmp;
  	}
  
  	T* get()
  	{
  		return m_pResource;
  	}
  	
  	operator bool() const
  	{
  		return m_pResource != nullptr;
  	}
  
  	T* operator->() { return m_pResource; }
  	T& operator*() { return *m_pResource; }
  
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
  	UniquePtr& operator=(const UniquePtr &) = delete;
  
  	T *m_pResource;
  };
  
  ```

- 





12、智能指针，手撕shared_ptr，实现shared_ptr该井以实现线程安全