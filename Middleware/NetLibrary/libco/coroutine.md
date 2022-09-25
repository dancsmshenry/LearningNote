https://zhuanlan.zhihu.com/p/51078499

https://zhuanlan.zhihu.com/p/338767781

https://zhuanlan.zhihu.com/p/178525588

https://runzhiwang.github.io/2019/06/21/libco/

https://zhuanlan.zhihu.com/p/85639686

https://zhuanlan.zhihu.com/p/84935949

https://www.cyhone.com/articles/analysis-of-libco/

https://blog.codingnow.com/2012/07/c_coroutine.html

https://www.zhihu.com/question/32218874/answer/216801915

https://mthli.xyz/coroutines-in-c/





协程分为：对称协程（当前的coroutine发生yield的时候会给别的coroutine，因此需要调度器来决定下一个yield的目标）和非对称协程（当前的coroutine发生yield的时候，会给回调用这个coroutine的协程）

有栈协程（stackful）和无栈协程（stackless）



背景：传统线程是内核态线程，

1:n实现协程（libco），n:m实现协程（golang）



我们项目中burger中实现的是非对称的1:n协程



我感觉协程的一个好处就是，可以让业务方直接写同步代码，而不是像之前那样一直回调（可以write的时候做什么，可以read的时候做什么）

而且，在发生阻塞的时候，可以及时将协程给切换掉，而不是浪费时间片

其实业务的本质就是io，io是最底层的

而上面的各种中间件和思想，很多都是因为io而引入缓存