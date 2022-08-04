# 最左前缀原则

- 就是多个索引组成了联合索引后，如果想要在查询的时候用上索引，就必须要带上做左边的索引元素（即第一个索引元素）
- 同时这个联合索引，是先对第一个位置的元素进行排序，如果相同的话就比较第二个元素的大小，接着依次比较下去



# 创建索引的原则

- (区分度，是否是查询时使用，插入性能和读取性能权衡，减少回表)



# 参考

- to read list

  - https://www.pudn.com/news/628f83e8bf399b7f351ec2bf.html
- https://zhuanlan.zhihu.com/p/40777145
  - https://blog.csdn.net/qq_33329834/article/details/109569199
- https://zhuanlan.zhihu.com/p/40779118