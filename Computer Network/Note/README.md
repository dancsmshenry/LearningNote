# Computer Networks Note

- 应用层：HTTP，HTTPS，DNS，DHCP
- 传输层：TCP，UDP
- 网络层：IP，ARP，RARP







###### 基于计网五层模型的理解

- 应用层
  - 即我们使用的应用所在的层级。对于前一层传来的信息（传输层将信息传给应用层），遵循一定的规则（http、https、ftp等协议），然后顺利的基于规则对信息进行加工处理，最后拿给客户端的相关引用程序（浏览器，桌面端应用，app等）渲染
  - 所以我觉得该层级最重要的是要学习有关**https等相关协议**的相关规则，知道应用层是如何对我们的信息进行加工处理的，出现错误时是如何勘误报错的（当然，这对爬虫来说应该是最重要的一个关键点）
  - 相关知识点：
    - 状态码
    - 相关报文的字段
    - get和post请求的区别
    - http的优缺点
    - cookie和session
    - https，ssl（加密方式）
- 传输层
  - 对，可是每个客户端上面都会有很多很多的应用，那该怎么传输数据呢？答案就是引入传输层，ip地址和端口号
  - 那信息到底是如何传递的呢？这里就用两种协议来传输，**tcp和udp**
  - 注：协议其实是对当前的信息进行打包处理，然后利用计网的抽象出来的分层把信息丢给下一层（思想是真的牛皮）
- 网络层
  - 那你把信息给我了，我应该把信息传给你的目的主机是吧，可我能直接到你的目的主机吗？很难的啦，所以一定是要想快递一样的先传给你，再传给你，最后传给你。网络层干的就是这件事情，而这件事就是要依靠**ip协议来进行**
- 数据链路层
  - 那么你都想好了信息是传球一样的传来传去的，那两个人之间是要怎么传输的呢？这就是数据链路层的问题了
- 物理层
  - 脱离抽象，靠近实物的信息传输层面





# 女巫攻击

传统互联网领域

- 模拟出多种身份进行攻击，生活中常见的就是多个ip地址刷流量，刷赞
- 再比如说：电商平台操纵多个消耗刷单，抢购软件冒充多人实施抢购
- 解决办法：采用可靠的第三方进行验证（实名认证）



区块链领域

- 投票时生成多个地址刷票，诸如矿工挖矿的记账权、token空投、DAO决策等等
- 原因：区块链以钱包地址定义为一个用户
- 解决办法：工作量证明、资产证明、行为证明等等



# 12、一个TCP连接可以对应几个HTTP请求？ 

如果维持连接，一个 TCP 连接是可以发送多个 HTTP 请求的。





# 13、一个 TCP 连接中 HTTP 请求发送可以一起发送么（比如一起发三个 请求，再三个响应一起接收）？

- HTTP/1.1 存在一个问题，单个 TCP 连接在同一时刻只能处理一个请求，意思是说：两个请求的生命周 期不能重叠，任意两个 HTTP 请求从开始到结束的时间在同一个 TCP 连接里不能重叠
- 在 HTTP/1.1 存在 Pipelining 技术可以完成这个多个请求同时发送，但是由于浏览器默认关闭，所以可以 认为这是不可行的。在 HTTP2 中由于 Multiplexing 特点的存在，多个 HTTP 请求可以在同一个 TCP 连 接中并行进行。 
- 那么在 HTTP/1.1 时代，浏览器是如何提高页面加载效率的呢？主要有下面两点： 
  - 维持和服务器已经建立的 TCP 连接，在同一连接上顺序处理多个请求。 
  - 和服务器建立多个 TCP 连接。



浏览器对同一 Host 建立 TCP 连接到的数量有没有限制？

