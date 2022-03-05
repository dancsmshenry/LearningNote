# 容器

## Vector（数组）

### 基本用法

- ```cpp
  //构造函数的四种方式
  vector<string> i1(2, "hi");
  vector<string> i2{"why", "always", "me"};
  vector<string> i3(i2.begin(), i3.end());
  vector<stirng> i4(i3);
  
  //operator= 赋值运算符
  i4 = i3;
  
  //assign 第一个参数是数字，第二个参数是变量，即数量*变量
  vector<char> i5;
  i5.assign(5, 'x');
  i5.assign(i4.begin(), i4.end());//也可以用迭代器
  i5.assign({'1', '2', '3'});//还可以用initializer_list
  
  //at(索引)
  vector<int> i6{1, 2, 3};
  i6.at(1);//等价于i6[1]
  
  //operator[]，返回第几个值
  i6[1] = 10;
  
  //front容器首元素
  std::cout << i7.front() << std::endl;
  
  //back容器最后一个元素
  std::cout << i7.back() << std::endl;
  
  //begin返回指向容器的第一个元素的迭代器，end返回指向容器尾端的迭代器
  for (vector<string>::reverse_iterator it = sv.begin(); it != sv.end(); it ++ ){
      std::cout << *it << " ";
  }
  
  //rbegin返回一个指向容器最后一个元素的反向迭代器，rend返回一个指向容器前端的反向迭代器（反向迭代器+1会往前面移动）
  for (std::vector<int>::reverse_iterator it = test_vector.rbegin(); it != test_vector.rend(); it ++ ){
          std::cout << *it << " ";
  }
  
  //empty若容器为空则为true，否则为false
  bool flag = i6.empty();
  
  //size容器中的元素个数
  std::cout << i6.size() << std::endl;
  
  //max_size返回容器可容纳的元素最大数量
  std::cout << i6.max_size() << std::endl;
  
  //capacity返回当前分配存储的容量
  std::cout << i6.capacity() << std::endl;
  
  //resize重设容器大小以容纳count个元素
  i6.resize(10);
  
  //shrink_to_fit请求移除未使用的容量,将容量由capacity()减少为size()
  i6.shrink_to_fit();
  
  //clear从容器移除所有元素
  i6.clear();
  
  //insert的三种形式
  i6.insert(i6.begin(), 10);//在begin的位置添加一个10的元素
  i6.insert(i6.begin(), 10, 10);//在begin的位置添加10个值为10的元素
  i6.insert(i6.begin() + 2, i5.begin(), i5.end());//把另一个容器的元素插入到指定位置
  
  //erase从容器移除指定的元素
  i6.erase(i6.begin());//删除单个元素
  i6.erase(i6.begin() + 2, i6.begin() + 5);//删除指定区间的元素
  
  //push_back向容器尾部插入元素
  i6.push_back(111);
  
  //pop_back移除容器最后一个元素
  i6.pop_back();
  
  //swap交换两个容器的内容
  i6.swap(i5);
  
  //emplace在指定位置添加元素
  i6.emplace(i6.begin() + 1, 11);
  
  //emplace_back在容器末尾就地构造元素（在末尾添加元素）
  i6.emplace_back(10);
  ```



### 定义

- ![](vector的定义.png)
- 可以看到一个vector中有三个指针，分别指向使用空间的头尾，以及可用空间的尾
  - 为了降低空间配置的速度成本，vector实际配置的大小可能比客户端需求量大一些，这便是容量的概念
- 同时，将alloc作为默认的空间分配器
- 同时，vector的迭代器本质上就是一个指针，指向T元素
- ![](vector示意图.png)
- vector的指针类型都是存储在栈上的，而指针指向的数组才是存放在栈上的



### push_back

- 时间复杂度分析：https://zhuanlan.zhihu.com/p/165290655
- 实现原理：
  - 当我们以push_back将新元素插入到vector尾端的时候，首先检查是否有备用空间，如果有就直接在备用空间上构造元素，并调整迭代器finish，使vector变大，如果没有就拓大空间（重新配置、移动数据、释放原空间）
  - ![push_back](push_back.png)
  - 为什么还要独立开一个insert_aux函数：因为可能其他的函数，比如insert也会用到插入元素的功能，所以进行再次封装
  - ![insert_aux](insert_aux.png)
