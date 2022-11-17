# 多线程服务器端实现

## 18.2 线程创建及运行

- ```c
  #include <stdio.h>
  #include <unistd.h>
  #include <pthread.h>
  void* thread_main(void *arg);
  
  int main(int argc, char *argv[]){
          pthread_t t_id;
          int thread_param = 5;
  
          if (pthread_create(&t_id, NULL, thread_main, (void*)&thread_param) != 0){
                  puts("pthread_create() error!");
                  return -1;
          };
          sleep(10);//上面再遍历过线程函数以后，是一边执行线程，一边执行主函数的（所以如果sleep的参数变为了2，就无法执行完这个线程的）
          puts("end of main");
          return 0;
  }
  
  void* thread_main(void *arg){
          int i;
          int cnt = *((int*)arg);
  
          for (i = 0; i < cnt; i ++ ){
                  sleep(1);
                  puts("running thread");
          }
          return NULL;
  }
  
  ```

- ```c
  #include <pthread.h>
  
  int pthread_create(pthread_t* restrict thread, const pthread_attr_t* restrict attr, void*(* start_routine)(void*), void* restrict arg);
  
  //thread 保存新创建线程ID的变量地址值，线程与进程相同，也需要区分不同线程的ID
  //attr 用于传递线程属性的参数，传递为NULL时，创建默认属性的线程
  //start_routine 相当于线程main函数的、在单独执行流中执行的函数地址值（函数指针）
  //arg 通过第三个参数传递调用函数时包含参数信息的变量地址值
  ```

- ```c
  #include <pthread.h>
  
  int pthread_join(pthread_t thread, void** status);
  //thread 该参数值ID的线程终止后才会从该函数返回
  //status 保存线程的main函数返回值的指针变量地址值
  /*
  调用该函数的进程（或线程）将进入等待状态，直到第一个参数为ID的线程终止为值，而且可以得到线程的main函数返回值
  */
  ```

- 根据临界区是否引起问题，函数可分为以下2类：

  - 线程安全函数：被多个线程同时调用时也不会引发问题
  - 非线程安全函数：被同时调用时会引发问题

- 线程安全函数的名称后缀一般加上_r

- 多线程访问同一个全局变量会出问题的



## 18.3 线程存在的问题和临界区

- 多个线程改变全局变量的情况，有可能是说，第一个复制数据进行修改，然后在第一个还在修改数据的过程中，第二个线程可能会也会修改这个值，但是此时的值还是原来的，即如果想要的是第二个线程修改的是第一个线程修改后得到的值的话，就会出现问题
- 两条不同的语句由不同线程同时执行时，可能构成临界区（访问同一内存空间）



## 18.4 线程同步

- 需要同步的情况：
  - 同时访问同一内存空间时发生的情况
  - 需要指定访问同一内存空间的线程执行顺序的情况
- 互斥量
  - 表示不允许多个进程同时访问，主要用于解决线程同步访问的问题