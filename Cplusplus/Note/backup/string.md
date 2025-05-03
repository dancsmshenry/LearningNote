对于字符串，strlen 始终记录字符长度（即使字符数组很长，依然只计算有效字符的长度），而 sizeof 则记录字符长度 + 1

```C++
std::cout << sizeof("ab") << std::endl; // 3 as string（ab\0）
std::cout << sizeof('ab') << std::endl; // 4 as byte（只要是多于1个字符，得到的结果都是4）
std::cout << strlen("ab") << std::endl; // 2 as byte（ab）
const char *c = "123456";
std::cout << strlen(c) << std::endl; // 6 as string
std::cout << sizeof(c) << std::endl; // 8（length of pointer）

char s1[100] = "1234567";
std::cout << strlen(s1) << std::endl;
// 7 ，not 8 or 100

////////////////////////////

char aaa[] = "sdfsdfsdfds";
std::cout << sizeof(aaa) << std::endl; // 4

int getlength(char srt[]) {
    return sizeof srt;
}

std::cout << getlength(aaa) << std::endl; // 8
```

<br/>

<br/>

关于 char* 创建的字符串和 char[] 创建的字符串的区别

注：所以一般 段错误，都是读到了不可访问的内存吗？

```C++
char *c1 = "2e21"; // only read, can not write
char c2[5] = "2e21"; // can read and write
// 注：这里存放字符串时，要给最后面的 /0 预留一位空间

*++c1 = '1'; // can compile but not run, segmentation fault

*++c2 = '1'; // can not compile

*c2 = '1'; // can compile and run

char c3[] = "sdf";
c3[0] = 'd';
```

<br/>

<br/>

关于 char 的一个比较坑的地方

```C++
for (char i = 0; i < 129; ++ i) {
    std::cout << "test" << std::endl;
}
// 会无限循环（char [-127,128]）
```

<br/>

<br/>

关于string 的 find 函数：

对于 string 中的 find 函数，如果找不到当前需要找的字符，那么就会返回一个 *18446744073709551615，即 2 的 64 次方 减一

```c++
static const size_type npos = static_cast<size_type>(-1);

std::string str("t1-t2-t3")

while (str.find("-") < str.size()) {
    std::cout << str.substr(str.find("-")) << std::endl;
    str = str.substr(str.find("-") + 1);
}
```



对于 char * 的类型，新建的时候要用 new char[]，删除的时候要用 delete[]

PS：被 CSDN 坑了，只要不加 [] 的都是会内存泄漏（可以用 asan 检测出来）

```c++
#include <cstring>

class Person {
public:
  char *name;
  int age;
  int *a;

  Person(const char *name, int age) {
    this->name = new char[strlen(name) + 1];
    a = new int[10];
    strcpy(this->name, name);
    this->age = age;
  }

  ~Person() {
    delete[] this->name;
    delete[] a;
  }
};

int main() { Person p1("dsf", 1); }

```

