# Vector（数组）

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







# Deque（双向队列）

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





# List（双向链表）

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



# Set（集合，RB-Tree）

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



# Map（key-value）

- ```cpp
  
  ```



# Stack（栈）

- ```cpp
  ```





# Queue（单向队列）

- ```cpp
  
  ```



# Unordered_set（集合，hash）

- ```cpp
  ```



# Unordered_map（key-value，hash）

- ```cpp
  
  ```



# String

- ```cpp
  ```



# Pair

- ```cpp
  ```



# priority queue（优先队列）



# 一些其他函数

- ```cpp
  max_element;//q
  accumulate;//累积求和
  ```

- 