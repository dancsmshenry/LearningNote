# char，string的相互转化

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
  strcpy(c，s.c_str()); 
  
  //d) char* 转string
  char* c = “abc”; 
  string s(c); 
  
  //e) const char* 转char*
  const char* cpc = “abc”; 
  char* pc = new char[strlen(cpc)+1]; 
  strcpy(pc，cpc);
  
  //f) char* 转const char*，直接赋值即可
  char* pc = “abc”; 
  const char* cpc = pc;
  ```

- string的底部就是封装了const char*

- 实际操作过程我们可以用const char*给 string类初始化

- string继承自basic_string，其实是对char * 进行了封装，封装的string包含了char*数组，容量，长度等属性

- string可以进行动态扩展，在每次扩展的时候另外申请一块原空间大小两倍的空间，然后将原字符串拷贝过去，并加上新增的内容







# char[]和char*

- ```cpp
  #include <iostream>
  #include <cstdio>
  
  using namespace std;
  
  int main() {
      char *p1 = "hello";
      char p2[] = "hello";
      char *p3 = "hello";
  
      printf("%p"， *(&p1));//00007ff61011c001
      printf("\n%p"， *(&p2));//000000c85a7ff64a
      printf("\n%p"， *(&p3));//00007ff61011c001
  
  }
  ```

- char*是常量，编译器会对它进行优化，只要内容相同的话，都会指向同一块内存（默认是const）

- 事实上，char*的数据会存在常量区（所以会默认的加上const）；而char[]不是常量，是字符串数组，是可以改变的

- ```cpp
  int main() {
      char *p1 = nullptr, *p2 = nullptr;
      p1 = (char*)malloc(10);
      p2 = (char*)malloc(10);
      printf("%p\n", p1);
      printf("%p\n", p2);
      strcpy(p1, "111");
      strcpy(p2, "111");
      printf("%p\n", p1); // 0000018661981560
      printf("%p\n", p2); // 0000018661981580
      // 如果这样写的话，至少在我的编译器上是没有优化的（可能是因为这里是指向堆地址的吧）
  }
  ```

- 需要用到const的时候必须要加上，否则就会像下面一样

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
        // printf("%s"， c2[1]);
        // 代码可以编译链接，但是运行的时候会发生错误（因为char*传入的值都是不能修改的）
        // 为了避免这样的错误，就必须加上const
        
        // 如果要强行过编译，可以让指针指向nullptr，表示后续的数据都是在堆上的
        char* c2 = nullptr;
        c2 = (char*)malloc(20);
        strcpy(c2, "hello");
        test(c2);
    }
    ```

- 总结：
  - 由char型数组是一段连续的存储空间，所以内容是可以改变的
  - 但是char*定义的字符串存储在字符常量区，是不可以修改的







# 不用swap交换string

- 不借助swap函数，实现交换两个string的值

- ```cpp
  void swap(string& a， string&ｂ) {
      string tmp(move(a));
      a = move(b);
      b = move(tmp);
  }
  ```







# string能否被继承

- string的析构函数不是virtual的，所以多态会造成内存泄漏的......
- 能被继承，但因析构函数不是虚函数会导致资源泄漏







# byte和char的区别





# string和char*的区别

const char*的优点

- 适配性更好，C语言和C++都适用
- 效率更高，当传递的是"xxxx"这种串时，string方式会自动创建出个临时对象，临时对象的创建和销毁也是比较耗费性能的
- 还是效率，string占用的空间比const char*更大



string的优点

- 方便，不需要关心是否释放相关内存，不需要担心内存泄漏问题
- 有些string是const char*不能替代的，比如一个string中间有'\0'，使用const char *作为参数传递过去会被截断的，也就不符合需求





有关string的移动构造函数
