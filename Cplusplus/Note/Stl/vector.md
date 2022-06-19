# vector

### 用法

- ```cpp
  //构造函数的四种方式
  vector<string> i1(2, "hi");
  vector<string> i2{"why", "always", "me"};
  vector<string> i3(i2.begin(), i3.end());
  vector<stirng> i4(i3);
  
  vector<int> f(4); // 保证得到的元素都是0
  
  // operator= 赋值运算符
  i4 = i3;
  
  // assign
  vector<char> i5;
  i5.assign(5, 'x');               // 第一个参数是数字，第二个参数是变量，即数量*变量
  i5.assign(i4.begin(), i4.end()); // 也可以用迭代器
  i5.assign({'1', '2', '3'});      // 还可以用initializer_list
  
  // at(索引)
  vector<int> i6{1, 2, 3};
  i6.at(1); //等价于i6[1]
  
  // operator[]，返回第几个值
  i6[1] = 10;
  
  // front容器首元素
  std::cout << i7.front() << std::endl;
  
  // back容器最后一个元素
  std::cout << i7.back() << std::endl;
  
  // begin返回指向容器的第一个元素的迭代器，end返回指向容器尾端的迭代器
  for (vector<string>::reverse_iterator it = sv.begin(); it != sv.end(); it++)
  {
      std::cout << *it << " ";
  }
  
  // rbegin返回一个指向容器最后一个元素的反向迭代器，rend返回一个指向容器前端的反向迭代器（反向迭代器+1会往前面移动）
  for (std::vector<int>::reverse_iterator it = test_vector.rbegin(); it != test_vector.rend(); it++)
  {
      std::cout << *it << " ";
  }
  
  // empty若容器为空则为true，否则为false
  bool flag = i6.empty();
  
  // size容器中的元素个数
  std::cout << i6.size() << std::endl;
  
  // max_size返回容器可容纳的元素最大数量
  std::cout << i6.max_size() << std::endl;
  
  // capacity返回当前分配存储的容量
  std::cout << i6.capacity() << std::endl;
  
  // resize重设容器大小以容纳count个元素
  i6.resize(10);
  
  // shrink_to_fit请求移除未使用的容量,将容量由capacity()减少为size()
  i6.shrink_to_fit();
  
  // clear从容器移除所有元素
  i6.clear();
  
  // insert的三种形式
  i6.insert(i6.begin(), 10);                       //在begin的位置添加一个10的元素
  i6.insert(i6.begin(), 10, 10);                   //在begin的位置添加10个值为10的元素
  i6.insert(i6.begin() + 2, i5.begin(), i5.end()); //把另一个容器的元素插入到指定位置
  
  // erase从容器移除指定的元素
  i6.erase(i6.begin());                     //删除单个元素
  i6.erase(i6.begin() + 2, i6.begin() + 5); //删除指定区间的元素
  
  // push_back向容器尾部插入元素
  i6.push_back(111);
  
  // pop_back移除容器最后一个元素
  i6.pop_back();
  
  // swap交换两个容器的内容
  i6.swap(i5);
  
  // emplace在指定位置添加元素
  i6.emplace(i6.begin() + 1, 11);
  
  // emplace_back在容器末尾就地构造元素（在末尾添加元素）
  i6.emplace_back(10);
  ```







### 实现

- ![](image/vector的定义.png)
- 可以看到一个vector中有**三个指针**，分别指向使用空间的头尾，以及可用空间的尾
  - 为了降低空间配置的速度成本，vector实际配置的大小可能比客户端需求量大一些，这便是容量的概念
- alloc作为默认的空间分配器
- vector的迭代器本质上就是一个指针，指向元素T
  - 所以迭代器也可以用[]运算符进行访问：b[i]等价于*(b + i)

- ![](image/vector示意图.png)
- vector的指针类型都是存储在栈上的，而指针指向的数组才是存放在堆上的
- 为什么不能把数据放到栈上
  - 栈上是不能动态扩容的（栈上的元素的析构时脱离了作用域才会析构的，而我们如果需要实现动态扩容的话就需要）
