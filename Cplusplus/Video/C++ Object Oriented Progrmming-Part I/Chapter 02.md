# 头文件与类的声明

- 两种基本的设计方式

  - object based：面对的是单一class的设计
  - object oriented：面对的是多重classes的设计，classes和classes之间的关系

- 代码的基本方式

  - .h，.hpp，.cpp等拓展名

- include的方式

  - 在c语言中，`#include<stdio.h>`
  - 在cpp中，`#include<cstdio>`

- header（头文件）中的防卫式声明

  - ```cpp
    #ifndef __COMPLEX__//这里需要改为文件的名字
    #define __COMPLEX__//同上
    
    //代码部分
    
    #endif
    ```

  - 第一次引入这个头文件，就会把这个`__COMPLEX__`给定义了先，如果后续又引入了这个文件，就可以直接跳过（防止重复引用）

- 头文件的布局

  - 前置声明（因为友元和静态函数的缘故，有些函数或类名需要在最开始先声明一遍）
  - 类声明（比如类里面的函数，只定义而不写全）
  - 类定义（补全之前定义的函数）

- class的声明：class head，class body

- class template的简介