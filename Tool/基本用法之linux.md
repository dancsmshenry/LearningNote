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

- 解压.tar文件
  - `tar xzf file_name`

- 解压tar.gz文件
  - `tar -zxvf file_name`








# 下载文件

- `wget download_url`



## 库的安装

- 很多时候，某些库（protobuf）是可以用pip进行安装和卸载的
- pip install protobuf==3.16.0（指定版本安装）
- pip uninstall protobuf（卸载库）





# Others

- 返回前一个文件夹：cd ..
- 重复上一次命令：!!
- strace -p pid（可以查看当前进程用到了哪些系统调用）







# to do list

- xargs学习
- linux常用命令
- 如何找到文本中首字母大写的所有行
- nmap，linux下网络扫描和嗅探的工具