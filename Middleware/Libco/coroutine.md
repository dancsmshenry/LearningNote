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





对无栈协程的理解：

- 无栈coroutine需要对函数进行语言级别上的分解，即将函数拆分为不同的模块，使得原函数的执行变为一个一个函数模块的执行

- ```cpp
  struct test_coroutine {
      int i;
      int __state = 0;
      void MoveNext() {
          switch(__state) {
          case 0:
              return frist();
          case 1:
              return second();
          case 2:
          	return third();
          }
      }
      void frist() {
          i = 0;
          __state = 1;
      }
      void second() {
          i++;
          _state = 2;
      }
      void third() {
      	i--;
      }
  };
  
  ```

- 我们可以看到相比与有栈协程中的test函数，这里把整个协程抽象成一个类，以原本需要执行切换的语句处为界限，把函数划分为几个部分，并在某一个部分执行完以后进行状态转移，在下一次调用此函数的时候就会执行下一部分，这样的话我们就完全没有必要像有栈协程那样显式的执行上下文切换了，我们只需要一个简易的**调度器来调度这些函数**即可

- 从执行时栈的角度来看，其实所有的协程共用的都是一个栈，即系统栈，也就也不必我们自行去给协程分配栈，因为是函数调用，我们当然也不必去显示的保存寄存器的值，而且相比有栈协程把局部变量放在新开的空间上，无栈协程直接使用系统栈使得CPU cache局部性更好，同时也使得无栈协程的中断和函数返回几乎没有区别，这样也可以凸显出无栈协程的高效

- 换句话说，就不需要我们自己再开辟空间用来存储寄存器的值，而是直接借助原生的stack空间实现的，所以效率上会更快

- 不过，这种做法的难点在于，要从编译器的角度对代码进行改造，难度upup



对称协程和非对称协程

- 对称协程 Symmetric Coroutine：任何一个协程都是相互独立且平等的，调度权可以在任意协程之间转移
- 非对称协程 Asymmetric Coroutine：协程出让调度权的目标只能是它的调用者，即协程之间存在调用和被调用关系
- 对称就是它们之间都是平等的，就是假如A协程执行了B，C协程，那么B协程可以切换回A，也可以切换回C。而非对称只能是B切换回A，A切换回C，C再切换回A，以此类推



https://blog.csdn.net/weixin_43705457/article/details/106924435

https://mthli.xyz/coroutines-in-c/

https://blog.csdn.net/weixin_43705457/article/details/106857068

https://blog.csdn.net/liuyuan185442111/article/details/123151817