- 为什么end要在最后一个元素的后面一个位置：因为当没有元素的时候，begin和end指向一起







### 扩容

- 为什么要选择两倍扩容
  - 为什么是成倍扩容，而不是成差扩容？https://blog.csdn.net/zhangqianqian57/article/details/119135430
  - gcc是2倍扩容，有些是1.5倍
- 新增元素：vector通过一个连续的数组存放元素，如果集合已满，在新增数据的时候，就要分配一块 更大的内存，将原来的数据复制过来，释放之前的内存，在插入新增的元素
- 对vector的任何操作，一旦引起空间重新配置，指向原vector的所有迭代器就都失效了
- 初始时刻vector的capacity为0，塞入第一个元素后capacity增加为1
- 不同的编译器实现的扩容方式不一样，VS2015中以1.5倍扩容，GCC以2倍扩容

- 对比可以发现采用采用成倍方式扩容，可以保证常数的时间复杂度，而增加指定大小的容量只能达到 O(n)的时间复杂度，因此，使用成倍的方式扩容

- 考虑可能产生的堆空间浪费，成倍增长倍数不能太大，使用较为广泛的扩容方式有两种，以2二倍的 方式扩容，或者以1.5倍的方式扩容
- 以2倍的方式扩容，导致下一次申请的内存必然大于之前分配内存的总和，导致之前分配的内存不能 再被使用，所以最好倍增长因子设置为(1,2)之间








### resize

- resize的扩容，会把新扩容得到的元素设为0（原来的部分比较大的话，就会把多出来的部分给删除掉）







### data()

- ```cpp
  #include <iostream>
  #include <vector>
  
  using namespace std;
  
  int main() {
      int *p;
      std::vector<int> holder;
      {
          vector<int> a{1,2,3,4,5};
          p = a.data();
          holder = std::move(a);
      }
      cout << p[0] << endl;
  }
  ```







### push_back

- 时间复杂度分析：https://zhuanlan.zhihu.com/p/165290655
- 实现原理：
  - 当我们以push_back将新元素插入到vector尾端的时候，首先检查是否有备用空间，如果有就直接在备用空间上构造元素，并调整迭代器finish，使vector变大，如果没有就拓大空间（重新配置、移动数据、释放原空间）
  - ![push_back](image/push_back.png)
  - 为什么还要独立开一个insert_aux函数：因为可能其他的函数，比如insert也会用到插入元素的功能，所以进行再次封装
  - ![insert_aux](image/insert_aux.png)
- 有关push_back和move的问题：https://www.zhihu.com/question/474844271/answer/2308411415
- 一旦空间重新分配，指向原vector的所有的迭代器都会失效





### shrink_to_fit

- 将容器的容量变小，所以会重新分配内存





### erase

- erase()函数，只能删除内容，不能改变容量大小;  erase成员函数，它删除了itVect迭代器指向的元素，并且返回要被删除的itVect之后的迭代器，迭代器相 当于一个智能指针;clear()函数，只能清空内容，不能改变容量大小;如果要想在删除内容的同时释放内 存，那么你可以选择deque容器
- erasre也不会改变容器的容量的







### clear

- vector的clear()的时间复杂度是多少？
  - 参考:https://www.zhihu.com/question/355171938/answer/2173582004
- clear只是改变容器的大小（last/end指针的位置），不会改变capacity








### at和[]

- vector越界访问其实是不会报错的（但是访问到啥变量就不清楚了）（因为每次判断是否越界的分支if语句其实是非常损耗性能的）
- vector的at会检查是否越界（at的参数时size_t，放入负数的话会被转为整数）







### pop_back

- 向量容器vector的成员函数pop_back()可以删除最后一个元素







### remove

- 还可以采用通用算法remove()来删除vector容器中的元素







### push_back和emplace_back的区别

- 这两者都是将对象放到vector当中

