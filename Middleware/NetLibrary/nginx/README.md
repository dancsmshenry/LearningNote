安装

```shell
sudo apt-get install libpcre3-dev // 安装prcre库，解析正则表达式
sudo apt-get install libz-dev //	安装zlib库，压缩解压功能
sudo apt-get install libssl-dev	//	安装openssl库，ssl功能相关库，用于网站加密通讯
```



- mainline版本：版本号中间数字一般为奇数。更新快，一个月内就会发布一个新版本，最新功能，bug修复等，稳定性差一点

- stable版本：稳定版，版本号中间数字一般为偶数。经过了长时间的测试，比较稳定，商业化环境中用这种版本；这种版本发布周期比较长，几个月

- Legacy版本：遗产，遗留版本，以往的老版本



- 安装，现在有这种二进制版本：通过命令行直接安装

-  灵活：要通过编译 nginx源码手段才能把第三方模块弄进来



- auto / :编译相关的脚本，可执行文件configure一会会用到这些脚本
  - cc / : 检查编译器的脚本
  - lib / : 检查依赖库的脚本
  - os / : 检查操作系统类型的脚本
  - type / : 检查平台类型的脚本

- CHANGES : 修复的bug，新增加的功能说明

- CHANGES.ru : 俄语版CHANGES

-  conf / : 默认的配置文件

- configure : 编译nginx之前必须先执行本脚本以生成一些必要的中间文件（执行脚本，配置环境，会产生中间文件）

- contrib / : 脚本和工具，典型的是vim高亮工具
  - vim / : vim高亮工具

- html / : 欢迎界面和错误界面相关的html文件（缺省页面）

- man / : nginx帮助文件目录

- src / : nginx源码目录

  - core : 核心代码

  - event : event(事件)模块相关代码

  - http : http(web服务)模块相关代码

  - mail : 邮件模块相关代码

  - os : 操作系统相关代码

  - stream : 流处理相关代码

- objs/:执行了configure生成的中间文件目录

- ngx_modules.c：内容决定了我们一会编译nginx的时候有哪些模块会被编译到nginx里边来。

- Makefile:执行了configure脚本产生的编译规则文件，执行make命令时用到





第一步：

```shell
./configure // 执行脚本检查配置;会多了一个obj文件，存放中间文件
```

可能遇到权限不够的问题：

```shell
chmod +x  xampp.run #给xampp.run执行权限
chmod +w xampp.run #给xampp.run写权限
chmod +r  xampp.run #给xampp.run读权限
```



第二步：

```shell
make // 生成可执行文件
sudo make install // 安装到目录中
```



安装后得到的nginx是在usr/local/nginx/sbin的文件夹中，后续执行sudo ./nginx即可运行nginx



nginx的压测信息

```shell
root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/http_load-12mar2006# http_load -p 9000 -s 30 test.txt
354960 fetches, 28 max parallel, 2.17236e+08 bytes, in 30.0003 seconds
612 mean bytes/connection
11831.9 fetches/sec, 7.2411e+06 bytes/sec
msecs/connect: 0.217255 mean, 10.231 max, 0.038 min
msecs/first-response: 0.845237 mean, 10.231 max, 0.492 min
HTTP response codes:
  code 200 -- 354960
  


root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/http_load-12mar2006# http_load -p 8000 -s 30 test.txt
357730 fetches, 28 max parallel, 2.18931e+08 bytes, in 30.0005 seconds
612 mean bytes/connection
11924.1 fetches/sec, 7.29757e+06 bytes/sec
msecs/connect: 0.214411 mean, 10.001 max, 0.033 min
msecs/first-response: 0.838712 mean, 10.001 max, 0.467 min
HTTP response codes:
  code 200 -- 357730


root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/http_load-12mar2006# http_load -p 8000 -s 30 test.txt
358070 fetches, 539 max parallel, 2.19139e+08 bytes, in 30 seconds
612 mean bytes/connection
11935.7 fetches/sec, 7.30462e+06 bytes/sec
msecs/connect: 0.285334 mean, 1009.84 max, 0.033 min
msecs/first-response: 2.07025 mean, 39.185 max, 0.382 min
HTTP response codes:
  code 200 -- 358070


root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/http_load-12mar2006# http_load -p 7000 -s 30 test.txt
363920 fetches, 38 max parallel, 2.22719e+08 bytes, in 30 seconds
612 mean bytes/connection
12130.7 fetches/sec, 7.42396e+06 bytes/sec
msecs/connect: 0.209392 mean, 5.656 max, 0.03 min
msecs/first-response: 0.824586 mean, 5.656 max, 0.484 min
HTTP response codes:
  code 200 -- 363920


root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/http_load-12mar2006# http_load -p 6000 -s 30 test.txt
415355 fetches, 291 max parallel, 2.54197e+08 bytes, in 30 seconds
612 mean bytes/connection
13845.2 fetches/sec, 8.47324e+06 bytes/sec
msecs/connect: 0.315024 mean, 5.813 max, 0.026 min
msecs/first-response: 14.2426 mean, 27.017 max, 0.577 min
HTTP response codes:
  code 200 -- 415355



root@iZuf69fsi3ctdtj4ys7h0mZ:/github_project/http_load-12mar2006# http_load -p 5500 -s 30 test.txt
415860 fetches, 323 max parallel, 2.54506e+08 bytes, in 30.0007 seconds
612 mean bytes/connection
13861.7 fetches/sec, 8.48334e+06 bytes/sec
msecs/connect: 0.32222 mean, 7.052 max, 0.024 min
msecs/first-response: 15.6691 mean, 33.278 max, 0.583 min
HTTP response codes:
  code 200 -- 415860
```





关闭nginx

```shell
kill -QUIT 340157 // 340157w，太粗暴
sudo ./nginx -s quit //	y
```



查看nginx的相关进程

```shell
ps -ef | grep nginx
```

