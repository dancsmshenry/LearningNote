**有关 cpp 的 io 流**



对于一个 fstresm，如果读完了所有的内容，也就是读到了 eof，那么此时 iosstate 就会被设置为 failbit，后续再 seekg，是不会生效的

因为流内部会认为这个流失效了，需要用 clear 重置一下。



所以，需要对 cpp 的 stream 重新认识一下，很多客户其实也不懂这方面的知识。

https://zhuanlan.zhihu.com/p/117306283



o_trunc 表示将文件打开后，其中的内容都清空

o_wronly 表示以只写权限打开文件

o_rdonly 表示以只读权限打开文件

o_rdwr 表示既可以写文件，也可以读文件

o_create 表示如果文件不存在，则创建文件

o_excl 和 o_create 一起使用，表示如果文件以存在，则会返回打开失败

o_cloexec 表示子进程中不会继承父进程的 fd，避免多进程导致的问题

o_append 表示打开文件进行写入操作的时候，会从文件的末尾开始写

权限 644 表示用户组可读可写该文件



fstream，fopen

- 向一个二进制文件尾部添加数据，则该文件的打开方式是ios_base::app

