# 有了指针为什么还要迭代器

- 迭代器不是指针，是类模板，表现的像指针，他是模拟了指针的一些功能，重载了指针的一些操作
- 返回的也是对象的引用
- Iterator类的访问方式就是把不同集合类的访问逻辑抽象出来，使得不用暴露集合内部的结构而达到循环遍历集合的效果
- 背景：编程中会用到各种各样的容器，这些容器的底层实现不同，所以它们进行遍历的方法也是不同的，这不利于代码的重用
- 范围上：指针也是迭代器的一种
- 功能上：迭代器有着比指针更细的划分并对应能力不同的功能（迭代器重载了很多的运算符）
- 行为上：迭代器用法上更加统一良好（不怕越界，可以使用begin和end）



# 迭代器的注意事项

- for each容器的时候是基于迭代器的，如果一边遍历一遍insert元素的话，就可能造成容器扩容，间接导致失效
- 例如unordered_set在添加元素的时候，如果容量达到上限的话，就会使得迭代器失效



# emplace和insert效率的问题

- emplace的一般实现是用的args去创建（构造）一个新的对象，然后将这个对象去实施真正的insert操作。可是这里用的unordered_set,那么很可能因为不能出现重复key的原因出现拒绝添加，那么就会析构这个对象，这样这个构造+析构的操作就是浪费的了
- 而这里的insert只会在发现可以添加的时候才创建一个对象，因此少了对象的构造和拷贝
- 参考《Effective Modern C++》条款42
- 因此emplace在vector，list等容器上效率会高很多，因为新增元素的位置与元素本身无关
- 而set，map等容器需要依据元素本身的比较结果才能确定插入位置，因此无论如何都要先构造出元素，确定位置后才能把元素移过去



# 为什么stl的扩容没有用到移动构造

- 可以发现 `std::vector` 并没有采用 `std::move`，而是调用的拷贝构造函数。这一点是很重要的，因为移动构造意味着所有权的变更，因此在移动构造的过程中，如果出现了异常，那么原始数据很有可能是无法恢复的。而拷贝构造就不一样了，即使产生了异常，原始数据还是存在的。这也是 STL 中的设计思路之一



# emplace_back和push_back的区别

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




# back函数的坑爹的地方

- back返回的是对象元素的引用，如果临时变量的声明周期结束了（扩容导致地址失效），引用就会悬空失效了..



# memset

- 不要用memset对容器进行清空，因为容器的内部结构很复杂，必定codedump，从而后续造成内存泄漏
- 也不要用这个对memset对vector进行初始化
- vector中有其自身的结构，不能单纯的按字节进行初始化。使用memset对vector进行初始化，会破坏vector中的结构，造成vector中的数据错误



# vector 扩容优化

- 使用move吗......



# vector 线程安全

- 必然不是线程安全的（又不是原子操作，有没有上锁....）
- 解决办法：可以考虑用两个vector, 轮换使用，更新的vector不去读， 当前的读的vector不更新，然后轮换当前vector





# 一些坑

- list在早期的版本中，size的时间复杂度是o(n)

- ```cpp
  /* stl_list.h */
  template <typename _Tp, typename _Alloc = std::allocator<_Tp>>
      class list : protected _List_base<_Tp, _Alloc> {
      ...
      /**  Returns the number of elements in the %list.  */
      size_type size() const _GLIBCXX_NOEXCEPT { 
          return std::distance(begin(), end()); 
      }
      ...
  }
  
  /* bits/stl_iterator_base_funcs.h */
  template<typename _InputIterator>
  inline typename iterator_traits<_InputIterator>::difference_type
  distance(_InputIterator __first, _InputIterator __last) {
      // concept requirements -- taken care of in __distance
      return std::__distance(__first, __last, std::__iterator_category(__first));
  }
  
  /* bits/stl_iterator_base_funcs.h */
  template <typename _InputIterator>
  inline typename iterator_traits<_InputIterator>::difference_type
  __distance(_InputIterator __first, _InputIterator __last, input_iterator_tag) {
      // concept requirements
      __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
  
      /* 遍历列表获取 __n。*/
      typename iterator_traits<_InputIterator>::difference_type __n = 0;
      while (__first != __last) {
          ++__first;
          ++__n;
      }
      return __n;
  }
  ```

- 在cpp11后保证了是o1

- 原因：

  - STL中的链表是支持splice方法的。在做splice的时候我们无法预先知道被插入的链表会变大多少，被移除的链表会减少多少，除非循环遍历被splice的区间。但是一般来讲我们希望splice的时间复杂度是常数时间的，所以老版本的实现size()时选择了每次循环遍历。新版本改成常数时间是有代价的，就是splice这个方法每次都要循环遍历区间来维护两个链表的大小，这个方法就废掉了



map<int, int> m;能否通过m[0]判断是否在map中

vector list map 等存储1000个对象，哪种耗费内存最多 为什么

好像有本书说不要继承stl容器

https://zhuanlan.zhihu.com/p/352606819



5、最长回文子串

- 首先，vector因为被标准库包装了太多，导致内存空间上不如普通的二维数组，所以使用的空间上会比一般的做法逊色很多

- 其次，比较一下语句

  - ```cpp
        // res = (res.size() >= dp[j][j + i]) ? res : s.substr(j, i + 1);
        if (res.size() < dp[j][j + i]) {
            res = s.substr(j, i + 1);
        }
    //第一行注释的语句，用了会超时，而第二第三行则不会，
    ```

  - 我认为，可能是第一行编译的时候会耗费更多的时间，导致时间太长了