# Webbench

```shell
wget http://home.tiscali.cz/~cz210552/distfiles/webbench-1.5.tar.gz
tar zxvf webbench-1.5.tar.gz
cd webbench-1.5
make && make install
```



原理

- Webbench 首先 fork 出多个子进程，每个子进程都循环做 web 访问测试。子进程把访问的结果通过pipe 告诉父进程，父进程做最终的统计结果



webbench的用法

```shell
 ./webbench -c 1000 -t 30 网址
```

参数：-c 表示客户端数 -t 表示时间



缺点
1.不适合中大型网站测试；
2.其并发采用多进程实现并非线程，长时间其会大量占用内存与CPU，所以一般长时间的压力测试不推荐使用webbench



https://blog.csdn.net/L_XRUI/article/details/76216079





# Iperf





# callgrind