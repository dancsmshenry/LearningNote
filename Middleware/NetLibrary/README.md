muduo一些可以优化的地方：

比如说每次修改channel的状态的时候，不一定非得调用epoll_ctl

而是用一个标志位记录当前channel的状态

比如说要让channel关注可读事件，而channel本身就已经关注了可读事件（通过标志位得知的），那么就不需要调用epoll_ctl

减少对系统调用的调用次数



有些不是很懂的地方：channel的tie到底是干什么的？buffer是如何实现的

https://www.nowcoder.com/discuss/post/353148000237199360