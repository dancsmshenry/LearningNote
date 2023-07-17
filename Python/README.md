# 某些github项目中，python代码无运行

可能是它开头写了`#!/bin/python`，导致windows下无法运行代码

- python作为脚本语言，所以可以在代码中执行shell类的脚本，有点小坑....

<br/>

<br/>

<br/>

# python库的安装方法

方法一：pip install 库名

- 或者，pip install --upgrade 库名

方法二：pycharm 中，在python的设置中直接安装

方法三：去**https://pypi.org/project/snownlp/**上下载原文件

文件是tar类型时的安装：

<img src="F:\Code\LearningNote\Tool\image\python库的安装.png" style="zoom:150%;" />

文件是whl类型时的安装：

- 先安装 pip install wheel
- 然后安装 .whl 文件 pip install 路径\文件名.whl
  - 例如放在D盘根目录时安装： pip install D:\\文件名.whl

<br/>

<br/>

<br/>

# 解决：/usr/bin/env: ‘python’: No such file or directory

背景：运行python脚本的时候报错，但本地的确有python

解决办法：

- 为其创建符号连接
- 先用``whereis python`指令查询当前的python安装的位置
- 然后用`sudo ln -s 上面得到的python的地址 /usr/bin/python`
- 比如我的python安装的位置是/usr/bin/python3.8，所以指令就是`sudo ln -s /usr/bin/python3.8 /usr/bin/python`

