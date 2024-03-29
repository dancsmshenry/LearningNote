# 日志系统：一条SQL更新语句是如何执行的？



### WAL技术

- Write-Ahead Logging，先写日志，再写磁盘
- 当有一条记录需要更新的时候，InnoDB 引擎就会先把记录写到 redo log（粉板）里面，并更新内存，这个时候更新就算完成了
- 同时，InnoDB 引擎会在适当的时候， 将这个操作记录更新到磁盘里面，而这个更新往往是在系统比较空闲的时候做，这就像打烊以后掌柜做的事





### crash-safe

- redo log保证了crash-safe的能力





### binlog和redo log的区别

- redo log是**InnoDB引擎**特有的；binlog是**MySQL的Server层**实现的，所有引擎都可以使用
- redo log 是物理日志，记录的是“在某个数据页上做了什么修改”，有哪些数据的修改；binlog 是逻辑日志，记录的是这个语句的原始逻辑，比如“给 ID=2 这一行的 c 字段加 1 ”
- redo log 是循环写的，空间固定会用完；binlog 是可以追加写入的。“追加写”是指binlog 文件写到一定大小后会切换到下一个，并不会覆盖以前的日志





### 执行语句

```sql
update T set c = c + 1  where ID=2;
```

- 执行器先找引擎取ID=2这一行，ID是主键，引擎直接用树搜索找到这一行
- 如果ID=2这一行所在的数据页本来就在内存中，就直接返回给执行器；否则就需要先从磁盘读入内存，然后再返回
- 执行器拿到引擎给的行数据，把这个值加上1，比如原来是N，现在就是N+1，得到新的一行数据，在调用引擎接口写入这行新数据
- 引擎讲这行新数据更新到内存中，同时将这个更新操作记录到redo log里面，此时redo log处于prepare状态，然后告知执行器执行完成了，随时可以提交事务
- 执行器生成这个操作的binlog，然后把binlog写入磁盘
- 执行器调用引擎的提交事务接口，引擎把刚刚写入的redo log改成提交状态，更新完成
- <img src="image/update语句执行流程.png" style="zoom:150%;" />
- 注意：这里最后将redo log的写入拆成了两个步骤：prepare和commit，这就是两阶段提交





### 两阶段提交

- 不使用两阶段提交的原因：
- <img src="image/两阶段提交.png" style="zoom:150%;" />





### 补充

- Binlog有两种模式，statement 格式的话是记sql语句， row格式会记录行的内容，记两条，更新前和更新后都有
- 为什么使用innodb的时候还保留两种日志
  - redolog只有InnoDB有，别的引擎没有
  - redolog是循环写的，不持久保存，binlog的“归档”这个功能，redolog是不具备的