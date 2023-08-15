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

