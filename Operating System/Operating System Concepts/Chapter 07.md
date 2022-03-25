# 7.2 死锁特征

7.2.1 必要条件

- 互斥：至少有一个资源必须处于非共享模式，即依次只有一个进程可使用。如果另一进程申请该资源，那么申请进程应等到该资源释放为止
- 占有与等待：一个进程应占有至少一个资源，并等待另一个资源，而该资源为其他进程所占有
- 非抢占：资源不能被抢占，即资源只能被进程在完成任务后资源释放
- 循环等待：有一组进程等待的，P0被P1占有，P1等待的资源被P2占有，Pn-1等待的资源被Pn占有，Pn等待的资源为P0占有
- 四个条件必须同时成立才会出现死锁



7.2.2 资源分配图





# 7.3 死锁处理方式

三种方法：

- 通过协议来预防或避免死锁，确保系统不会进入死锁状态
- 可以允许系统进入死锁状态，然后检测它，并加以恢复
- 可以忽视这个问题，认为死锁不可能在系统内发生



- 死锁预防：确保至少有一个必要条件不成立
- 死锁避免：操作系统先得到有关进程申请资源和使用资源的额外信息，有了这些额外信息，系统可以确认：对于每个申请，进程是否应该等待
- 系统提供一个算法来检查系统状态以确定死锁是否发生