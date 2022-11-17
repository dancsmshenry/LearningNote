# 答疑文章（一）：日志和索引相关问题



### 日志相关问题

崩溃恢复时的判断规则

- 如果redo log里面的事务是完整的，也就是已经有了commit标识，则直接提交
- 如果redo log里面的事务只有完整的prepare，则判断对应的事务 binlog 是否存在并完整： 
  - 如果是，则提交事务
  - 否则，回滚事务



binlog的格式

- 一个事务的binlog是有完整格式的
  - statement 格式的 binlog，最后会有 COMMIT
  - row 格式的 binlog，最后会有一个 XID event
- MySQL5.6.2版本以后，还引入binlog-checksum参数，用来验证binlog内容的正确性
- 对于 binlog 日志由于磁盘原因，可能会在日志中间出错的情况
- MySQL 可以通过校验 checksum 的结果来发现



redo log和 bin log的关联

- 这两个日志有一个共同的数据字段，叫作XID，崩溃恢复的时候，会按顺序扫描redo log
  - 如果碰到既有 prepare、又有 commit 的 redo log，就直接提交
  - 如果碰到只有 parepare、而没有 commit 的 redo log，就拿着 XID 去 binlog 找对应的事务



redo log的大小

- 如果是常见的TB磁盘的话，就将redo log设置为几个文件，每个文件1GB