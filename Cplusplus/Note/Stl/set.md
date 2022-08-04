## set

### 用法

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



### emplace和insert效率的问题

- emplace的一般实现是用的args去创建（构造）一个新的对象，然后将这个对象去实施真正的insert操作。可是这里用的unordered_set,那么很可能因为不能出现重复key的原因出现拒绝添加，那么就会析构这个对象，这样这个构造+析构的操作就是浪费的了
- 而这里的insert只会在发现可以添加的时候才创建一个对象，因此少了对象的构造和拷贝
- 参考《Effective Modern C++》条款42
- 因此emplace在vector，list等容器上效率会高很多，因为新增元素的位置与元素本身无关
- 而set，map等容器需要依据元素本身的比较结果才能确定插入位置，因此无论如何都要先构造出元素，确定位置后才能把元素移过去





## unordered_set

- 底层是哈希表实现



# 坑

- https://leetcode.cn/problems/permutations-ii/solution/c-hui-su-setqu-zhong-by-zhang-jian-qi-sh-d3zu/
- 说是对于vector<int>，unordered_set无法实现去重的功能，而set才可以，后续要研究一下



