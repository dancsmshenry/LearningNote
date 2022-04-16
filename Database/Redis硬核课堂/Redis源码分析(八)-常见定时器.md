- 在单线程的reactor模式下，当io多路复用时，但当前的事件还没有处理完（本轮epoll返回的fd事件），而后新的定时任务又到达（比如说下一轮epoll返回的fd事件又来了），应该如何处理





# 参考

- https://hardcore.feishu.cn/docs/doccnONjCnzPSyvEIrRumMZThWh#