- 假设我们还处在 HTTP/1.1 时代，那个时候没有多路传输，当浏览器拿到一个有几十张图片的网页该怎 么办呢？肯定不能只开一个 TCP 连接顺序下载，那样用户肯定等的很难受，但是如果每个图片都开一 个 TCP 连接发 HTTP 请求，那电脑或者服务器都可能受不了，要是有 1000 张图片的话总不能开 1000  个TCP 连接吧，你的电脑同意 NAT 也不一定会同意。 有。Chrome 最多允许对同一个 Host 建立六个 TCP 连接。不同的浏览器有一些区别。 如果图片都是 HTTPS 连接并且在同一个域名下，那么浏览器在 SSL 握手之后会和服务器商量能不能用 HTTP2，如果能的话就使用 Multiplexing 功能在这个连接上进行多路传输。不过也未必会所有挂在这个 域名的资源都会使用一个 TCP 连接去获取，但是可以确定的是 Multiplexing 很可能会被用到。 如果发现用不了 HTTP2 呢？或者用不了 HTTPS（现实中的 HTTP2 都是在 HTTPS 上实现的，所以也就 是只能使用 HTTP/1.1）。那浏览器就会在一个 HOST 上建立多个 TCP 连接，连接数量的最大限制取决 于浏览器设置，这些连接会在空闲的时候被浏览器用来发送新的请求，如果所有的连接都正在发送请求 呢？那其他的请求就只能等等了。





# OSI模型

- 应用层

  - 更像是在做系统
  - 为应用程序提供服务并规定应用程序中通信相关的细节，包括文件传输、电子邮件、原创登录等协议
- 表示层

  - 是把数据转化成一种能够在网络中传输的数据格式
  - 将应用处理的信息转换为适合网络传输的格式
- 会话层

  - 是想怎样更好的把数据传输到对面
  - 负责建立和断开通信连接
- 传输层：

  - 确立连接与断开连接重发
  - 起着可靠传输的作用
- 网络层：

  - 通信处理
  - 将数据传输到目标地址
- 数据链路层：通过传输介质互连的设备之间进行数据处理
  - 网络层是把整个数据传输给接收端‘
  - 但是数据链路层是把一个分段的数据发送过去

  - 负责物理层面上互连的、节点之间的通信传输
- 物理层

  - 负责0、1比特流与电压的高低、光的闪灭之间的互换





# 守护进程

- 定义：
  - 守护进程(daemon)是一类在后台运行的特殊进程，用于执行特定的系统任务。很多守护进程在系统引导的时候启动，并且一直运行直到系统关闭。另一些只在需要的时候才启动，完成任务后就自动结束





# telnet（一种应用层协议）

- 定义：
  - 使用于互联网及局域网中，使用虚拟终端的形式，提供双向、以文字字符串为主的命令行接口交互功能。属于TCP/IP协议族的其中之一，是互联网远程登录服务的标准协议和主要方式，常用于服务器的远程控制，可供用户在本地主机运行远程主机上的工作
- 用途：
  - 用户首先在电脑运行Telnet程序，连线至目的地服务器，然后输入账号和密码以验证身份。用户可以在本地主机输入命令，然后让已连接的远程主机运行，就像直接在对方的控制台上输入一样。传统Telnet会话所传输的资料并未加密，账号和密码等敏感资料容易会被窃听，因此很多服务器都会屏蔽Telnet服务，改用更安全的SSH。

- 仿真终端功能
  - 仿真终端（nvt）
  - 行模式
  - 透明模式
- 协商选择机制
- 用于登录路由器或高性能交换机





# FTP（文本传输协议）

- 定义：
  - 文件传输协议（英语：File Transfer Protocol，缩写：FTP）是一个用于在计算机网络上在客户端和服务器之间进行文件传输的应用层协议。文件传送（file transfer）和文件访问（file access）之间的区别在于：前者由FTP提供，后者由如NFS等应用系统提供

- 两条TCP连接
  - 一条用来控制，一条用来数据的传输
  - 控制用的是tcp21号端口
  - 数据传输用的端口是20
  - 通常用于数据传输的tcp连接是按照与控制用的连接相反的方向建立的
