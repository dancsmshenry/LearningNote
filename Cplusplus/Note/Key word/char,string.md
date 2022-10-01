# char

- char的=是逐个逐个字符匹配的（包括\0）



## char[]和char*

- char* 的本质是 const char* 

  - 即指向的数据是放在字符常量区的，如果出现两个char* 所指向的数据相同，那么就代表它们指向同一个地址

  - 在cpp中最后在前面加上const，否则会warning

  - 会在字符串最后默认加上\0

  - ```cpp
    const char* s1 = "abc";
    sizeof s1; // 记录的是指针的大小
    strlen(s1);// 记录的是字符串删掉\0的长度
    ```

- char[]的本质是char* const

  - 是一个字符数组

  - 会在字符串最后默认加上\0（但是char[]是可以修改最后那个字符的；所以如果擅自修改最后一个字符，在使用strcpy等函数时就会出错）

  - sizeof(char[])会统计所有字符数

  - ```cpp
    char s1[4] = "abc";
    sizeof s1; // 记录的是字符数组的大小
    strlen(s1);// 记录的是字符串删掉\0的长度
    
    char s2[] = "dsfsdf";// 不能被[]蒙骗为指针，实际上还是一个数组..（可变的）
    void test(char a[]){
        std::cout << sizeof(a) << std::endl;//	z
    }
    ```





一些比较奇怪的现象

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
      // 如果这样写的话，至少在我的编译器上是没有优化的（我认为可能是因为strcpy是按值拷贝的；并且编译器没有足够的智能做优化）
      //	从这里看实际上是p1和p2是指向了一块申请了的内存空间，而这个内存空间是在堆上申请的，
  }
  ```



记录一下同花顺笔试中出现的问题

- ```cpp
  char string[100], str1[10];
  for (int i = 0; i < 10; ++ i) {
      str1[i] = 'a';
  }
  strcpy(string, str1);//	strcpy是要读到\0才会停止的，而这里没有\0，所以就会内存越界
  ```



输出

- ```cpp
  void test1() {
      char c[5] = {'a', 'b', '\0', 'c', '\0'};
      for (auto& c1: c) {
          cout << c1;
      }
      // abc
      // 而读到\0x
  }
  
  void test2() {
      const char *c1 = "ab\0c\0";
      //	cout << c1; // cc1指针是不能直接打印的.
      // ab
      // char*读到\0就会停下来
  }
  ```

- 



## string和char*

const char*的优点

- 适配性更好，C语言和C++都适用
- 效率更高，当传递的是"xxxx"这种串时，string方式会自动创建出个临时对象，临时对象的创建和销毁也是比较耗费性能的
- 同时string占用的空间比const char*更大



string的优点

- 方便，不需要关心是否释放相关内存，不需要担心内存泄漏问题
- 有些string是const char*不能替代的，比如一个string中间有'\0'，使用const char *作为参数传递过去会被截断的，也就不符合需求







# string

- 一些编译器会采取**SSO**（small string optimization）的优化，小型字符串会存储在std::string对象的某个缓冲区中，而不使用堆上分配的内存

- string继承自basic_string，其实是对char * 进行了封装，封装的string包含了char*数组，容量，长度等属性

- string可以进行动态扩展，在每次扩展的时候另外申请一块原空间大小两倍的空间，然后将原字符串拷贝过去，并加上新增的内容

- string的字符串后面不加上\0

- ```cpp
  //	string转const char*
  string s = “abc”; 
  const char* c_s = s.c_str(); 
  
  //	char* 转string
  char* c = “abc”; 
  string s(c); 
  ```




## 不用swap交换string

- ```cpp
  void swap(string& a， string&ｂ) {
      string tmp(move(a));
      a = move(b);
      b = move(tmp);
  }
  ```



## string能否被继承

- 能被继承，但string的析构函数不是虚函数，因此会导致资源泄漏



## move函数





char32_t u2[] = u"hello";

char16_t u4 = u8"hello";

char u3[] = u"hello";

char utf8[] = u8"hello";
