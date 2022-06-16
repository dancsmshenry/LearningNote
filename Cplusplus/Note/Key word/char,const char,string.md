- ```cpp
  //a) string转const char*
  string s = “abc”; 
  const char* c_s = s.c_str(); 
  
  //b) const char* 转string，直接赋值即可
  const char* c_s = “abc”; 
  string s(c_s); 
  
  //c) string 转char*
  string s = “abc”; 
  char* c; 
  const int len = s.length(); 
  c = new char[len+1]; 
  strcpy(c,s.c_str()); 
  
  //d) char* 转string
  char* c = “abc”; 
  string s(c); 
  
  //e) const char* 转char*
  const char* cpc = “abc”; 
  char* pc = new char[strlen(cpc)+1]; 
  strcpy(pc,cpc);
  
  //f) char* 转const char*，直接赋值即可
  char* pc = “abc”; 
  const char* cpc = pc;
  ```

- string的底部就是封装了const char*

- 实际操作过程我们可以用const char*给 string类初始化

- string继承自basic_string,其实是对char * 进行了封装，封装的string包含了char*数组，容量，长度等等属性

- string可以进行动态扩展，在每次扩展的时候另外申请一块原空间大小两倍的空间（2^n），然后将原字 符串拷贝过去，并加上新增的内容







- ```cpp
  #include <iostream>
  #include <cstdio>
  
  using namespace std;
  
  int main() {
      char *p1 = "hello";
      char p2[] = "hello";
      char *p3 = "hello";
  
      printf("%p", *(&p1));//00007ff61011c001
      printf("\n%p", *(&p2));//000000c85a7ff64a
      printf("\n%p", *(&p3));//00007ff61011c001
  
  }
  ```

- char*是常量，编译器会对它进行优化，只要内容相同的话，都会指向同一块内存（默认是const）

- 而char[]不是常量，是字符串数组，是可以改变的





- 不借助swap函数，实现交换两个string的值

- ```cpp
  void swap(string& a, string&ｂ) {
      string tmp(move(a));
      a = move(b);
      b = move(tmp);
  }
  ```



string能否被继承

- 能被继承，但是析构不是虚函数会导致资源泄漏



# string的大坑

- string的析构函数不是virtual的，所以多态会造成内存泄漏的......







- 由char型数组是一段连续的存储空间，所以内容是可以改变的
- 但是char*定义的字符串存储在字符常量区，是不可以修改的





- 我们知道char*用来定义一个指针变量时，指针变量是可以改变的，
- 所以当用 char * 定义的字符串作为形参时，我们认为：char *背后的含义是：给我个字符串，我要修改它。（认为有误）
- 而理论上，我们传给函数的字面常量是没法修改的。（即char *定义的字符串不能被修改）
- 所以说：可行的方法是:把参数类型修改为const char *
- 这个类型表示：给我个字符串，我只读取它。（确实也就只能读取它）



- 这里说明了几点，需要用到const的时候必须要加上，否则就会像下面一样

- ```cpp
  #include <stdio.h>
  #include <iostream>
  
  void test(char* c1) {
      c1[0] = 'q';
  }
  
  int main()
  {
      char* c2 = "hello world";
      test(c2);
      std::cout << c2 << std::endl;
      // printf("%s", c2[1]);
  }
  ```

- 上面的代码能够编译，但是运行会直接报错（因为char*传入的值都是不能修改的）

- 为了避免这样的错误，就必须加上const