- 有关push_back和move的问题：https://www.zhihu.com/question/474844271/answer/2308411415
- 为什么要选择两倍扩容
  - 为什么是成倍扩容，而不是成差扩容？https://blog.csdn.net/zhangqianqian57/article/details/119135430
  - gcc是2倍扩容，有些是1.5倍
- 一旦空间重新分配，指向原vector的所有的迭代器都会失效





## List（双向链表）

### 基本用法

- ```cpp
  //四种构造函数
  list<string> list1{"why", "always", "me", "!"};
  list<string> list2(list1.begin(), list1.end());
  list<string> list3(list1);
  list<string> list4(4, "you");
  
  //operator=
  list<string> list5 = list1;
  
  //assign将值赋给容器（会覆盖掉原来的值）
  list1.assign({1,2,3,4,5});//插入initializer_list
  list1.assign(10, 1111);//第一个是数量，第二个是value
  list7.assign(list1.begin(), list1.end());//放入一个容器
  
  //front返回第一个元素，back返回最后一个元素
  
  //iterator和revers_iterator，正向迭代器和反向迭代器
  for (list<string>::iterator it = list1.begin(); it != list1.end(); it++) {
  	cout << *it << " ";
  }
  for (list<string>::reverse_iterator it = list1.rbegin(); it != list1.rend(); it++) {
  	cout << *it << " "; 
  }
  
  //empty判断容器是否为空，size返回大小，max_size返回容器的最大的容量
  
  //clear清除所有内容
  
  //insert插入元素
  list7.insert(list7.begin(), "hello");//指定位置插入元素
  list7.insert(list7.begin(), 2, "no");//指定位置插入一定数量的元素
  list7.insert(list7.begin(), list6.begin(), list6.end());//指定位置插入容器元素
  
  //erase删除指定位置的元素，ps：advance(range_begin, 2)使得迭代器向后移动数个位置
  list.erese(list.begin());//删除指定位置的元素
  list.erase(list.begin() + 2, list.begin() + 5);//删除区域间的元素
  
  //push_back，pop_back，push_front,pop_front
  
  //resize重新设定链表的大小，swap交换链表元素，sort排序，merge合并两个链表
  list9.merge(list8);
  
  //splice分割链表
  auto it = list11.begin();
  advance(it, 2);
  list11.splice(it, list12);//把链表的前两个给删除掉
  
  //remove移除满足特定标准的元素
  list12.remove(5);
  
  //reverse将该链表的所有元素的顺序反转
  list12.reverse();
  
  //unique删除连续的重复的元素
  list11.unique();
  
  //emplace_back在容器末尾就地构造元素
  ```



### 定义

- 节约空间，对于任何位置的元素插入或删除，都是常数时间
- list节点
  - 两个指针（一个指向前面的节点，一个指向后面的节点），一个数据
  - ![](list的节点.png)
- list迭代器
  - 一个指针（指向listnode节点）
  - ![](list迭代器.png)
- list
  - 一个指针（指向链表的第一个节点）
  - ![](list.png)
- list是一个环形链表
  - ![](list环形链表.png)
- 产生一个空链表
  - ![](空链表.png)





## Deque（双向队列）

### 基本用法

