# 权限管理

chmod +x run.sh
- 当前shell脚本因权限无法执行，使用该指令修改权限

<br/>

<br/>

<br/>

# 文件夹的操作

```shell
# 重命名文件夹
mv oldname newname

# 删除文件夹
rm -rf foldername

# 新建文件夹
mkdir foldername
mkdir -p foldername/foldername # 可以递归的创建文件夹

# 复制文件夹
# 左边是源文件，右边是目标文件夹（从源文件夹移动到目标文件夹）
cp -r /usr/bin/toml11* /test/ 

# 进入文件夹
cd foldername

# 查看文件夹下的文件
ls
ls -a # 能够同时查看隐藏文件

# 查看当前文件夹中文件的所有详细信息
l
```

<br/>

<br/>

<br/>

# 文件的操作

```shell
# 打开文件
vim test.cc

# 删除文件
rm filename
rm -f filename # 强制删除文件
find ./ -name "*.o" | xarg rm -rf # 删除.o后缀类型的文件

# 解压文件
tar xzf filename # 解压.tar文件
tar -zxvf filename # 解压.tar.gz文件

# 下载文件
wget xxxx

# 将文件复制到某个路径下
cp filename path
```

<br/>

<br/>

<br/>

# 关于进程的操作

```shell
# 列出与本次登录有关的进程信息
ps -l

# 查询内存中进程信息
ps -aux

# 查询***进程的详细信息
ps -aux | grep ***

# 查看内存中进程的动态信息
top

# 杀死进程
kill -9 pid

# 动态显示内存中的进程信息
top

# 查看指定用户的进程
top -u [用户名]
```

<br/>

<br/>

<br/>

# 关于应用程序的安装

```shell
# 第一种，需要安装某些静态库，比如 protobuf，则可以使用 pip
pip install protobuf==3.16.0 # 后面可以选择安装指定库
pip uninstall protobuf # 卸载库

# 第二种，需要安装 gcc 、或是 cmake，则需要使用 apt
sudo apt-get install cmake # 后面添上需要安装的应用程序

# 安装 j
apt-get install openjdk-11-jdk
```

<br/>

<br/>

<br/>

# 其他

```shell
pwd # 会显示当前所在的路径

cd .. # 返回前一个文件夹

!! # 重复上一次命令

strace -p pid # 可以查看当前进程用到了哪些系统调用
```

<br/>

发现Unable to locate package的问题

- 可能是软件源发生了更替
- 解决：先`sudo apt-get update`，`sudo apt-get install`

<br/>

如何退出conf文件

- Ctrl + x

<br/>

wrk安装时出现的问题

- https://blog.csdn.net/GMCN__/article/details/119491365

<br/>

https://sourceforge.net/p/boost/activity/?page=0&limit=100#64d394b2d747e69e43894463

在 linux 主机无法联网时，使用该网站下载 boost 包

<br/>

<br/>

<br/>

# WSL

wsl的安装：应用商店安装即可

换源：https://blog.csdn.net/weixin_45941288/article/details/122568131

在安装g++的时候出现问题，https://blog.csdn.net/qq_35553433/article/details/112994517

<br/>

## 如何在wsl上访问windows的文件

首先进入 WSL，然后进根目录/，使用ls可以看到一个名为mnt的目录（mnt 是 mount 加载的缩写）

在这里可以看到各种盘，例如c表示 C 盘，d表示 D 盘

然后我们就可以进入不同的盘来对文件进行操作了

<br/>

## wsl和vscode的配置

好像不需要怎么配置...，直接下载好vscode的插件remote-ssh，remote-wls即可

插件那里切换过去即可

需要安装一些插件，还需要切换到阿里源，同时更新一些配置

```shell
sudo sed -i s@/archive.ubuntu.com/@/mirrors.aliyun.com/@g /etc/apt/sources.list
sudo apt update -y
sudo apt upgrade -y

//	安装gcc和gdb，还有 cmake
sudo apt-get install gdb
sudo apt-get install g++
sudo apt-get install cmake
```

<br/>

<br/>

<br/>

如何安装 boost 

```shell
sudo apt-get update
sudo apt-get install libboost-all-dev
```

<br/>

<br/>

<br/>

## 安装wsl后可能导致windows的gcc出现红线

有可能是修改了gcc的路径

去`c_cpp_properties.json`路径下查找`"compilerPath": "D:\\Cpp\\TDM-GCC-64\\bin\\gcc"`即可