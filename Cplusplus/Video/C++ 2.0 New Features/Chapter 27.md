# 容器-结构与分类_ 旧与新的比较 _ 关于实现手法

- 注意：把一个对象当作了右值，进行了move construct，就不能用这个资源了
- sequence containers
  - array(cpp11)
  - vector
  - deque
  - list(双向链表)
  - forward-list(cpp11，单向链表)
- assoviative containers
  - set/multiset
  - map/multimap
- unordered containers(cpp11)
  - unordered set/multiset
  - unordered map/multimap
