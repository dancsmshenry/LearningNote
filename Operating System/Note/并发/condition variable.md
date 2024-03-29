# 定义

- 也就是OS书中常说的**管程**

- 使我们可以睡眠等待某种条件出现
- 是利用线程间共享的全局变量进行同步的一种机制
- 主要包含两个动作
  - 一个线程等待“条件变量”的条件成立而挂起（阻塞）
  - 另一个线程使“条件变量”成立，给出条件成立的信号
- 为了防止竞争，条件变量的使用总是和一个互斥锁结合在一起
- 条件变量是用来等待线程而不是上锁的，条件变量通常和互斥锁一起使用。条件变量之所以要和互斥锁一起使用，主要是因为互斥锁的一个明显的特点就是它只有两种状态：锁定和非锁定，而条件变量可以通过允许线程阻塞和等待另一个线程发送信号来弥补互斥锁的不足，所以互斥锁和条件变量通常一起使用
- 当条件满足的时候，线程通常解锁并等待该条件发生变化，一旦另一个线程修改了环境变量，就会通知相应的环境变量唤醒一个或者多个被这个条件变量阻塞的线程。这些被唤醒的线程将重新上锁，并测试条件是否满足。一般来说**条件变量被用于线程间的同步；**当条件不满足的时候，允许其中的一个执行流挂起和等待
- 可以用它mutex和条件变量来实现生产者消费者模型







# 虚假唤醒

- spurious wakeup

- 多个线程同时等待同⼀个条件满⾜时，当唤醒线程时，可能会唤醒多个线程，但是如果对应的资源只有⼀个线程能获得，其余线程就⽆法获得该资源，因此其余线程的唤醒是⽆意义的（有时甚⾄是有危害的），其余线程的唤醒则被称为虚假唤醒
- 所以，为了防止虚假唤醒，就必须要用while循环来判断

- 假如有多个消费者被唤醒，但是有一个消费者把数据给消费了，那么其他的消费者其实是不能继续往下消费的
- 但，如果你用的是if，就会造成别的消费者往下走去消费数据了，这就会出问题
- 所以得用while，每次唤醒的时候都要去判断是否真的是符合条件
- 当多个线程同时在等待同一条件，此时条件满足发起唤醒则可能会唤醒多个线程，但是如果对应的资源不够所有唤醒线程使用，则剩余线程的唤醒就是无意义的，也就被称作虚假唤醒

- PS：并发果然是会有各种奇奇怪怪的情况（所以要理解并发，就要放到各种奇怪的视角去看）

- 对于while(count > 0) {wait();}，为什么这里必须要用while？

- 假设此时有thread01和thread02，此时被生产者同时唤醒这两个线程，如果此时是if

- 那么有一个情况会比较坑爹，此时thread01被唤醒，那么他就会往下走去消费数据，最后释放锁

- 而接着thread01的时间片用完了，时间片给thread02

- 因为是if，所以它不会判断是否有数据可以消费，它就因此直接消费数据，此时就报错了.....



避免虚假唤醒

- 在睡眠返回之后重新检查条件判断（while代替if）

```cpp
while (true) {
    pthread_mutex_lock(&mutex);
    while (workQueue == nullptr) { // // 这里如果if的话，虚假唤醒时则会去获取空指针的内容，导致出错
        pthread_cond_wait(&cond, &mutex);
    }
    messagePtr = workQueue;
    workQueue = workQueue->next;
    pthread_mutex_unlock(&mutex);
}
```







# api的使用