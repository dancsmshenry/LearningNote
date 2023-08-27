# 批量修改文件名

新建txt文件，修改一下内容后更改后缀为bat

```bash
ren *.gif *.jpg
```

重命名命令，需要修改的文件类型，修改后的文件类型

<br/>

<br/>

<br/>

# chrome67 版本后无法拖拉安装 crx 插件

https://huajiakeji.com/utilities/2018-09/1525.html

<br/>

<br/>

<br/>

# Gitee：Your push would publish a private email address.

背景：gitee的一个报错（之前做douyin项目的时候遇到的）

去gitee或github中把下面的邮箱的选项叉掉即可

<img src="F:\Code\LearningNote\Tool\image\1.png" style="zoom: 200%;" />

<br/>

<br/>

<br/>



# windows下系统变量无法展开

可能是把 %JAVA_HOME%\bin 和 %JAVA_HOME%\bin 一起放在了 Path 开头，导致不能展开

解决办法，把 % 开头的系统变量放到后面，不要放在第一位

<br/>

<br/>

<br/>

# jdk的下载

https://injdk.cn

<br/>

<br/>

<br/>

# rust 的安装

```shell
curl https://sh.rustup.rs -sSf | sh	//	输入后按空格即可
source $HOME/.cargo/env //	配置系统变量
chmod +x $HOME/.cargo/env	//	如果上一条指令的权限不够，就chmod权限
rustc --version	//	查看rust的版本
```

<br/>

<br/>

<br/>

# pandoc 使用出现的问题

使用 pandoc 的时候，是先将 markdown 转换成 latex，然后再将 latex 转成 pdf 的

因此可能会爆出以下错误 ! File ended while scanning use of \@newl@bel

有时候我们使用latex时，之前出现了错误我们已经修改好了，但是再次编译的时候出现如下这种错误，这个主要使用因为上次使用latex编译时生成的.aux文件影响了这次的latex编译，我们在文件目录中将   正在编译的文件名.aux  这个文件直接删除即可

也就是将该 aux 文件或是之前编译的错误删除即可
