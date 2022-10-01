# 进入文件夹

- `cd filefolder_name`







# 用vim打开文件

- `vi test.cpp`







# 查看文件

- 普通的查看文件：`ls`
- 查看隐藏文件：`ls -a`







# 删除文件（文件夹）

- `rm -rf 文件夹`，删除文件夹
- `rm -f 文件名`，删除单个文件
- `rm -r 文件名`，递归删除，不管有多少个文件，全部删除
- `find ./ -name "*.o" | xarg rm -rf`，删除某种后缀类型的文件（这里是删除所有后缀为o的文件）







# 解压文件

- `tar xzf file_name`







# 下载文件

- `wget download_url`







# Others

- 返回前一个文件夹：cd ..
- 重复上一次命令：!!
- strace -p pid（可以查看当前进程用到了哪些系统调用）







# to do list

- xargs学习
- linux常用命令
- 如何找到文本中首字母大写的所有行
- nmap，linux下网络扫描和嗅探的工具