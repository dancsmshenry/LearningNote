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



# 应用程序的安装

- `sudo apt-get install cmake`，最后填需要安装的应用程序



## gcc的安装

- `sudo apt install gcc`安装gcc
- `gcc -v`查看gcc版本
- 如果失败了，可能需要更新一下`sudo apt-get install update`





## vim常用

- 



## 查看进程信息

  ps -l  列出与本次登录有关的进程信息；
ps -aux   查询内存中进程信息；
ps -aux | grep ** *    查询  ***  进程的详细信息
  top  查看内存中进程的动态信息；
  kill -9 pid  杀死进程。

top 动态显示内存中的进程信息（top）



# Others

- 返回前一个文件夹：cd ..
- 重复上一次命令：!!
- strace -p pid（可以查看当前进程用到了哪些系统调用）



发现Unable to locate package的问题

- 可能是软件源发生了更替
- 解决：先`sudo apt-get update`，`sudo apt-get install`



如何退出conf文件

- Ctrl + x



wrk安装时出现的问题

- https://blog.csdn.net/GMCN__/article/details/119491365







# WSL

wsl的安装：应用商店安装即可



## 如何在wsl上访问windows的文件

- 首先进入 WSL，然后进根目录/，使用ls可以看到一个名为mnt的目录（mnt 是 mount 加载的缩写）
- 在这里可以看到各种盘，例如c表示 C 盘，d表示 D 盘
- 然后我们就可以进入不同的盘来对文件进行操作了



## wsl和vscode的配置

- 好像不需要怎么配置...，直接下载好vscode的插件remote-ssh，remote-wls即可

- 插件那里切换过去即可

- 需要安装一些插件，还需要切换到阿里源，同时更新一些配置

- ```shell
  sudo sed -i s@/archive.ubuntu.com/@/mirrors.aliyun.com/@g /etc/apt/sources.list
  sudo apt update -y
  sudo apt upgrade -y
  
  //	安装gcc和gdb
  sudo apt-get install gdb
  sudo apt-get install g++
  ```

- 



## 安装wsl后可能导致windows的gcc出现红线

- 可能是修改了gcc的路径
- 去`c_cpp_properties.json`路径下查找`"compilerPath": "D:\\Cpp\\TDM-GCC-64\\bin\\gcc"`即可



# to do list

- xargs学习
- linux常用命令
- 如何找到文本中首字母大写的所有行
- nmap，linux下网络扫描和嗅探的工具