- FTP是一个8位的客户端-服务器协议，能操作任何类型的文件而不需要进一步处理，就像MIME或Unicode一样。但是，FTP有着极高的延时，这意味着，从开始请求到第一次接收需求数据之间的时间，会非常长；并且不时的必须执行一些冗长的登录进程





# CGI（通用网关接口）

- 定义：
  - 在计算机领域，Common Gateway Interface (CGI) 是为了web 服务去执行类似于console application (也可以称作command-line interface programs) 的程序，这种程序是在server上实现 动态页面 提供了一种通用的协议，这样的程序称作 CGI 脚本。重点是这些脚本如何在server上执行。通常情况下，一次请求对应一个CGI 脚本的执行，生成一个 HTML







# RSS（简易资讯聚合）

- 定义：
  - 中文译作简易资讯聚合[3]，也称聚合内容[4]，是一种消息来源格式规范，用以聚合经常发布更新资料的网站，例如部落格文章、新闻、音讯或视讯的网摘。RSS文件（或称做摘要、网路摘要、或频更新，提供到频道）包含全文或是节录的文字，再加上发布者所订阅之网摘资料和授权的元数据。简单来说 RSS 能够让使用者订阅个人网站个人博客，当订阅的网站有新文章是能够获得通知。







# 端口转发

- 定义：就是将一台主机的网络端口转发到另外一台主机并由另一台主机提供转发的网络服务



### 网络层的作用

实现主机与主机之间的通信，也叫点对点（end to end）通信

ps：数据链路层是实现两个设备之间的通信，ip层是实现两个网络之间的通信

- 在网络中数据包传输中，源IP地址和⽬标IP地址在传输过程中是不会变化的，只有源 MAC 地址和⽬标 MAC ⼀直在变化







#  MAC

- 定义：
  - MAC地址（英语：Media Access Control Address），直译为媒体访问控制地址，也称为局域网地址（LAN Address），以太网地址（Ethernet Address）或物理地址（Physical Address），它是一个用来确认网络设备位置的地址
  - MAC地址用于在网络中唯一标示一个网卡，一台设备若有一或多个网卡，则每个网卡都需要并会有一个唯一的MAC地址
  - 所以具有唯一性
- 在OSI模型中，第二层数据链接层则负责MAC地址
- 组成：
  - MAC地址共**48**位（6个字节），以十六进制表示。第1Bit为广播地址(0)/群播地址(1)，第2Bit为广域地址(0)/区域地址(1)。前3~24位由IEEE决定如何分配给每一家制造商，且不重复，后24位由实际生产该网络设备的厂商自行指定且不重复
- mac地址分为三种
  - 单播 MAC 地址是指第一个字节的最低位是 0 的 MAC 地址
  - 组播 MAC 地址是指第一个字节的最低位是 1 的 MAC 地址
  - 广播 MAC 地址是指每个比特都是 1 的 MAC 地址。广播 MAC 地址是组播 MAC 地址的一个特例





### 路由控制

- ![](F:\Code\LearningNote\Computer Network\Note\image\路由控制.png)



### IP分片与重组

- 每种数据链路的最⼤传输单元 MTU 都是不相同的，如 FDDI 数据链路 MTU 4352、以太网的 MTU 是 1500 字节等
- 我们最常⻅数据链路是以太网，它的 MTU 是 1500 字节，那么当 IP 数据包⼤⼩⼤于 MTU 时， IP 数据包就会被分片
- 为啥ip要分片，tcp也要分片？
  - 在分片传输中，⼀旦某个分片丢失，则会造成整个 IP 数据报作废，所以 TCP 引⼊了 MSS 也就是在 TCP 层进⾏ 分片不由 IP 层分片
  - 而ip分片是因为链路有自己的最大传输单元



### IPV6



网段地址是主机号全为0的地址，表示某个网段

广播地址是主机号全为1的地址，向同一个网段中的所有主机发送数据包的一个地址





# FTP

- FTP协议使用两条TCP连接来完成文件传输，一条连接用于传送控制信息(命令和响应)，另一条连接用于数据发送