- ```cpp
  //构造函数的四种方式
  deque<string> words1{"the", "is", "deque"};
  deque<string> words2(words1.begin(), words1.end());
  deque<string> words3(words1);
  deque<string> words4(5, "YES");
  
  //front获取第一个元素
  std::cout << words1.front() << std::endl;
  
  //back返回最后一个元素
  std::cout << words1.back() << std::endl;
  
  //size返回容器的大小
  std::cout << "words contains : " << words4.size() << std::endl;
  
  //push_back把元素放入末尾
  words4.push_back("NO");
  
  //pop_back移除最后一个元素
  words4.pop_back();
  
  //push_front把元素放到开头
  words4.push_front("SS");
  
  //pop_front移除第一个元素
  words4.pop_front();
  
  //erast移除元素
  words4.erase(words4.begin());//移除某个位置的元素
  words1.erase(words1.begin()+2, words1.end());//移除某个区间的元素
  
  //insert插入元素
  words1.insert(words1.begin()+1, words4.begin(), words4.end());//第一个参数是位置，后面是要插入的容器的内容
  words1.insert(words1.begin()+3, "strat");//指定位置插入元素
  words1.insert(words1.begin()+3, 5, "IS");//位置，重复次数，重复的数据
  
  //iterator正向迭代器，+1是向右边走
  for (deque<string>::iterator it = words1.begin(); it != words1.end(); it++) {
  	cout << *it << " ";
  }
  
  //reverse_iterator反向迭代器，+1向左走
  for (deque<string>::reverse_iterator it = words1.rbegin(); it != words1.rend(); it++) {
  	cout << *it << " ";
  }
  
  //empty
  
  //size
  
  //max_size
  
  //shrink_to_fit
  
  //at
  
  //assign
  
  //emplace_back
  
  //emplace_front
  
  //swap
  ```



### 定义

- 是一种双向开口的连续线性空间，可以在头尾两端分别做元素的插入和删除
- 和vector的差异，允许在常数时间内对头端进行元素的插入或移除操作
- 没有容量观念，动态地以分段连续空间合成，随时可以增加一段新的空间并连接起来
- 非必要不适用deque，如果要对deque进行排序，就要先把deque复制到vector上，将vector排序，再复制会deque
- deque系由一段一段的定量连续空间构成。一旦有必要在deque的前端或尾端增加新空间，便配置一段定量连续空间，串接在整个deque的头端或尾端。deque的最大任务，便是在这些分段的定量连续空间上，维护其整体连续的假象，并提供随机存取的借口。避开了“重新配置、复制、释放”的轮回，代价则是复杂的迭代器架构
- deque采用一块所谓的map（注意，不是STL的map容器）作为主控。这里所谓map是一小块连续空间，其中每个元素（此处称为一个节点，node）都是指针，指向另一段（较大的）连续线性空间，称为缓冲区。缓冲区才是deque的储存空间主体。SGI STL 允许我们指定缓冲区大小，默认值0表示将使用512 bytes 缓冲区
- deque大体图
  - ![](deque大体图.png)
- 迭代器
  - 有四个指针，分别指向连续空间的开始地址，结束地址，空间中当前元素的地址以及连续空间地址在map中的位置（该节点在map中的位置）
  - ![](deque迭代器示意图.png)
  - ![](deque迭代器源码.png)
- deque中中控器、缓冲区、迭代器的相互关系
  - ![](deque中中控器、缓冲区、迭代器的相互关系.png)
- deque本身的数据结构
  - ![](deque数据结构.png)
- https://blog.csdn.net/u010710458/article/details/79540505





## Stack（栈）

### 基本用法

- ```cpp
  
  ```



### 定义

- stack默认的底部容器是deque（所以它的大小和deque的大小一样）
- ![](stack数据结构.png)
- stack不提供迭代器（因为先进后出，所以不能有迭代器）
- 也可以用list作为底部容器



## Queue（单向队列）

### 基本用法

- ```cpp
  
  ```



### 定义

- 先进先出，底层是以deque作为底层容器的
- ![](queue数据结构.png)
- queue也不提供迭代器，不提供遍历功能
- 也可以以list作为底层容器



## priority queue（优先队列）

- ```cpp
  
  ```



## Set（集合）

- ```cpp
  //默认初始化
  set<int> i;
  
  //插入元素
  i.insert(9);
  
  //initializer_list构造函数
  set<string> s{"why", "always", "me"};
  
  //复制构造函数
  set<string> c(s);
  
  ```

- 底层是红黑树实现



## Map（哈希表）

- ```cpp
  
  ```

- 底层是红黑树实现



## Unordered_set（集合）

- ```cpp
  ```

- 底层是哈希表实现



## Unordered_map（哈希表）

- ```cpp
  
  ```

- 底层是哈希表实现



- 



## String（字符串）

- ```cpp
  ```





# 算法

## max_element

- 返回容器的最大值



## accumulate

- 累积求和



## lower_bound

- 二分查找

- https://blog.csdn.net/qq_40160605/article/details/80150252





# 迭代器
