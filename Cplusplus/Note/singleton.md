# 懒汉模式

- 直到用到的时候才会被创建出来

- ```cpp
  class single {
  private:
      single() = default;
      single(const single& s) = default;
      static single* s1;
  
  public:
      static single* getsingle() {
          if (s1 == nullptr) {
              s1 = new single();
          }
          return s1;
      }
  };
  
  single* single::s1 = nullptr;
  /**
  线程不安全，因为：
  1、线程A进入函数getsingle执行判断语句，这句执行后就挂起了，这时线程A已经认为s1为nullptr，但是线程A还没有创建single对象
  
  2、又有一个线程B进入函数getsingle执行判断语句，此时同样认为s1变量为nullptr，因为A没有创建getsingle对象。线程B继续执行，创建了一个getsingle对象
  
  3 稍后，线程A接着执行，也创建了一个新的single对象
  
  4 创建了两个对象！
  **/
  ```

- ```cpp
   class Singleton
   {
   public:
       static Singleton& Instance()
       {
           static Singleton instance;
           return instance;
       }
   public:
       Singleton(const Singleton&) = delete;
       Singleton(Singleton&&) = delete;
       Singleton& operator=(const Singleton&) = delete;
       Singleton& operator=(Singleton&&) = delete;
   private:
       Singleton() = default;
       ~Singleton() = default;
   };
    
  //线程安全的，effective cpp里面给的例子（）
  ```

- 用智能指针实现

  - ```cpp
    class Singleton
     {
     public:
         static Singleton& Instance()
         {
             static std::unique_ptr<Singleton> instance_ptr(new Singleton());
             return *instance_ptr;
         }
     public:
         Singleton(const Singleton&) = delete;
         Singleton(Singleton&&) = delete;
         Singleton& operator=(const Singleton&) = delete;
         Singleton& operator=(Singleton&&) = delete;
         ~Singleton() = default;
     private:
         Singleton() = default;
     };
    ```







# 饿汉模式

- 一开始就创造出来了

- ```cpp
  class Singleton
  {
  private:
  	static Singleton instance;
  private:
  	Singleton();
  	~Singleton();
  	Singleton(const Singleton&);
  	Singleton& operator=(const Singleton&);
  public:
  	static Singleton& getInstance() {
  		return instance;
  	}
  }
  
  // initialize defaultly
  Singleton Singleton::instance = new Singleton();
  //线程安全的
  ```

- 问题：

  - 由于在main函数之前初始化，所以没有线程安全的问题。但是潜在问题在于no-local static对象（函数外的static对象）在不同编译单元中的初始化顺序是未定义的。也即，static Singleton instance;和static Singleton& getInstance()二者的初始化顺序不确定，如果在初始化完成之前调用 getInstance() 方法会返回一个未定义的实例



- 参考：https://zhuanlan.zhihu.com/p/37469260



- 其实是不是，除了单例对象，其他的对象是不需要反初始化接口的？
  - 单例对象需要反初始化，是因为需要保证析构的顺序，避免资源的不当访问
  - 部分类需要提供类似 stop 的接口，本质和 deinitialize 接口是有区别的，因为 stop 对应的其实是 start，类似网关，可以通过某些指令开启或者关闭，再或者开启关闭
  - 一般的对象，析构的时候再将资源依次释放，是符合正常逻辑的；至于为什么需要有初始化的接口，而不是在构造的时候直接抛出错误异常，是因为我们的逻辑其实是不希望部分组件的功能影响了整体，比如说使用某个 log 组件，构造失败后可以接住错误，而不是让整个程序挂掉，所以才用 initialize 的类似返回错误码的机制
