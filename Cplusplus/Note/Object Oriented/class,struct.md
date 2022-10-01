# struct和class的区别

相同点

- 两者都拥有成员函数、公有和私有部分 
- 任何可以使用class完成的工作，同样可以使用struct完成



不同点

- 两者中如果不对成员不指定公私有，struct默认是公有的，class则默认是私有的
- class默认是private继承，而struct模式是public继承



# struct 后面用冒号：

- ```cpp
  struct model {
    int a1: 4;  
  };
  ```

- 这里的a1只占用4位，其中最后一位作为符号位

- 如果超出了4位，那就还是只保留最后四位

- 总结，a1变量总共只占用4位，但是整个结构体还是4个字节（相当于要保留一个整数）





# struct的初始化

- ```cpp
  #include<stdio.h>
  struct student{
      /* data */
      int age;
      char name[5];
      char gender;
      double score;
  };
  
  int main()
  {
      struct student stu={
          .age=15, // 一种类型的
          .gender='M',
          .name="ca",
          .score=56.15,
      };
     
      printf("%d,%c,%s,%lf",stu.age,stu.gender,stu.name,stu.score);
  }
  
  typedef struct {int i;} color;
  struct color c2 {int i}; // 错误的用法（其他的都是z）
  struct {int i;} c1;
  struct color {} c3;
  ```
  
- 



# struct在C和C++中的区别

- 在C语言中，不支持成员函数（但是可以支持函数指针）；在Cpp中支持成员函数
- 在 C 中， struct 是用户自定义数据类型（UDT）；在 Cpp 中，struct 是抽象数据类型（ADT），支持成员函数的定义，能继承，能实现多态
- 在 C 中  struct 是没有权限的设置的，且struct中只能是一些变量的集合体，可以封装数据却不可以隐藏数据，而且成员不可以是函数
- 在 Cpp 中，struct 增加了访问权限，且可以和类一样有成员函数，成员默认访问说明符为 public （为了与 C 兼容）