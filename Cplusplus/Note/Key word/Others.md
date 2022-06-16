# 其他

记录一些比较常见，但却无关紧要的小知识





### noexcept



### ifdef

ifdef和endif

- 背景1；

  - 一般，源程序中所有的行都参加编译，但是有时希望对其中一部分内容只在满足一定条件下进行编译，也就是对一部分内容指定编译条件，这就是条件编译

- 形式：

  - ```cpp
    #ifdef
    //程序段1
    #else
    //程序段2
    #endif
    ```

  - 当标识符已经被定义过，则对段1进行编译，否则就对段2进行编译

- 背景2：

  - 在一个大的软件工程里面，可能会有多个文件同时包含一个头文件，当这些文件编译链接成一个可 执行文件上时，就会出现大量“重定义”错误
  - 在头文件中使用#define、#ifndef、#ifdef、#endif能避免头文件重定义



### extern

- extern可以置于变量或者函数前，以表示变量或者函数定义在别的文件中，提示编译器遇到此变量和函数时在其他模块中寻找其定义

- ```cpp
  #include "my.h"
  
  CMyWinApp theApp; // 声明和定义了一个全局变量
  
  //------------------------------------------------------------------
  // main
  //------------------------------------------------------------------
  int main()
  {
  
      CWinApp* pApp = AfxGetApp();
  
      return 0;
  
  }
  //------------------------------------------------------------------
  //My.cpp
  ```

- ```cpp
  #include "my.h"  // it should be mfc.h, but for CMyWinApp definition, so...
  
  extern CMyWinApp theApp; // 提示编译器此变量定义在其他文件中，遇到这个变量时到其他模块中去寻找
  
  CWinApp* AfxGetApp()
  {
    return theApp.m_pCurrentWinApp;
  }
  //MFC.cpp
  ```



extern关键字

- extern是C/C++语言中表明函数和全局变量作用范围的关键字，该关键字高速编译器，其声明的函数和变量可以在本模块或其他模块中使用
- 与extern对应的关键字是static，被它修饰的全局变量和函数只能在本模块中使用。因此，一个函数或变量只可能被本模块使用时，其不可能被extern “C”修饰



extern "c"

- 被extern "C"修饰的变量和函数是按照C语言方式编译和链接的

- cpp代码调用C语言代码，在cpp的头文件中使用

  - ```cpp
    /* c语言头文件：cExample.h */
    #ifndef C_EXAMPLE_H
    #define C_EXAMPLE_H
    extern int add(int x,int y);     //注:写成extern "C" int add(int , int ); 也可以
    #endif
    
    /* c语言实现文件：cExample.c */
    #include "cExample.h"
    int add( int x, int y )
    {
    　return x + y;
    }
    
    // c++实现文件，调用add：cppFile.cpp
    extern "C"
    {
    　#include "cExample.h"        
        //注：此处不妥，如果这样编译通不过，换成 extern "C" int add(int , int ); 可以通过
    }
    
    int main(int argc, char* argv[])
    {
    　add(2,3);
    　return 0;
    }
    ```

- 在C中引用C++语言中的函数和变量时，C++的头文件需添加extern "C"，但是在C语言中不能直接引用声明了extern "C"的该头文件，应该仅将C文件中将C++中定义的extern "C"函数声明为extern类型

  - ```cpp
    //C++头文件 cppExample.h
    #ifndef CPP_EXAMPLE_H
    #define CPP_EXAMPLE_H
    extern "C" int add( int x, int y );
    #endif
    
    //C++实现文件 cppExample.cpp
    #include "cppExample.h"
    int add( int x, int y )
    {
    　return x + y;
    }
    
    /* C实现文件 cFile.c
    /* 这样会编译出错：#include "cExample.h" */
    extern int add( int x, int y );
    int main( int argc, char* argv[] )
    {
    　add( 2, 3 );
    　return 0;
    }
    ```

- https://www.jianshu.com/p/5d2eeeb93590







### enum



### union



### RAII

- 如果一个函数有多处return，我想每个return都加一些相同的处理，最好怎么实现？
- 这里最好的写法就是RAII模式的应用。不过很多时候我们也不必每次新建一个RAII模式的类。可以使用用unique_ptr来完成

