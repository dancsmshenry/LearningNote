# 背景

- ftp、pop和telnet都是不安全的，因为它们都是用明文传送口令和数据
- 同时容易出现中间人攻击的情况







# 定义

- Secure Shell（安全外壳协议，简称SSH）是一种加密的网络传输协议，可在不安全的网络中为网络服务提供安全的传输环境
- SSH通过在网络中创建安全隧道来实现SSH客户端与服务器之间的连接
- SSH最常见的用途是远程登录系统，人们通常利用SSH来传输命令行界面和远程执行命令。SSH使用频率最高的场合是类Unix系统，但是Windows操作系统也能有限度地使用SSH
- SSH以非对称加密实现身份验证。身份验证有多种途径：
  - 例如其中一种方法是使用自动生成的公钥-私钥对来简单地加密网络连接，随后使用密码认证进行登录
  - 另一种方法是人工生成一对公钥和私钥，通过生成的密钥进行认证，这样就可以在不输入密码的情况下登录。任何人都可以自行生成密钥。公钥需要放在待访问的电脑之中，而对应的私钥需要由用户自行保管。认证过程基于生成出来的私钥，但整个认证过程中私钥本身不会传输到网络中
- SSH协议有两个主要版本，分别是SSH-1和SSH-2。无论是哪个版本，核实未知密钥来源都是重要的事情，因为SSH只验证提供用户是否拥有与公钥相匹配的私钥，只要接受公钥而且密钥匹配服务器就会授予许可。这样的话，一旦接受了恶意攻击者的公钥，那么系统也会把攻击者视为合法用户
- 还有一个好处就是数据都是被压缩了的