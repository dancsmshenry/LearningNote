# 为什么这些SQL语句逻辑相同，性能却差异巨大？



### 条件字段函数操作

- 如果对字段做了函数计算，就用不上索引了
- 因为B+树的索引是从左往右开始计算遍历的，如果当前的逻辑是针对索引中特定部分的值进行查询的话，就会用不上索引
- 也就是说，对索引字段做函数操作，可能会破坏索引值的有序性，因此优化器就决定放弃搜索功能，变为全索引扫描
- 但是优化器还是可以选择遍历主键索引，或者遍历其他索引



- 不过优化器在个问题上确实有“偷懒”行为，即使是对于不改变有序性的函数，也不会考虑使用索引。比如，对于 select * from tradelog where id + 1 = 10000 这个 SQL 语句， 这个加 1 操作并不会改变有序性，但是 MySQL 优化器还是不能用 id 索引快速定位到 9999 这一行。所以，需要你在写 SQL 语句的时候，手动改写成 where id = 10000 -1 才可以





### 隐式类型转换

- 数据库的数据类型的转换

  - 比如说"10" > 9
  - 数据库是将字符串转换为数字

- 背景：

  - ```sql
    select * from tradelog where tradeid = 110717;
    ```

  - PS：这里的tradeid是一个字符串，也就是用字符串建的索引

  - 对于优化器来说就是

  - ```sql
    select * from tradelog where CAST(tradid AS signed int) = 110717;
    ```

  - 这里就变成了对索引字段做函数操作，优化器就会因此放弃走B+树搜索功能





### 隐式字符编码转换

- 字符集不同只是条件之一，连接过程中要求在被驱动表的索引字段上加函数操作，是直接导致对被驱动表做全表扫描的原因
- 解决：
  - 统一字符集
  - 或者修改sql语句





### 小结

- 对索引字段做函数操作，可能会破坏索引值的有序性，因此优化器就决定放弃走树搜索功能