## list

### 用法

- ```cpp
  //四种构造函数
  list<string> list1{"why", "always", "me", "!"};
  list<string> list2(list1.begin(), list1.end());
  list<string> list3(list1);
  list<string> list4(4, "you");
  
  // operator=
  list<string> list5 = list1;
  
  // assign将值赋给容器（会覆盖掉原来的值）
  list1.assign({1, 2, 3, 4, 5});            //插入initializer_list
  list1.assign(10, 1111);                   //第一个是数量，第二个是value
  list7.assign(list1.begin(), list1.end()); //放入一个容器
  
  // front返回第一个元素，back返回最后一个元素
  
  // iterator和revers_iterator，正向迭代器和反向迭代器
  for (list<string>::iterator it = list1.begin(); it != list1.end(); it++)
  {
      cout << *it << " ";
  }
  for (list<string>::reverse_iterator it = list1.rbegin(); it != list1.rend(); it++)
  {
      cout << *it << " ";
  }
  
  // empty判断容器是否为空，size返回大小，max_size返回容器的最大的容量
  
  // clear清除所有内容
  
  // insert插入元素
  list7.insert(list7.begin(), "hello");                    //指定位置插入元素
  list7.insert(list7.begin(), 2, "no");                    //指定位置插入一定数量的元素
  list7.insert(list7.begin(), list6.begin(), list6.end()); //指定位置插入容器元素
  
  // erase删除指定位置的元素，ps：advance(range_begin, 2)使得迭代器向后移动数个位置
  list.erese(list.begin());                       //删除指定位置的元素
  list.erase(list.begin() + 2, list.begin() + 5); //删除区域间的元素
  
  // push_back，pop_back，push_front,pop_front
  
  // resize重新设定链表的大小，swap交换链表元素，sort排序，merge合并两个链表
  list9.merge(list8);
  
  // splice分割链表
  auto it = list11.begin();
  advance(it, 2);
  list11.splice(it, list12); //把链表的前两个给删除掉
  
  // remove移除满足特定标准的元素
  list12.remove(5);
  
  // reverse将该链表的所有元素的顺序反转
  list12.reverse();
  
  // unique删除连续的重复的元素
  list11.unique();
  
  // emplace_back在容器末尾就地构造元素
  ```



### 实现

#### list节点

- 三个指针（一个指向前面节点的指针，一个指向后面节点的指针和一个指向数据的指针）
- ![](image\list的节点.png)



#### list迭代器

- 一个指针（指向listnode节点）
- ![](image\list迭代器.png)



#### list

- 一个指针（指向链表的第一个节点）
- <img src="image\list.png" style="zoom:150%;" />

- 是结点组成的环形链表
  - ![](image\list环形链表.png)
- 空链表的情况
  - ![](image\空链表.png)





#### 在当前的编译器中的大小

- 在现在的编译器中，list已经是24（3*8，即三个指针了）,list_node不变
- ![](image\list_1.png)\
- ![](image\list_2.png)







### size

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
  
      /* 遍历列表获取 __n*/
      typename iterator_traits<_InputIterator>::difference_type __n = 0;
      while (__first != __last) {
          ++__first;
          ++__n;
      }
      return __n;
  }
  ```

- 在cpp11后保证了是O（1）

- 原因：

  - STL中的链表是支持splice方法的。在做splice的时候我们无法预先知道被插入的链表会变大多少，被移除的链表会减少多少，除非循环遍历被splice的区间。但是一般来讲我们希望splice的时间复杂度是常数时间的，所以老版本的实现size()时选择了每次循环遍历。新版本改成常数时间是有代价的，就是splice这个方法每次都要循环遍历区间来维护两个链表的大小，这个方法就废掉了
