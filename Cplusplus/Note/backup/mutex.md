std::recursive_mutex 为互斥锁，但是允许同一个线程重复拿锁

#### Scoped Locking

Scoped Locking 是将RAII手法应用于locking的并发编程技巧。其具体做法就是在构造时获得锁，在析构时释放锁，目前Scoped Locking技巧在C++中有以下4种实现：

- std::lock_guard (c++11): 单个std::mutex(或std::shared_mutex)
- std::unique_lock (c++11): 单个std::mutex(或std::shared_mutex), 用法比std::lock_guard更灵活
- std::shared_lock (c++14): 单个std::shared_mutex
- std::scoped_lock (c++17): 多个std::mutex(或std::shared_mutex)

应用：std::lock_guard, std::unique_lock, std::shared_lock 和 std::scoped_lock