- ```cpp
  #include <iostream>
  #include <vector>
  
  class Test {
  public:
      Test() {std::cout << "Test" << std::endl;}
      ~Test() {std::cout << "~Test" << std::endl;}
      Test(const Test &p) {std::cout << "Test copy" << std::endl;}
      Test(const Test &&p) {std::cout << "Test move" << std::endl;}
      Test(int age) {std::cout << "Test age" << std::endl;}
  };
  
  int main(int argc, const char *argv[]) {
      std::vector<Test> v;
      v.emplace_back(Test(12));
      /*
      Test age
  	Test move
  	~Test
  	~Test//程序结束的析构
  	传右值：这里调用了一次构造函数（先在外面构造一个临时对象，执行完这句话后析构），一次移动构造函数（在emplace_back里面），所以有两次析构
      */
      
      v.push_back(Test(12));
      /*
      Test age
  	Test move
  	~Test
  	~Test//程序结束的析构
  	传右值：这里调用了一次构造函数（先在外面构造一个临时对象，执行完这句话后析构），一次移动构造函数（在push_back里面），所以有两次析构 
      */
      
      v.emplace_back(12);
      /*
      Test age
  	~Test//程序结束的析构
  	传右值：这里调用了一次含参的构造函数
      */
      
      v.push_back(12);
      /*
      Test age
  	Test move
  	~Test
  	~Test//程序结束的析构
  	传右值：这里调用了一次构造函数（先在外面构造一个临时对象，执行完这句话后析构），一次移动构造函数（在push_back里面），所以有两次析构
      */
      
      //传左值的话，两者都是一样的：调用一次构造函数，再调用一次拷贝构造函数（在push_back或emplace_back里面）
  }
  
  ```

- 所以，从语义上来说，如果你传入的是一个左值，就表明你是还需要这个值的，所以两个push都是一样的效果

- 但，如果你传入的是一个右值的话，那么系统就会认为你是不需要这个值的，所以就会调用移动构造函数然后再push

- 而至此，好像两者都是一样的，没啥不同，但是接下来就会有问题了：

  - 如果传入的不是该类对象，而是一个数字（但是可以隐性的转换为该类对象）
  - 那对于push_back来说，和传入一般的右值是一样的
  - 可是，对于emplace_back来说，只会调用一次构造函数哦......
  - 可能这就是emplace_back的意义吧....
  
- 使用push_back()向容器中加入一个右值元素(临时对象)时，首先会调用构造函数构造这个临时对象，然后需要调用拷贝构造函数将这个临时对象放入容器中。原来的临时变量释放。这样造成的问题就是临时变量申请资源的浪费

- 引入了右值引用，转移构造函数后，push_back()右值时就会调用构造函数和转移构造函数,如果可以在插入的时候直接构造，就只需要构造一次即可。这就是c++11 新加的emplace_back

- ```cpp
  template <class... Args>
  void emplace_back(Args&&... args);
  ```

- 在容器尾部添加一个元素，这个元素原地构造，不需要触发拷贝构造和转移构造

- 总结：

  - push_back：对于右值，拷贝构造+移动构造；对于左值，构造+拷贝构造
  - emplace_push：对于右值， 会直接原地构造对象同时插入；对于左值，即emplace_back是直接拷贝构造到容器上







### 释放空间

- 由于vector的内存占用空间只增不减，比如你首先分配了10,000个字节，然后erase掉后面9,999个，留下一个有效元素，但是内存占用仍为10,000个（所有内存空间是在vector析构时候才能被系统回收）

- clear()可以清空所有元素。但是即使clear()，vector所占用的内存空间不变，无法保证内存的回收

- 如果要清空vector所占用的内存，可以用swap

- ```cpp
  #include <vector>
  #include <iostream>
  
  using namespace std;
  
  int main() {
      vector<int> f1(100, 100);
      {
          vector<int> f;
          f1.swap(f);
      }
      //	vector<int>().swap(f1); // 或者这样
      
      
      // 为什么这样不行
      //	f1.swap(vector<int>()); // 因为swap的参数是T&，不能传递匿名对象
      cout << f1.size() << endl;
  }
  ```
