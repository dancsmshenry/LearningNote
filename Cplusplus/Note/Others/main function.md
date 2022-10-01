# 传入参数

- 若不需要从命令行中获取参数，就使用int main(void) ；否则的话，就用int main( int argc, char *argv[] )

- ```cpp
  int main(void);
  int main(int argc, char* argv[]); // 这个是简化版的main函数（但也是最常用的）
  int main(int argc , char* argv[],char* envp[]); // 这个才是真正的main函数原版
  //	PS:所以说main函数是可以从命令行获取参数的
  ```



- 第一个参数argc表示的是传入参数的个数
- 第二个参数char* argv[]，是字符串数组，用来存放指向的字符串参数的指针数组，每一个元素指向一个参数
  - argv[0]：指向程序运行的全路径名
  - argv[1]：指向执行程序名后的第一个字符串 ，表示真正传入的第一个参数
  - argv[2]：指向执行程序名后的第二个字符串 ，表示传入的第二个参数
  - PS：规定**argv[argc]为NULL ，表示参数的结尾**
- 第三个参数char* envp[]，也是一个字符串数组，主要是保存这用户环境中的变量字符串



- ```c
  // test for main
  #include <stdio.h>
  
  int main(int argc ,char* argv[] ,char* envp[])
  {
      int i = 0;
  
      while(envp[i++])
      {
          printf("%s\n", envp[i]);
      }
  
      return 0;
  }
  ```







# 返回值

## 含义

- 返回值说明程序的退出状态
- 如果返回0，则代表程序正常退出
- 返回其它数字的含义则由系统决定（通常，返回非零代表程序异常退出）



## 标准

- c/cpp中是没有定义void main()的（但是一些编译器在实现上支持了void main()，至少我的gcc是支持的）

- cpp/c中没有明确规定要有返回类型，默认返回类型是int

  - 换言之main()等价于int main()

  - ```cpp
    #include <stdio.h>
    
    main(int argc ,char* argv[] ,char* envp[])
    {
        int i = 0;
    
        while(envp[i++])
        {
            // printf("%s\n", envp[i]);
        }
        printf("33");
    
    	return 0;//	这里有无都是ok的
    }//	无论是cpp还是c都是可以运行的
    ```

- 在cpp中（我的gcc10.3），main函数的返回值必须是int
- 在c中（我的gcc 10.3），main函数的返回值是可以为int，也可以为void的，甚至可以不写返回值类型（但gcc会给出warning）



## return语句

- 如果 main 函数的最后没有写 return 语句的话，c/cpp都规定编译器要自动在生成的目标文件中加入return 0，表示程序正常退出
- PS：return的返回值会进行类型转换







# 在main函数执行之前的代码

- linux系统下程序的入口是**_start**，这个函数是linux系统库（glibc）的一部分，当我们的程序和Glibc链接在一起形成最终的可执行文件的之后，这个函数就是程序执行初始化的入口函数
- __start是由ld链接器默认的链接脚本指定的，当然用户也可以通过参数进行设定
- **作用**：在调用 _start之前，装载器就会将用户的参数和环境变量压入栈中



main函数之前做的事情

- 设置栈指针
- 初始化static静态和global全局变量，即data段的内容
- 将未初始化的全局变量赋值，数值型short，int，long等为0，bool为FALSE，指针为NULL等等，即.bss段的内容
- 运行全局构造器，类似c++中全局构造函数
- 将main函数的参数argc，argv等传递给main函数，然后才执行main函数



真正运行的代码

- 全局对象的构造函数会在main 函数之前执行

  - ```c
    #include <iostream>
    using namespace std;
    
    inline int startup_1()
    {
        cout<<"startup_1 run"<<endl;
        return 0;
    }
    
    int static no_use_variable_startup_1 = startup_1();
    
    int main(int argc, const char * argv[]) 
    {
        cout<<"this is main"<<endl;
        return 0;
    }
    ```

- 一些全局变量、对象和静态变量、对象的空间分配和赋初值就是在执行main函数之前，而main函数执行完后，还要去执行一些诸如释放空间、释放资源使用权等操作

- 进程启动后，要执行一些初始化代码（如设置环境变量等），然后跳转到main执行。全局对象的构造也在main之前

- 通过关键字**attribute**，让一个函数在主函数之前运行，进行一些数据初始化、模块加载验证等

  - ```c
    #include <stdio.h>
    
    __attribute__((constructor)) void before_main_to_run() {
        printf("Hi～,i am called before the main function!\n");
        printf("%s\n",__FUNCTION__); 
    } 
    
    __attribute__((destructor)) void after_main_to_run() {
        printf("%s\n",__FUNCTION__); 
        printf("Hi～,i am called after the main function!\n");
    } 
    
    int main( int argc, char ** argv ) {
        printf("i am main function, and i can get my name(%s) by this way.\n",__FUNCTION__); 
        return 0; 
    }
    ```







# 在main函数执行之后的代码

- 全局对象的析构函数会在main函数之后执行
- 可以用 atexit 注册一个函数，它会在main 之后执行
- __ attribute __((destructor))



## atexit

- atexit 函数可以“注册”一个函数，使这个函数将在main函数正常终止时被调用，当程序异常终止时，通过它注册的函数并不会被调用

- 编译器必须至少允许程序员注册32个函数。如果注册成功，atexit 返回0，否则返回非零值，没有办法取消一个函数的注册

- 在 exit 所执行的任何标准清理操作之前，被注册的函数按照与注册顺序相反的顺序被依次调用。每个被调用的函数不接受任何参数，并且返回类型是 void。被注册的函数不应该试图引用任何存储类别为 auto 或 register 的对象（例如通过指针），除非是它自己所定义的。多次注册同一个函数将导致这个函数被多次调用

- ```cpp
  #include<stdio.h>
  #include<stdlib.h>
  
  void fn0( void ), fn1( void ), fn2( void ), fn3( void ), fn4( void );
  
  int main( void ) {
    //注意使用atexit注册的函数的执行顺序：先注册的后执行
      atexit( fn0 );  
      atexit( fn1 );  
      atexit( fn2 );  
      atexit( fn3 );  
      atexit( fn4 );
      printf( "This is executed first.\n" );
      printf("main will quit now!\n");
      return 0;
  }
  
  void fn0() {
      printf( "first register ，last call\n" );
  }
  
  void fn1() {
      printf( "next.\n" );
  }
  
  void fn2() {
      printf( "executed " );
  }
  
  void fn3() {
      printf( "is " );
  }
  
  void fn4() {
      printf( "This " );
  }
  ```





https://blog.csdn.net/z_ryan/article/details/80985101