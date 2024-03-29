- 尾递归，进入下一个函数不再需要上一个函数的环境了，得到结果以后直接返回
- 非尾递归，下一个函数结束以后此函数还有后续，所以必须保存本地的环境以供处理返回值



- 尾递归相当于是在返回值的时候依赖于一个新的本函数，即控制权转移到新的递归函数
- 本质就是函数控制权的转移



- 普通的递归创建stack累积而后计算再收缩，而尾递归只会占用恒量的内存



- 所以有种模式为了防止普通递归带来的栈的消耗，所以就把变化的参数通过引用传递的方式当作函数变量

- ```cpp
  //尾递归版的循环相加
  int f(int x, int& sum) {
      if (x == 1 || x == 0) {
          return 1;
      } else {
          return f(x - 1, sum + x);
      }
  }
  ```



- python，java和pascal等语言无法实现尾递归优化，所以只能通过引用传递的方式来实现



- 尾递归，比线性递归多一个参数，这个参数是上一次调用函数得到的结果
- 尾递归每次调用都在收集结果，避免了线性递归不收集结果只能依次展开消耗内存的坏处



- 尾递归是一种形式，只是用这种形式表达出的概念可以被某些编译器优化（所以java/python不可以优化，cpp可以 ）
- 尾递归的特殊形式决定了这种递归代码在执行过程中是可以不需要回溯的（通常递归都是要回溯的）
- 如果编译器针对尾递归形式的递归代码做这种优化，就可能把原本需要线性复杂度栈内存空间的执行过程用常数复杂度的空间完成



- 尾递归优化主要是对栈内存空间的优化, 这个优化是O(n)到O(1)的; 至于时间的优化, 其实是由于对空间的优化导致内存分配的工作减少所产生的, 是一个常数优化, 不会带来质的变化
- 经过尾递归优化的尾递归代码和循环的代码的执行效率基本上是相当的. 这也是函数式编程效率上没有落后的一个很重要的原因



- 一个理解：为什么java等语言不适用尾递归优化，因为出错的时候无法查看栈信息，不利于debug



- 函数式编程的递归都是尾递归，转变的方法就是把需要用到的环境通过参数传递给下一层

- ```cpp
  int fib(int a, int b, int n) {
      if (n == 0) {
          return a;
      } else {
          return fib(b, a + b, n - 1);
      }
  }
  fib(1,1,3);
  ```



递归的背景

- 在函数被调用时，栈用来传递参数和返回值
- 栈：后进先出，用来保护/恢复现场，可以把每个调用的堆栈当作寄存、交换临时数据的内存区
- 当c程序中调用一个函数时，栈会分配一个空间来保存与这个调用相关的信息，每个调用都被当作是活跃的，栈上的那块存储空间称为活跃记录或者栈帧
- 缺点：
  - 栈维护了每个函数调用的信息直到函数返回后才释放，这需要占用相当大的空间，尤其是在程序中使用了许多的递归调用的情况下。除此之外，因为有大量的信息需要保存和恢复，因此生成和销毁活跃记录需要消耗一定的时间。我们需要考虑采用迭代的方案



定义

- 如果一个函数中所有的递归形式的调用都出现在函数的末尾
- 当递归调用是整个函数体最后执行的语句且它的返回值不属于表达式的一部分时，就是尾递归



优点

- 规避函数堆栈溢出



缺点

- coredump的时候，很难排查问题