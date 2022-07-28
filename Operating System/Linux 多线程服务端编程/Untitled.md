1 Reactor模式的实现：关键是三个类：Channel,Poller,EventLoop。

class Channel：

事件分发器，其记录了描述符fd的注册事件和就绪事件，及就绪事件[回调](https://so.csdn.net/so/search?q=回调&spm=1001.2101.3001.7020)比如可读回调readCallback。其和文件描述符fd是一一对应的关系，但其不拥有fd。当一个fd想要注册事件并在事件就绪时执行相应的就绪事件回调时，首先通过Channel::update(this)->EventLoop::updateChannel(Channel*)->Poller::updateChannel(Channel*)调用链向poll系统调用的侦听事件表注册或者修改注册事件。Channel作为是事件分发器其核心结构是Channel::handleEvent()该函数执行fd上就绪事件相应的事件回调，比如fd可读事件执行readCallback()。Channel应该还具有一个功能是：Channel::~Channel()->EventLoop::removeChannel(Channel*)->Poller::removeChannel(Channel*)将Poller中的Channel*移除防止空悬指针。这是因为Channel的生命周期和Poller/EventLoop不一样长。其关键数据成员：int fd_文件描述符，int events_文件描述符的注册事件，int revents_文件描述符的就绪事件，及事件回调readCallback_,writeCallback...



class Poller：实现IO multiplexing,其功能仅仅是poll系统调用的简单封装，其生命周期和EventLoop一样长，Poller不拥有Channel支持有Channel*指针(因此必要时候需要Channel自己解注册以防空悬指针)。Poller的关键数据成员是:vector<struct pollfd> pollfds_事件结构体数组用于poll的第一个参数;map<int,Channel*> channels_用于文件描述符fd到Channel的映射便于快速查找到相应的Channel,如poll返回后遍历pollfds_找到就绪事件的fd再通过channels_找到fd的channel然后就可以通过Channel::handleEvent()执行就绪事件回调，值得注意的是Channel中已经记录了fd所以fd和Channel完成了双射。关键的成员函数：Poller::poll(int timeoutMs,vector<Channel*> *

 * activeChannels)其调用poll侦听事件集合，并在timoutMs时间内就绪的事件集合通过activeChannels返回。这里Poller::poll()在poll返回后本可以执行Channel::handleEvent()将就绪事件的回调执行了，但是并没有这样做的原因是，Channel::handleEvent()可能修改Poller的两个容器,即添加或删除Channel*，在遍历容器的时候修改容器是非常危险的，同时为了简化Poller，Poller的职责仅仅是IO复用，至于事件分发还是交给Channel自己完成。

class EventLoop: 事件循环。先看一个调用链：EventLoop::loop()->Poller::poll()通过此调用链获得一个vector<Channel*> activeChannels_的就绪事件集合，再遍历该容器，执行每个Channel的Channel::handleEvent()完成相应就绪事件回调。至此一个完整的Reactor模式即完成。注意这里的Reactor遵循one loop per thread即所在一个线程中完成，故并没有涉及到线程同步机制，以后可能会有其它线程调用这三个类，则通过线程转移函数将一些操作转移到一个线程中完成。(若一个函数既可能加锁情况下使用有可能在未加锁情况下使用，那么就拆成两个函数，需要加锁的函数去调用不需要加锁的函数。线程转移实现就可以通过两个函数实现，如：假设类one隶属于线程B，线程A调用one的方法fun，fun向one注册一个回调，从而将具体操作转移到one的所属线程B中去执行。)


2 定时器: 主要有几个类,Timer定时器包含超时回调，TimerId定时器加上一个唯一的ID，Timestamp时间戳，TimerQueue管理所有的定时器。传统的定时通过select/poll实现，现在通过timerfd实现定时，采用文件描述符实现定时将有利于统一事件源。这些将为EventLoop实现定时功能。
   Timer：定时器，具有一个超时时间和超时回调。超时时间由当前时间戳加上一个超时时间生成一个绝对时间。定时器回调函数timerCallback。
   TimerQueue: 定时器队列，用于管理所有的定时器,当定时器超时后执行相应的Timer::run()定时器回调。采用set<pair<TimeStamp,Timer*> >存储所有未超时的定时器，这里采用pair<TimeStamp,Timer*>的原因是在一个时间点可能有多个时间戳TimeStamp超时，而查找只返回一个。通过给timerfd一个超时时间实现超时计时，通过Channel管理timerfd，然后向EventLoop和Poller注册timerfd的可读事件，当timerfd的可读事件就绪时表明一个超时时间点到了，TimerQueue::handleRead()遍历set容器找出那些超时的定时器并执行Timer::run()实现超时回调。timerfd怎么实现多个定时器超时计时的呢？每次向set插入一个定时器Timer的时候就比较set的头元素的超时时间，若新插入的超时时间小，则更新timerfd的时间，从而保证timerfd始终是set中最近的一个超时时间。当timerfd可读时，需要遍历容器set，因为可能此时有多个Timer超时了(尽管tiemrfd是当前最小的定时时间)。为了复用定时器，每次执行完定时器回调后都要检查定时器是否需要再次定时。这里的关键是采用timerfd实现统一事件源。
   
3 class EventLoop的改动，实现用户定时回调：当有了定时器TimerQueue后，EventLoop就可以实现几个定时器接口：EventLoop::runAt(TimeStamp,TimerCallback)在一个绝对时间执行一个回调TimerCallback;EventLoop::runAfter(double delay,TimerCallback)实现一个相对时间回调，其内部实现是当前时间戳TimeStamp加上delay后形成一个绝对时间戳然后调用EventLoop::runAt(); EventLoop::runEvery(double interval,TimerCallback)实现周期回调，这里将使用到TimerQueue执行完超时回调后会检查定时器是否需要再次定时的功能。


4 class EventLoop的改动，实现用户指定任务回调：EventLoop::runInLoop(boost::function<void()>)，若是EventLoop隶属的线程调用EventLoop::runInLoop()则EventLoop马上执行;若是其它线程调用则执行EventLoop::queueInLoop(boost::function<void()>将任务添加到队列中(这里就是前面说的线程转移)。EventLoop如何获得有任务这一事实呢？通过eventfd可以实现线程间通信，具体做法是：其它线程向EventLoop::vector<boost::function<void()> >添加任务T，然后通过EventLoop::wakeup()向eventfd写一个int，eventfd的回调函数EventLoop::handleRead()读取这个int，从而相当于EventLoop被唤醒，此时loop中遍历队列执行堆积的任务。这里采用Channel管理eventfd，Poller侦听eventfd体现了eventfd可以统一事件源的优势。


5 实现线程安全的class TimerQueue：原来添加定时器的调用链：TimerQueue::addTimer()->TimerQueue::insert()实现添加的，但是这只能实现TimerQueue所属的线程执行，若其它线程想向此IO线程添加一个定时任务是不安全的。
为了实现添加定时器Timer到set的线程安全性，将定时器添加函数TimerQueue::addTimer()分拆为两部分：TimerQueue::addTimer()只负责转发，addTimerInLoop()实现具体的定时器添加。具体的调用链为：TimerQueue::addTimer()->EventLoop::runInLoop(TimerQueue::runInLoop)->TimerQueue::runInLoop()->TimerQueue::insert()，可以看出通过把TimerQueue::runInLoop()这个回调任务添加EventLoop::runInLoop()中从而实现将添加定时器这一操作转移到IO线程来做。TimerQueue::insert()插入一个新的定时器后将检查当前最近的超时时间，若最近的超时时间变了则重置timerfd的计时。


6 class  EventLoopThread: 启动一个线程执行一个EventLoop,其语义和"one loop per thread“相吻合。注意这里用到了互斥量和条件变量,这是因为线程A创建一个EventLoopThread对象后一个运行EventLoop的线程已经开始创建了，可以通过EventLoopThread::startLoop()获取这个EventLoop对象，但是若EventLoop线程还没有创建好，则会出错。所以在创建EventLoop完成后会执行condititon.notify()通知线程A，线程A调用EventLoopThread::startLoop()时调用condition.wai()等待，从而保证获取一个创建完成的EventLoop.毕竟线程A创建的EventLoop线程，A可能还会调用EventLoop执行一些任务回调呢。


7 class Acceptor： 用于accept一个TCP连接，accept接受成功后通知TCP连接的使用者。Acceptor主要是供TcpServer使用的，其生命期由后者控制。一个Acceptor相当于持有服务端的一个socket描述符，该socket可以accept多个TCP客户连接，这个accept操作就是Acceptor实现的。
 这里封装了一些常用的网络相关的数据结构和操作，如class InetAddress表示sockaddr_in的封装，如可以通过ip地址和port端口生成一个sockaddr_in; class Socket封装了部分关于socket套接字的操作，如Socket::bindAddress(InetAddress&)将socket和一个sockaddr_in地址绑定，Socket::accept(InetAddress& peerAddr)将一个socket允许连接一个客户端地址peerAddr，Socket::listen()监听socket，Socket::shutdownWrite()实现关闭socket的写。
  Acceptor在构造的时候会创建一个socket描述符acceptSocket_(这是一个Socket类型即socket的RAII封装)，并通过一个Channel(注册事件及回调函数)管理acceptSocket_::fd成员(即socket描述符)，一旦该socket可读即有TCP客户连接请求，则Channel::handleEvent()将会调用Acceptor::hanleRead()执行accept一个TCP客户连接。Acceptor::handleRead()还会将新的TCP客户连接和客户端地址通过回调函数newConnectionCallback(connfd,peerAddr)传给该TCP客户连接的使用者，通常是TcpServer类，这里的回调函数newConnectionCallback是在Acceptor::setNewConnectionCallback(newConnectionCallback)指定的。值得注意的是这里又是统一事件源的思想，即通过Channel和Poller管理事件。Acceptor::listen()的工作是：启动acceptSocket_::listen()监听socket描述符，并通过Channel::enableReading()将socket的可读事件注册到Poller的事件集合中。


8 class TcpServer: 管理所有的TCP客户连接，TcpServer供用户直接使用，生命期由用户直接控制。用户只需设置好相应的回调函数(如消息处理messageCallback)然后TcpServer::start()即可。
 这里先假设每个TCP客户连接由一个类TcpConenction管理(具体执行消息的接收发送之类的)，而TcpServer的工作就是管理这些TcpConenction，TcpConnection将在后面给出。假设TcpServer持有boost::scoped_ptr<TcpConnection>的指针TcpConnectionPtr。
  TcpServer在构造时接收一个由IP地址和port构成的InetAddress参数，并将此地址传给Acceptor用于接收该地址的TCP连接请求。
  TcpServer持有scoped_ptr<Acceptor> acceptor_用于接收TcpServer监听端口上的TCP连接请求，注意Accpetor每次accept连接后都要将新连接的描述符connfd和地址peerAddr返回给使用者，这里TcpServer在构造时通过accptor_->setNewConnectionCallback(bind(&TcpServer::newConnection,this,_1,_2))将TcpServer::newConnection传给Acceptor，acceptor_在接受TCP客户连接后将调用TcpServer::newConnection(connfd,peerAddr)，而TcpSrever::newConnection()的主要功能就是为<connfd,peerAddr>创建一个TcpConnection管理该TCP客户连接，并向TcpConnection注册一些回调函数，比如:connectionCallback主要是在TcpServer中由用户指定的一些连接处理函数最后一路经由TcpSrever传到TcpConnection中才被调用，此外还有用户指定的消息处理回调等都是经由TcpServer传给TcpConnection中去具体执行。此外TcpServer::newConnection()中还会执行TcpConnection::connectEstablished()该函数将会使这个具体的TcpConnection连接对应的描述符connfd加入poll的事件表，即也是通过一个Channel管理一个具体的TCP客户连接。用户向TcpServer注册连接回调函数的调用链：用户在创建TcpServer后TcpServer::setConnectionCallback()接收用户注册的连接回调函数;同时在TcpServer创建时会向Acceptor注册回调：TcpServer::TcpServer()->Acceptor::setNewConnecioncallback()后有新TCP连接Acceptor接受连接，并执行回调给连接使用者：Acceptor::handelRead()->newConnection()/Tcpserver::newConnection()->TcpConnection::connectEstablished()/并向TcpConnection注册用户注册的Callback函数。
  TcpServer采用map<string,TcpConnectionPtr>管理所有的TCP客户连接，其中string是由TcpServer的服务端地址加上一个int构成表示TcpConnectionPtr的名字。
  TcpServer中由用户指定的回调有：connectionCallback当TcpConenction建立时调用(由TcpConnection::connectEstablished()调用connectionCallback())用于执行用户指定的连接回调。messageCallback当TcpConenction有网络消息的时候执行该函数由Channel::handleEvent()->TcpConnection::handleRead()->messageCallback()。writeCompleteCallback由用户指定的当TCP连接上的消息发送完毕时执行的回调。这些函数都是用户在TcpServer创建后通过TcpServer::set*Callback系列函数注册的。当Acceptor接受一个新的TCP连接时执行Acceptor::handleRead()->TcpServer::newConnection()->TcpConnection::set*Callback()这样完成用于指定函数的传递。那么执行呢？这个要在TcpConenction对应的socket事件就绪时可读/可写时由Channel::handEvent()执行这些用户指定的回调。
  TcpServer::removeConnection()主要功能从TcpServer中移除一个TcpConnection，但是不能直接移除，而要通过线程转移函数完成。TcpServer::removeConenction()将执行EventLoop::runInLoop(bind(&TcpServer::removeConnectionInLoop)->EventLoop::runInLoop()->TcpServer::removeConnectionInLoop()
   TcpServer::removeConenctionInLoop()将一个TcpConnection从TcpServer中移除，并向EventLoop注册回调EventLoop::runInLoop(bind(&TcpConenction::connectDestroyed)),然后执行TcpConnection::connectDestroyed()。


9 class TcpConnection: 用于管理一个具体的TCP客户连接，比如消息的接收与发送，完成用户指定的连接回调connectionCallback。这里采用shared_ptr管理TcpConnection，因此其public继承boost::enable_shared_from_this<TcpConnection>。
  TcpConnection构造时接收参数有TCP连接的描述符sockfd，服务端地址localAddr,客户端地址peerAddr，并通过Socket封装sockfd。且采用Channel管理该sockfd，向Channel注册TcpConection的可读/可写/关闭/出错系列回调函数，用于Poller返回就绪事件后Channel::handleEvent()执行相应事件的回调。
  TcpConnection有四个状态：kConnecting正在连接，kConnected已连接，kDisconnecting正在断开，kDisconnected已断开。
  TcpConnection:有一些列函数用于TcpServer为连接指定事件回调函数，如TcpConnection::setConnectionCallback/setCloseback等是在TcpServer::newConnection()中注册的回调函数，并且当Acceptor接受一个新TCP连接后执行回调TcpServer::newConnection()，该回调创建一个TcpConenction对象并将用户指定的回调函数通过TcpConnection::set*Callback函数传给TcpConneciton。
  TcpConnection有一些列函数用户处理sockfd上的事件回调函数，如TcpConnection::handleRead()是在Poller返回sockfd可读事件时由Channel::handleEvent()调用的。类似还有TcpConnection::handleWrite()等。
  TcpConnection::send(string& message)->EventLoop::runInLoop(bind(&TcpConnection::sendInLoop(string& message))->EventLoop::doPendingFunctors()->TcpConnection::sendInLoop(string& message)保证消息发送的线程安全，后者通过write系统调用发送消息。
  TcpConnection::shutdown()->EventLoop::runInLoop(bind(&TcpConnection::shutdownInLoop())->EventLoop::doPendingFunctors()->TcpConnection::shutdownInLoop()类似上面，通过线程转移操作实现安全关闭TCP连接。
  TcpConnection中增加了用户指定系列回调函数conenctionCallback.messageCallback,writeCompleteCallback这些都是用户通过TcpServer传给TcpConnection，在TcpServer中已经描述过了。当Poller返回TcpConenction对应的Socket就绪事件时Channel::handleEvent()->TcpConnection::handle些列函数->执行这一些列回调。
   TcpConnection::closeCallback()不是给用户使用的，而是通知TcpServer或TcpClient移除它们容器中的TcpConnectionPtr。该函数如何设定的呢？当Acceptor接受一个TCP连接时:Channel::handelEvent()->Acceptor::handleRead()->TcpServer::newConenction()中新建一个TcpConnection并通过TcpConnection::setCloseCallback(bind(&TcpSerer::,removeConenction,this,_1))这样才完成将TcpServer::removeChannel()函数传递给TcpConnection::closeCallback()。closeCallback()何时执行呢？当由Channel管理的TcpConnection对应的Socket发生POLLHUP事件(该事件由Poller返回)就绪时，Channel::handleEvent()->TcpConnection::handleClose()->TcpConnection::closeCallback()->TcpServer::removeConnection()。
   TcpConnection::connectEstablished()连接建立回调函数(不是用户通过TcpServer指定的connectionCallback),该函数主要的功能：调用Channel::enableReading()将TcpConnection对应的Socket注册到Poller的事件表，执行用户指定的connectionCallback，并将TcpConnection状态置为kConnected。该函数何时被执行呢？回忆前面的Acceptor持有Tcpserver对应的服务端侦听描述符listenfd(由Channel管理)，当listenfd可读表明有TCP连接请求，此时Channel::handleEvent()->Acceptor::handleRead()->TcpServer::newConnection()->EventLoop::runInLoop(bind(&TcpConnection::connectEstablished))->EventLoop::queueInLoop()->EventLoop::loop()->EventLoop::doPendingFunctors()->TcpConnection::connectEstablished()。可见TcpServer也是通过向EventLoop::runInLoop添加Tcpconnection::conectEsatablished回调，表明TcpServer可TcpConencion可能不再同一个线程，需要通过线程转移来实现调用。
   TcpConenction::connectDestroyed()是TcpConenction析构前调用的最后一个函数，用于通知用户连接已断开。其只要功能是：将TcpConenction状态设为kDisconnected;Channel::disableAll()解除TcpConnection的事件注册，EventLoop::removeChannel()移除该管理TcpConnection的Channel;执行用于指定的回调conenctionCallback。该函数如何调用的呢？这要追溯到TcpServer::newConnection()将TcpServer::removeConenction注册到TcpConnection::closeCallback中，当TcpConnection对应的Socket的POLLHUP事件触发时执行TcpConenction::handleClose()->closeCallback()/TcpServer::removeConenction()->EvetnLoop::runInLoop()->TcpServer::removeInLoop()->EventLoop::runInLoop(bind(&TcpConnection::connectDestroyed))->TcpConnection::connectDestroyed()。
   TcpConnection::shutdown()用使用者执行关闭TcpConenction，TcpConnection::shutdown()->EventLoop::runInLoop()->TcpConnection::shutdownInLoop()->socket::shutdown(sockfd,SHUT_WR)//SHUT_WR表示以后的发送将被丢弃。
   TcpConnection::handleRead()被Channel::handleEvent()可读事件调用，它的主要工作是通过readv()将socket上的数据读取到Buffer中，并执行用于指定的消息回调messageCallback()。
   TcpConnection::handleWrite():被Channel::handleEvent()的可写事件调用，通过write()将Buffer的数据发送出去，若Buffer的数据一次性发送完毕，则执行用户指定的回调writeCompleteCallback()，若一次没有发送完毕，则poll和epoll的LT模式会反复触发可写事件的，所以下次还有机会发送剩余数据。
   TcpConnection::handleClose()主要执行Channel::disableAll()和closeCallback()。
   TcpConnection有连个Buffer(后面会提到)，inputBuffer_,outputBuffer_管理TcpConenction上的数据接收与发送。inputBuffer由TcpConnection::handleRead()调用(Buffer通过readv集中从fd集中读到内存中)。outputBuffer由TcpConnection::handleWrite()通过write()发送到fd上。
   TcpConnection::send()->EventLoop::runInLoop()->TcpConenction::runInLoop()，send()可以用户或者其它线程调用，用于发送消息message。这个函数需要先执行线程安全转移到TcpConenction所在的IO线程执行runInLoop()。runInLoop()函数的功能：首先检查TcpConneciton对应的Socket是否注册了可写事件，若注册了可写事件表明outputBuffer_中已经有数据等待发送，为了保证顺序这次的数据只好outputBuffer_.appen()到Buffer中通过Poller返回POLLOUT事件时Channel::handleEvent()->TcpConenction::handleWrite()来发送outputBuffer_的堆积数据。如果Channel::isWriting()返回false则表明此Socket没有向Poller注册POLLOUT事件也就此前没有数据堆积在outputBuffer_中，此次的消息message可以直接通过write发送，但是如果write没有一次性发送完毕，那么message剩余的数据仍要outputBuffer_::append()到Buffer中，并向Poller注册此Socket的POLLOUT事件，以通过TcpConnection::handleWrite()来发送outputBuffer_的堆积数据。无论是sendInLoop()->write还是Channel::handleEvent()->handleWrite()，只要确定发送完message或者outputBuffer_中的数据，那么都要调用用户指定的回调writeCompleteCallback()。
    此外TcpConenction还需要忽略SIGPIPE信号，做法是在TcpConenction.cc中定义一个IngoreSigPipe类构造时signal(SIGPIPE,SIG_IGN)。
   TcpConnection::setTcpNoDelay()->socketopt(..,TCP_NODELAY..)来关闭Nagle算法。
   
10  到了这步， EventLoop和Poller都应该具备成员函数removeC hannel()用于移除那些管理TcpConenction等的Channel。这里Poller有个成员vector<struct pollfd> pollfds_当移除Channel时有个trick值得注意：先将要移除的Channel::fd()的pollfd和pollfds_的最后一个元素交换swap()然后再调用pollfds_.pop_back可以避免vector删除时元素的移动。这样删除操作的复杂度为O(1)。


11  class Buffer应用层缓冲区：在non-blocking+IO multiplexing中应用层缓冲区是必须的。例如：TcpConection向发送100Kb数据，但是write只发送80Kb，剩下20Kb肯定要阻塞线程等待发送了，这和non-blocking矛盾，因此需要设计Buffer充当中间件置于应用层和底层write/read间从而实现non-blocking。这样，应用层只管生成或者读取数据，至于怎样存取数据和数据量则由Buffer完成。Buffer底层是vector<char>,有一个readerIndex和writerIndex分别表示可读位置和可写位置，这两个位置内的区间表示Buffer已有的数据。值得注意的是Buffer的两个trick：每次读取fd上的数据时通过readv一部分读取到Buffer中，一部分读取到找空间char extrabuf[65535]中，若Buffer装满了即extrabuf中有数据，则需要extrabuf中的数据append到Buffer中，这样做可以在初始时每个连接的Buffer的避免过大造成内存浪费，也避免反复调用read的系统开销，每次Buffer不够时通过extrabuf再append到Buffer中使Buffer慢慢变大;还有一个就是Buffer提供了一个前向空间，在消息序列化完毕时可以通过prepend()将消息的大小添加的Buffer的头部。另外Buffer的readerIndex和writerIndex都是移动的，只要在Buffer的空闲空间不够时才加大Buffer的vector，否则可以通过内部腾挪方式即让readerIndex和writerIndex向前移动(数据也跟着移动)这样Buffer就不增大vector.size().


12 class TcpServe的改进:  TcpServer有自己的一个EventLoop用来接收新的TCP客户连接，然后从event loop pool中选一个loop给TCP客户连接(即TcpConnection)。这就需要使用class EventLoopThreadPool来创建多个线程每个线程一个EventLoop(one loop per thread)。
  TcpServer::newConnection()在创建一个TcpConnection后从EventLoopTreadPool中选一个EventLoop给这个TcpConnection。

  TcpServer::removeConnection()需要拆分成两个函数，因为现在TcpServer和TcpConenction可能不再同一个线程里了，需要通过线程转移函数将移除操作转移到TcpConneciton的IO线程中去。TcpServer::removeConnection()->EventLoop::runInLoop()->TcpServer::removeConnectionInLoop()->EventLoop::runInLoop()->TcpConnection::connectDestroyed()。Tcpserver中erase掉这个TcpConnectionPtr。



13 class Connector:用于发起连接，当socket变得可写时表示连接建立完毕，其间需要处理各种类型的错误。connect返回EAGAIN是真的错误表示暂时没有端口可用，要关闭socket稍后再试;EINPROGRESS是“正在连接”，即使socket可写，也需要用getsockopt(sokfd,SOL_SOCKET,SO_ERROR...)再次确认。超时重连的时间应逐渐延长，需要处理自连接的情况。Connector只负责建立连接，不负责建立TcpConnection，它有一个建立连接回调函数由用户指定(Connector基本是TCP客户端使用，且一个客户端一个Conenctor)。

 Connector有三个状态：kDisconnected未连接，kConnecting正在连接，kConnected已连接。

 Connector构造时指定一个服务端地址InetAddress和一个事件循环EventLoop，状态设为kDisConnected。指定一个最大重试连接时间。

 Connector::start()可以由其它线程调用，该函数内部执行EventLoop::runInLoop(bind(&Connector::startInLoop,this))将通过EventLoop将操作转移到Connector的线程中去。

 Connector::startInLoop()判断此Connector还没有连接，则调用Connector::connect()

 Connector::connect()创建一个sockfd,并调用connect(sockfd,&serverAddress,sizeof(serverAddress))，然后返回一个errno，根据errno的值进行进一步选择是关闭连接，重师连接还是调用已连接函数。

 连接返回errno为EAGAIN则调用Connector::retry()该函数调用EventLoop::runAfter()在一段时间间隔后重试连接。

 errno为EINPROGRESS表示正在连接，则调用Connector::connecting()该函数将该为该连接设置一个Channel来管理连接，并向Channel注册Connector::handleWrite,Conenctor::handleError的回调函数。其中Connector::handleWrite()当正在连接kConnecting则用需要测试该连接(已经可写了还kConencting)可能需要进一步重新连接即调用Connector::retry()注意这时候socketfd需要重新分配了，而Conenctor是可以重复使用的。Cionnector::handleError()执行Connector::removeAndResetChannel()和Connector::retry()重试连接。

 当用户或其它线程调用Connector::start()->EventLoop::runInLoop()->Connector::startInLoop()->Connector::connect()根据errnor执行下面的情形：

EAGAIN：Connector::retry()->EventLoop::runAfter()延迟重连->Conncetor::startInLoop()

EACCESS/EPERM/EBADF:  close(sockfd)

EINPROGRESS：Connector::connecting()该函数向Channel注册回调函数并Channel::enableWriting()关注这个正在连接的socketfd是否可写。

 此后当处于“正在连接kConnecting”的sockfd事件就绪时：Channel::handelEvent()->Connector::handleWrite()/Connector::handleError()

  Connector::handleWrite()若检测Connector状态仍在kConnecting时需要调用getsocketopt(sockfd,SOL_SOCKET,SO_ERROR...)检测，若返回0则执行用户指定的连接回调函数Connector::newConnectionCallback()。

  Connector::handleError()->Conenctor::retry()



14 class TcpClient:每个TcpClinet只管理一个Connector。其内容和TcpServer差不多,TcpClient具备TcpConnection断开连接后重新连接的功能。

  TcpClient构造时new一个Connector，并指定一个EventLoop。用户要指定的connectionCallback,messageCallback回调函数。并设置Connector::setNewConnection(bind(&TcpClient::newConnection,this,_1))将连接建立回调赋给Connector::newConnectionCallback。

  用户调用TcpClient::connect()发起连接->Conenctor::start()->TcpClient::newConnection().

  TcpClinet::newConnection()将new一个TcpConneciton对象conn并设置TcpConnection::setConnecitonCallback/setMessageCallback/setWriteCompleteCallback/setCloseCallback等回调函数。其中setConnectionCallback将用户指定的ConnectionCallback传给TcpConenciton，setMessageCallback将TcpClient中用户指定的messageCallback传给TcpConneciton。TcpConnection::closeCallback是TcpClient::removeConenction。最后TcpClient::newConneciton()将会调用TcpConnection::connectEstablished()。

  TcpClient::removeConnection()，由于TcpClient只管理一个Connector也就是一个TcpConenction它们都在一个线程中，所以不涉及操作线程转移。TcpClient::removeConenction()->EventLoop::queueInLoop()->TcpConnection::connectDestroyed().若有重连的必要将执行Connector::restart()。



14  class Epoller和Poller差不多。