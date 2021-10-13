## 第2章 变量和基本类型

### 2.1基本内置类型

- 基本算术类型

  | 类型      | 含义                   |
  | --------- | ---------------------- |
  | bool      | 布尔类型               |
  | char      | 字符                   |
  | short     | 短整型                 |
  | int       | 整型                   |
  | long      | 长整型（最小尺寸32位） |
  | long long | 长整型（最小尺寸64位） |
  | float     | 单精度浮点数           |
  | double    | 双精度浮点数           |

- 带符号类型和无符号类型

  - 类型`int、short、long和long long`都是带符号的，通过在这些类型名前添加unsigned就可以得到无符号类型
  - 而字符型则被分为`char、signed char和unsigned char`
  - 如果表达式里既有带符号类型又有无符号类型，当带符号类型取值为负时会出现异常结果，这是因为带符号数会自动地转换成无符号数

- 类型转换

  - 浮点数和整数：
    - 浮点数->整数，结果仅保留浮点数中小数点之前的部分
    - 整数->浮点数，小数部分记为0
  - 布尔类型：
    - 非布尔类型->布尔类型

- 字面值常量

  - 字符和字符串字面值
    - 用单引号括起来的一个字符为char型字面值，双引号括起来的零个或多个字符为字符串字面值
  - 转义序列
    - 在c++语言中有特殊含义的字符是不能直接使用的，在这些情况下需要用到转义序列
    - 转义序列均以反斜杠开始，如`\n`表示换行，`\"`表示双引号，`\'`表示单引号
  - 指定字面值类型
    - 通过前缀或后缀可以改变整型、浮点型和字符型字面值的默认类型
    - 如对于整型，前缀`ll`可以表示`long long`，前缀`l`可以表示`long`



### 2.2变量

- 命名规范
  - 需要由字母、数字和下划线组成，同时对大小写敏感
  - 变量名一般用小写字母，类名一般用大写字母开头
- 变量声明和定义的关系
  - **声明**使得名字为程序所知，**定义**负责创建于名字关联的实体
  - 变量能且只能被定义一次，但是可以被多次声明

```c++
extern int i;//是声明i而不是定义i
int j;//声明并定义了j
```

- 初始值
  - 当对象在创建时候获得了一个特定的值，这个对象就被初始化了
  - 初始化不是赋值，赋值是指把对象的当前值擦除，而以一个新值代替
- 初始化的几种方式

```c++
int units_sold = 0;
int units_sold = {0};
int units_sold{0};
int units_sold(0);
```



### 2.3复合类型

- 引用
  - 引用即为对象起了另外一个名字
  - 引用通常是将声明写成`&d`的形式来定义引用类型，其中d是声明的变量名
  - 因为引用本身不是一个对象，所以不能定义引用的引用
  - 引用类型的初始值必须是一个对象，且类型要与原对象相同

```c++
int a = 1024;
int &a1 = a;//a1是a的一个引用
cout << a1 << endl;//1024
a ++ ;
cout << a1 << endl;//1025，可以看出引用的本质
```

- 指针
  - 指针本身是一个对象，允许对指针赋值或拷贝，所以可以指向不同的对象（但是指针类型要与指向的对象的类型相同）
  - 指针的含义是存放着某个对象的地址
  - 指针无须再定义时赋值
  - 通常是将声明符写成`*d`的形式，其中d是变量名，如果一条语句中定义了几个指针变量，每个变量前面都要有`*`

```c++
int a = 2047;
int *a1;//定义一个指向int型对象的指针

a1 = &a;//a1存放a的地址，也可以说a1是指向a的指针
//&是取地址符，用于获取对象的具体地址
//注意：&在定义的类型的后买你是声明的一部分，而在表达式中是取地址符

cout << *a1 << endl;//2047
//*是解引用符号，用于获取指针所指向的对象的值
//注意：*在定义中的类型的后面是声明的一部分，而在表达式中的是解引用符

*a1 = 0;//通过对*a1进行赋值，从而改变a的值


int *p1 = 0;
int *p2 = nullptr;
//上面两条语句都表示空指针（需要首先#include <cstdlib>）

int *pi;
int zero = 0;
p1 = zero;//虽然zero=0，但还是不可以把int变量直接赋给指针


void *pv = &obj;//这里定义的是一个特殊的指针类型，obj可以指向任意类型的对象，即pv可以存放任意类型指针


int ival = 1024;
int *pi = &ival;
int **ppi = &pi;//可以定义指向指针的指针

int i = 42;
int *p;
int * &r = p;//r是一个对指针p的引用
```



### 2.4`const`限定符

- `const`是指把一个变量变为常量

- 与define的区别
  - `const`常量有数据类型，而define定义宏常量没有数据类型
  - define宏是在预处理阶段展开，`const`常量则是编译运行阶段使用
  - define宏仅仅是展开，有几个地方使用则展开几次，不分配内存；`const`常量会在内存中分配地址（可以是堆中也可以是栈中）
  - define定义的常量在内存中有若干个拷贝，`const`定义的常量在程序运行过程中只有一份拷贝，甚至不为普通`const`常量分配存储空间，而是将它们保存在符号表中，相当于没有了读内存的操作，使得效率也很高



### 2.5 处理类型

- 类型别名

  - 是某种类型的同义词，使用类型别名可以使复杂的类型名字变得简洁明了

  ```c++
  typeof double wages;//typeof命名
  using SH = short;//用using命名，简称别名声明
  ```

  - 和define的区别：
    - #define是 C 中定义的语法, typedef 是 C++ 中定义的语法, 二者在 C++ 中可以通用
    - 但 #define 成了预编译指令, typedef 当成语句处理

- `auto`类型说明符

  - 有时声明变量的时候很难知道表达式的类型，就可以用`auto`来让编辑器替我们分析所属类型
  - 所声明的变量一定有初始值
  - 可以同时声明多个变量，但数据类型一定要相同

```c++
int i = 1;
auto j = i * 2047;//即j的类型就是int
```

- `decltype`类型指示符
  - 希望从表达式的类型推断处要定义的变量的类型，但是不想用该表达式的值初始化变量

```c++
decltype(f()) sum = x;//sum的类型就是函数f的返回类型
```



### 2.6自定义数据类型

- 定义一个结构体

  ```c++
  struct Sales_data{
    	string bookNo;
      unsigned units_sold = 0;
      double revence = 0.0;
  };
  ```

- 使用结构体中的

  ```c++
  Sales_data data1, data2;cin >> data1.bookNo >> data1.units_sold;
  ```




# 第三章 字符串、向量和数组

### 3.1命名空间的`using`声明

- 使用某个命名空间：例如 `using std::cin`表示使用命名空间`std`中的名字`cin`。
- 头文件中不应该包含`using`声明
  - 这是因为头文件的内容会拷贝到所有引用它的文件中，可能会引起名字的冲突

### 3.2标准库类型`string`

- `string`表示可变长的字符序列

- 注意要用头文件`#include <string>`

- 定义和初始化string对象

  - | 方式                  | 解释                                                    |
    | --------------------- | ------------------------------------------------------- |
    | `string s1`           | 默认初始化，`s1`是个空字符串                            |
    | `string s2(s1)`       | `s2`是`s1`的副本                                        |
    | `string s2 = s1`      | 等价于`s2(s1)`，`s2`是`s1`的副本                        |
    | `string s3("value")`  | `s3`是字面值“value”的副本，除了字面值最后的那个空字符外 |
    | `string s3 = "value"` | 等价于`s3("value")`，`s3`是字面值"value"的副本          |
    | `string s4(n, 'c')`   | 把`s4`初始化为由连续`n`个字符`c`组成的串                |

  - 拷贝初始化：使用等号`=`将一个已有的对象拷贝到正在创建的对象

  - 直接初始化：通过括号给对象赋值

- `string`的操作：

  - | 操作                 | 解释                                                         |
    | -------------------- | ------------------------------------------------------------ |
    | `os << s`            | 将`s`写到输出流`os`当中，返回`os`                            |
    | `is >> s`            | 从`is`中读取字符串赋给`s`，字符串以空白分割，返回`is`        |
    | `getline(is, s)`     | 从`is`中读取一行赋给`s`，返回`is`                            |
    | `s.empty()`          | `s`为空返回`true`，否则返回`false`                           |
    | `s.size()`           | 返回`s`中字符的个数                                          |
    | `s[n]`               | 返回`s`中第`n`个字符的引用，位置`n`从0计起                   |
    | `s1+s2`              | 返回`s1`和`s2`连接后的结果                                   |
    | `s1=s2`              | 用`s2`的副本代替`s1`中原来的字符                             |
    | `s1==s2`             | 如果`s1`和`s2`中所含的字符完全一样，则它们相等；`string`对象的相等性判断对字母的大小写敏感 |
    | `s1!=s2`             | 同上                                                         |
    | `<`, `<=`, `>`, `>=` | 利用字符在字典中的顺序进行比较，且对字母的大小写敏感         |

  - 执行读操作`>>`：忽略掉开头的空白（包括空格、换行符和制表符），直到遇到下一处空白为止

  - `getline`：读取一整行，**包括空白符**

- 处理string对象中的字符

  - `cctype`头文件中定义了一组标准函数：

  - | 函数          | 解释                                                         |
    | ------------- | ------------------------------------------------------------ |
    | `isalnum(c)`  | 当`c`是字母或数字时为真                                      |
    | `isalpha(c)`  | 当`c`是字母时为真                                            |
    | `iscntrl(c)`  | 当`c`是控制字符时为真                                        |
    | `isdigit(c)`  | 当`c`是数字时为真                                            |
    | `isgraph(c)`  | 当`c`不是空格但可以打印时为真                                |
    | `islower(c)`  | 当`c`是小写字母时为真                                        |
    | `isprint(c)`  | 当`c`是可打印字符时为真                                      |
    | `ispunct(c)`  | 当`c`是标点符号时为真                                        |
    | `isspace(c)`  | 当`c`是空白时为真（空格、横向制表符、纵向制表符、回车符、换行符、进纸符） |
    | `isupper(c)`  | 当`c`是大写字母时为真                                        |
    | `isxdigit(c)` | 当`c`是十六进制数字时为真                                    |
    | `tolower(c)`  | 当`c`是大写字母，输出对应的小写字母；否则原样输出`c`         |
    | `toupper(c)`  | 当`c`是小写字母，输出对应的大写字母；否则原样输出`c`         |

- 遍历字符串：

  - 使用 `for (auto c: str)`，或者 `for (auto &c: str)`使用引用直接改变字符串中的字符



### 3.3标准库类型`vector`

- vector是一个容器，也是一个类模板

- 注意头文件`#include <vector>` 然后 `using std::vector`

- 容器：包含其他对象。

- 类模板：本身不是类，但可以**实例化instantiation**出一个类。 `vector`是一个模板， `vector<int>`是一个类型

- 通过将类型放在类模板名称后面的**尖括号**中来指定**类型**，如`vector<int> ivec`

- 初始化`vector`对象的方法

  - | 方法                        | 解释                                                         |
    | --------------------------- | ------------------------------------------------------------ |
    | `vector<T> v1`              | `v1`是一个空`vector`，它潜在的元素是`T`类型的，执行默认初始化 |
    | `vector<T> v2(v1)`          | `v2`中包含有`v1`所有元素的副本                               |
    | `vector<T> v2 = v1`         | 等价于`v2(v1)`，`v2`中包含`v1`所有元素的副本                 |
    | `vector<T> v3(n, val)`      | `v3`包含了n个重复的元素，每个元素的值都是`val`               |
    | `vector<T> v4(n)`           | `v4`包含了n个重复地执行了值初始化的对象                      |
    | `vector<T> v5{a, b, c...}`  | `v5`包含了初始值个数的元素，每个元素被赋予相应的初始值       |
    | `vector<T> v5={a, b, c...}` | 等价于`v5{a, b, c...}`                                       |

- 列表初始化： `vector<string> v{"a", "an", "the"};`

- `v.push_back(e)` 在尾部增加元素

- 其他`vector`的操作：

- | 操作               | 解释                                                         |
  | ------------------ | ------------------------------------------------------------ |
  | `v.emtpy()`        | 如果`v`不含有任何元素，返回真；否则返回假                    |
  | `v.size()`         | 返回`v`中元素的个数                                          |
  | `v.push_back(t)`   | 向`v`的尾端添加一个值为`t`的元素                             |
  | `v[n]`             | 返回`v`中第`n`个位置上元素的**引用**                         |
  | `v1 = v2`          | 用`v2`中的元素拷贝替换`v1`中的元素                           |
  | `v1 = {a,b,c...}`  | 用列表中元素的拷贝替换`v1`中的元素                           |
  | `v1 == v2`         | `v1`和`v2`相等当且仅当它们的元素数量相同且对应位置的元素值都相同 |
  | `v1 != v2`         | 同上                                                         |
  | `<`,`<=`,`>`, `>=` | 以字典顺序进行比较                                           |

- 范围`for`语句内不应该改变其遍历序列的大小。

- `vector`对象（以及`string`对象）的下标运算符，只能对确知已存在的元素执行下标操作，不能用于添加元素（所以才有`push_back`）

### 3.4迭代器介绍

- 所有标准库容器都可以使用迭代器

- 类似于指针类型，迭代器也提供了对对象的间接访问

- `auto b = v.begin();`返回指向第一个元素的迭代器。

- `auto e = v.end();`返回指向最后一个元素的下一个（哨兵，尾后,one past the end）的迭代器（off the end）

- 如果容器为空， `begin()`和 `end()`返回的是同一个迭代器，都是尾后迭代器

- 使用解引用符`*`访问迭代器指向的元素

- **容器**：可以包含其他对象；但所有的对象必须类型相同

- **迭代器（iterator）**：每种标准容器都有自己的迭代器。`C++`倾向于用迭代器而不是下标遍历元素

- **const_iterator**：只能读取容器内元素不能改变

- **箭头运算符**： 解引用 + 成员访问，`it->mem`等价于 `(*it).mem`

- **谨记**：但凡是使用了迭代器的循环体，都不要向迭代器所属的容器添加元素

- 标准容器迭代器的运算符:

  - | 运算符           | 解释                                   |
    | ---------------- | -------------------------------------- |
    | `*iter`          | 返回迭代器`iter`所指向的**元素的引用** |
    | `iter->mem`      | 等价于`(*iter).mem`                    |
    | `++iter`         | 令`iter`指示容器中的下一个元素         |
    | `--iter`         | 令`iter`指示容器中的上一个元素         |
    | `iter1 == iter2` | 判断两个迭代器是否相等                 |

- 迭代器运算

  - | 运算符               | 解释                                                         |
    | -------------------- | ------------------------------------------------------------ |
    | `iter + n`           | 迭代器加上一个整数值仍得到一个迭代器，迭代器指示的新位置和原来相比向前移动了若干个元素。结果迭代器或者指示容器内的一个元素，或者指示容器尾元素的下一位置。 |
    | `iter - n`           | 迭代器减去一个证书仍得到一个迭代器，迭代器指示的新位置比原来向后移动了若干个元素。结果迭代器或者指向容器内的一个元素，或者指示容器尾元素的下一位置。 |
    | `iter1 += n`         | 迭代器加法的复合赋值语句，将`iter1`加n的结果赋给`iter1`      |
    | `iter1 -= n`         | 迭代器减法的复合赋值语句，将`iter2`减n的加过赋给`iter1`      |
    | `iter1 - iter2`      | 两个迭代器相减的结果是它们之间的距离，也就是说，将运算符右侧的迭代器向前移动差值个元素后得到左侧的迭代器。参与运算的两个迭代器必须指向的是同一个容器中的元素或者尾元素的下一位置。 |
    | `>`、`>=`、`<`、`<=` | 迭代器的关系运算符，如果某迭代器                             |



### 3.5数组

- vector的低配版，长度固定

- 初始化：`char input_buffer[buffer_size];`，长度必须是`const`表达式，或者不写
- 数组不允许直接赋值给另一个数组
- 数组的访问
  - 数组下标的类型：`size_t` 。
  - 字符数组的特殊性：结尾处有一个空字符，如 `char a[] = "hello";` 。
- 用数组初始化 `vector`： `int a[] = {1,2,3,4,5}; vector<int> v(begin(a), end(a));` 

- 与指针的关系
  - 使用数组时，编译器一般会把它转换成指针
  - 标准库类型限定使用的下标必须是无符号类型，而内置的下标可以处理负值
  - **指针访问数组**：在表达式中使用数组名时，名字会自动转换成指向数组的第一个元素的指针

- C风格字符串
  - 从C继承来的字符串
  - 用空字符结束（`\0`）
  - 对大多数应用来说，使用标准库 `string`比使用C风格字符串更安全、更高效
  - 获取 `string` 中的 `cstring` ： `const char *str = s.c_str();` 
  - C标准库String函数，定义在`<cstring>` 中：

| 函数             | 介绍                                                         |
| ---------------- | ------------------------------------------------------------ |
| `strlen(p)`      | 返回`p`的长度，空字符不计算在内                              |
| `strcmp(p1, p2)` | 比较`p1`和`p2`的相等性。如果`p1==p2`，返回0；如果`p1>p2`，返回一个正值；如果`p1<p2`，返回一个负值。 |
| `strcat(p1, p2)` | 将`p2`附加到`p1`之后，返回`p1`                               |
| `strcpy(p1, p2)` | 将`p2`拷贝给`p1`，返回`p1`                                   |

### 3.6多维数组

- 多维数组的初始化： `int ia[3][4] = {{0,1,2,3}, ...}`

- 使用范围for语句时，除了最内层的循环外，其他所有循环的控制变量都应该是引用类型

- 动态数组

  - 使用 `new`和 `delete`表达和c中`malloc`和`free`类似的功能，即在堆（自由存储区）中分配存储空间

  - 定义： `int *pia = new int[10];` 10可以被一个变量替代

  - 释放： `delete [] pia;`，注意不要忘记`[]`第三章 字符串、向量和数组

    ### 3.1命名空间的`using`声明

    - 使用某个命名空间：例如 `using std::cin`表示使用命名空间`std`中的名字`cin`。
    - 头文件中不应该包含`using`声明
      - 这是因为头文件的内容会拷贝到所有引用它的文件中，可能会引起名字的冲突

    ### 3.2标准库类型`string`

    - `string`表示可变长的字符序列

    - 注意要用头文件`#include <string>`

    - 定义和初始化string对象

      - | 方式                  | 解释                                                    |
        | --------------------- | ------------------------------------------------------- |
        | `string s1`           | 默认初始化，`s1`是个空字符串                            |
        | `string s2(s1)`       | `s2`是`s1`的副本                                        |
        | `string s2 = s1`      | 等价于`s2(s1)`，`s2`是`s1`的副本                        |
        | `string s3("value")`  | `s3`是字面值“value”的副本，除了字面值最后的那个空字符外 |
        | `string s3 = "value"` | 等价于`s3("value")`，`s3`是字面值"value"的副本          |
        | `string s4(n, 'c')`   | 把`s4`初始化为由连续`n`个字符`c`组成的串                |

      - 拷贝初始化：使用等号`=`将一个已有的对象拷贝到正在创建的对象

      - 直接初始化：通过括号给对象赋值

    - `string`的操作：

      - | 操作                 | 解释                                                         |
        | -------------------- | ------------------------------------------------------------ |
        | `os << s`            | 将`s`写到输出流`os`当中，返回`os`                            |
        | `is >> s`            | 从`is`中读取字符串赋给`s`，字符串以空白分割，返回`is`        |
        | `getline(is, s)`     | 从`is`中读取一行赋给`s`，返回`is`                            |
        | `s.empty()`          | `s`为空返回`true`，否则返回`false`                           |
        | `s.size()`           | 返回`s`中字符的个数                                          |
        | `s[n]`               | 返回`s`中第`n`个字符的引用，位置`n`从0计起                   |
        | `s1+s2`              | 返回`s1`和`s2`连接后的结果                                   |
        | `s1=s2`              | 用`s2`的副本代替`s1`中原来的字符                             |
        | `s1==s2`             | 如果`s1`和`s2`中所含的字符完全一样，则它们相等；`string`对象的相等性判断对字母的大小写敏感 |
        | `s1!=s2`             | 同上                                                         |
        | `<`, `<=`, `>`, `>=` | 利用字符在字典中的顺序进行比较，且对字母的大小写敏感         |

      - 执行读操作`>>`：忽略掉开头的空白（包括空格、换行符和制表符），直到遇到下一处空白为止

      - `getline`：读取一整行，**包括空白符**

    - 处理string对象中的字符

      - `cctype`头文件中定义了一组标准函数：

      - | 函数          | 解释                                                         |
        | ------------- | ------------------------------------------------------------ |
        | `isalnum(c)`  | 当`c`是字母或数字时为真                                      |
        | `isalpha(c)`  | 当`c`是字母时为真                                            |
        | `iscntrl(c)`  | 当`c`是控制字符时为真                                        |
        | `isdigit(c)`  | 当`c`是数字时为真                                            |
        | `isgraph(c)`  | 当`c`不是空格但可以打印时为真                                |
        | `islower(c)`  | 当`c`是小写字母时为真                                        |
        | `isprint(c)`  | 当`c`是可打印字符时为真                                      |
        | `ispunct(c)`  | 当`c`是标点符号时为真                                        |
        | `isspace(c)`  | 当`c`是空白时为真（空格、横向制表符、纵向制表符、回车符、换行符、进纸符） |
        | `isupper(c)`  | 当`c`是大写字母时为真                                        |
        | `isxdigit(c)` | 当`c`是十六进制数字时为真                                    |
        | `tolower(c)`  | 当`c`是大写字母，输出对应的小写字母；否则原样输出`c`         |
        | `toupper(c)`  | 当`c`是小写字母，输出对应的大写字母；否则原样输出`c`         |

    - 遍历字符串：

      - 使用 `for (auto c: str)`，或者 `for (auto &c: str)`使用引用直接改变字符串中的字符

    

    ### 3.3标准库类型`vector`

    - vector是一个容器，也是一个类模板

    - 注意头文件`#include <vector>` 然后 `using std::vector`

    - 容器：包含其他对象。

    - 类模板：本身不是类，但可以**实例化instantiation**出一个类。 `vector`是一个模板， `vector<int>`是一个类型

    - 通过将类型放在类模板名称后面的**尖括号**中来指定**类型**，如`vector<int> ivec`

    - 初始化`vector`对象的方法

      - | 方法                        | 解释                                                         |
        | --------------------------- | ------------------------------------------------------------ |
        | `vector<T> v1`              | `v1`是一个空`vector`，它潜在的元素是`T`类型的，执行默认初始化 |
        | `vector<T> v2(v1)`          | `v2`中包含有`v1`所有元素的副本                               |
        | `vector<T> v2 = v1`         | 等价于`v2(v1)`，`v2`中包含`v1`所有元素的副本                 |
        | `vector<T> v3(n, val)`      | `v3`包含了n个重复的元素，每个元素的值都是`val`               |
        | `vector<T> v4(n)`           | `v4`包含了n个重复地执行了值初始化的对象                      |
        | `vector<T> v5{a, b, c...}`  | `v5`包含了初始值个数的元素，每个元素被赋予相应的初始值       |
        | `vector<T> v5={a, b, c...}` | 等价于`v5{a, b, c...}`                                       |

    - 列表初始化： `vector<string> v{"a", "an", "the"};`

    - `v.push_back(e)` 在尾部增加元素

    - 其他`vector`的操作：

    - | 操作               | 解释                                                         |
      | ------------------ | ------------------------------------------------------------ |
      | `v.emtpy()`        | 如果`v`不含有任何元素，返回真；否则返回假                    |
      | `v.size()`         | 返回`v`中元素的个数                                          |
      | `v.push_back(t)`   | 向`v`的尾端添加一个值为`t`的元素                             |
      | `v[n]`             | 返回`v`中第`n`个位置上元素的**引用**                         |
      | `v1 = v2`          | 用`v2`中的元素拷贝替换`v1`中的元素                           |
      | `v1 = {a,b,c...}`  | 用列表中元素的拷贝替换`v1`中的元素                           |
      | `v1 == v2`         | `v1`和`v2`相等当且仅当它们的元素数量相同且对应位置的元素值都相同 |
      | `v1 != v2`         | 同上                                                         |
      | `<`,`<=`,`>`, `>=` | 以字典顺序进行比较                                           |

    - 范围`for`语句内不应该改变其遍历序列的大小。

    - `vector`对象（以及`string`对象）的下标运算符，只能对确知已存在的元素执行下标操作，不能用于添加元素（所以才有`push_back`）

    ### 3.4迭代器介绍

    - 所有标准库容器都可以使用迭代器

    - 类似于指针类型，迭代器也提供了对对象的间接访问

    - `auto b = v.begin();`返回指向第一个元素的迭代器。

    - `auto e = v.end();`返回指向最后一个元素的下一个（哨兵，尾后,one past the end）的迭代器（off the end）

    - 如果容器为空， `begin()`和 `end()`返回的是同一个迭代器，都是尾后迭代器

    - 使用解引用符`*`访问迭代器指向的元素

    - **容器**：可以包含其他对象；但所有的对象必须类型相同

    - **迭代器（iterator）**：每种标准容器都有自己的迭代器。`C++`倾向于用迭代器而不是下标遍历元素

    - **const_iterator**：只能读取容器内元素不能改变

    - **箭头运算符**： 解引用 + 成员访问，`it->mem`等价于 `(*it).mem`

    - **谨记**：但凡是使用了迭代器的循环体，都不要向迭代器所属的容器添加元素

    - 标准容器迭代器的运算符:

      - | 运算符           | 解释                                   |
        | ---------------- | -------------------------------------- |
        | `*iter`          | 返回迭代器`iter`所指向的**元素的引用** |
        | `iter->mem`      | 等价于`(*iter).mem`                    |
        | `++iter`         | 令`iter`指示容器中的下一个元素         |
        | `--iter`         | 令`iter`指示容器中的上一个元素         |
        | `iter1 == iter2` | 判断两个迭代器是否相等                 |

    - 迭代器运算

      - | 运算符               | 解释                                                         |
        | -------------------- | ------------------------------------------------------------ |
        | `iter + n`           | 迭代器加上一个整数值仍得到一个迭代器，迭代器指示的新位置和原来相比向前移动了若干个元素。结果迭代器或者指示容器内的一个元素，或者指示容器尾元素的下一位置。 |
        | `iter - n`           | 迭代器减去一个证书仍得到一个迭代器，迭代器指示的新位置比原来向后移动了若干个元素。结果迭代器或者指向容器内的一个元素，或者指示容器尾元素的下一位置。 |
        | `iter1 += n`         | 迭代器加法的复合赋值语句，将`iter1`加n的结果赋给`iter1`      |
        | `iter1 -= n`         | 迭代器减法的复合赋值语句，将`iter2`减n的加过赋给`iter1`      |
        | `iter1 - iter2`      | 两个迭代器相减的结果是它们之间的距离，也就是说，将运算符右侧的迭代器向前移动差值个元素后得到左侧的迭代器。参与运算的两个迭代器必须指向的是同一个容器中的元素或者尾元素的下一位置。 |
        | `>`、`>=`、`<`、`<=` | 迭代器的关系运算符，如果某迭代器                             |

    

    ### 3.5数组

    - vector的低配版，长度固定

    - 初始化：`char input_buffer[buffer_size];`，长度必须是`const`表达式，或者不写
    - 数组不允许直接赋值给另一个数组
    - 数组的访问
      - 数组下标的类型：`size_t` 。
      - 字符数组的特殊性：结尾处有一个空字符，如 `char a[] = "hello";` 。
    - 用数组初始化 `vector`： `int a[] = {1,2,3,4,5}; vector<int> v(begin(a), end(a));` 

    - 与指针的关系
      - 使用数组时，编译器一般会把它转换成指针
      - 标准库类型限定使用的下标必须是无符号类型，而内置的下标可以处理负值
      - **指针访问数组**：在表达式中使用数组名时，名字会自动转换成指向数组的第一个元素的指针

    - C风格字符串
      - 从C继承来的字符串
      - 用空字符结束（`\0`）
      - 对大多数应用来说，使用标准库 `string`比使用C风格字符串更安全、更高效
      - 获取 `string` 中的 `cstring` ： `const char *str = s.c_str();` 
      - C标准库String函数，定义在`<cstring>` 中：

    | 函数             | 介绍                                                         |
    | ---------------- | ------------------------------------------------------------ |
    | `strlen(p)`      | 返回`p`的长度，空字符不计算在内                              |
    | `strcmp(p1, p2)` | 比较`p1`和`p2`的相等性。如果`p1==p2`，返回0；如果`p1>p2`，返回一个正值；如果`p1<p2`，返回一个负值。 |
    | `strcat(p1, p2)` | 将`p2`附加到`p1`之后，返回`p1`                               |
    | `strcpy(p1, p2)` | 将`p2`拷贝给`p1`，返回`p1`                                   |

    ### 3.6多维数组

    - 多维数组的初始化： `int ia[3][4] = {{0,1,2,3}, ...}`
    - 使用范围for语句时，除了最内层的循环外，其他所有循环的控制变量都应该是引用类型

    - 动态数组
      - 使用 `new`和 `delete`表达和c中`malloc`和`free`类似的功能，即在堆（自由存储区）中分配存储空间
      - 定义： `int *pia = new int[10];` 10可以被一个变量替代
      - 释放： `delete [] pia;`，注意不要忘记`[]`



## 第4章 表达式

### 4.1 基础

- 重载运算符：当运算符作用在类类型的运算对象时，用户可以自行定义其含义
- 左值和右值：
  - `C`：左值**可以**在表达式左边，右值不能
  - `C++`：当一个对象被用作**右值**的时候，用的是对象的**值**（内容）
  - 被用做**左值**时，用的是对象的**身份**（在内存中的位置）



### 4.2算术运算符

```c++
a + b;
a - b;
a * b;

a / b;//代表的是整除，即得到的是一个整数
{
    21 / -5 = -4;
    -21 / -8 = 2;
}

a % b;//求余，注意存在负数的情况
{
    21 % -5 = 1;
    -21 % -8 = -5;
}

+a;//正号
-a;//负号
```



### 4.3 逻辑和关系运算符

```c++
a < b;//小于
a <= b;//小于等于
a > b;//大于
a >= b;//大于等于
a == b;//相等
a != b;//不相等
a && b;//表示逻辑关系中的和，当且仅当二者都为真的时候才为真（所以前面是假的时候就不会继续往下算了）
a || b;//表示逻辑关系中的或，当且仅当二者都为假的时候才为假
! a;//表示逻辑关系中的非，注意只要a不是0，!a一定为假
```



### 4.4 赋值运算符

- 如果赋值运算的左右侧运算对象类型不同，则右侧运算对象将转换成左侧运算对象的类型（参考类型转换）
- 赋值运算符满足右结合律，这点和其他二元运算符不一样。 `ival = jval = 0;`等价于`ival = (jval = 0);`



### 4.5 递增和递减运算符

```c++
a ++;//表示a会先进行部分操作，然后再在原来的基础上加上1
++ b;//表示先让b在原来的基础上加上1，然后再进行操作（优先使用这个，参考原理，迭代器）
a --;//同理
-- b://同理
```



### 4.6 成员访问运算符

```c++
string s1 = "a string", *p = &s1;
auto n = s1.size();//点运算符获取类对象的一个成员
n = (*p).size();//运行p所指对象的size成员
n = p -> size();//与上一句等价
```



### 4.7 条件运算符

```c++
c = (a > b) ? a : b;//等价于一个if语句
```



### 4.8 位运算符

```c++
a = 1;
b = 0;
~a = 0;//位取反符号，先将数值转化为二进制数，然后再全部取反位
a >> 1 = 0;//右移位，先将数值转化为二进制数，然后全体向右边移一位，即除以二
a << 1 = 2;//左移位，先将数值转化为二进制数，然后全体向左边移一位，即乘以二
a & b = 0;//先将数值转化为二进制数，然后按照逻辑关系中的和运算进行比较
a | b = 1;//同理
a ^ b = 1;//同理，不过只有二者不同的时候才会为1
```



### 4.9 sizeof运算符

- 返回一条表达式或一个类型名字所占的字节数，返回的类型是 `size_t`
- `sizeof (type)`和 `sizeof expr`



### 4.10 逗号运算符



### 4.11 类型转换

- 隐式转换
  - 比 `int`类型小的整数值先提升为较大的整数类型
  - 条件中，非布尔转换成布尔
  - 初始化中，初始值转换成变量的类型
  - 算术运算或者关系运算的运算对象有多种类型，要转换成同一种类型



## 第5章 语句

### 5.1 简单语句

- 空语句：只有一个分号

```c++
;
```

- 复合语句块：用花括号 `{}`包裹起来的语句和声明的序列。一个块就是一个作用域

```c++
while (val <= 10){
    sum += val;
    ++ val;
}
```

- 空块

```c++
while (cin >> s && s!= sought){
    
}
```

- 注意：不一定所有的语句都会以分号结尾

```c++
for (int i = 0; i < 100; ++ i){
    i1 = i * i, i2 = i * i * i;
}
```



### 5.2 语句作用域



### 5.3 条件语句

- `if`语句

  - ```c++
    if (val < 0){
        
    }
    else{
        
    }//第一种情况
    
    if (val < 0){
        
    }
    else if (val == 0){
        
    }
    else if (val > 10){
        
    }
    else{
        
    }//第二种情况
    ```

  - 当有多个else和if的时候遵循的规则：else与离它最近的尚未匹配的if匹配

- `switch`语句

  - ```c++
    unsigned a = 0, e = 0, i = 0, o = 0, u = 0;
    char ch;
    while (cin >> vh){
        switch(ch){
            case 'a':
                a ++ ;
                break;
            case 'e':
                e ++ ;
                break;
            case 'i':
                i ++ ;
                break;
            case 'o':
                o ++ ;
                break;
            case 'u':
                u ++ ;
                break;
        }
    }
    ```

  - default标签：如果上面的情况都不符合，就执行这个

    - ```c++
      switch (ch){
          case'a':case 'e':case'i':case'o':case'u':
              ++ vowelCnt;
              break;
          default:
              ++ otherCnt;//当ch不属于aeioou其中的任何一个的时候
              break;
      }
      ```



### 5.4 迭代语句

- while语句

```c++
while (a != 100){
    sum += a;
    ++ a;
}
//()里面的值为布尔值
```

- 传统的for语句

```c++
for (int i = 0; i < 100; i ++ ){    sum += i;}//(, , )三部分组成：声明语句，条件判断语句和操作语句//这三个语句都可以为空语句
```

- 范围for语句

```c++
vector<int> v = {0, 1, 2, 3, 4}for (auto &r : v){    r *= 2;//对于v中的每个元素，都翻倍}//等价于for (auto beg = v.begin(), end = v.end())
```

- do while语句

```c++
do{    //statement}while (condition);
```



### 5.5 跳转语句

- break语句
  - 终止离它最近的while、do while、for或者switch语句，并从这些语句之后的第一条语句执行

- continue语句
  - 终止最近的循环中的当前迭代并立即开始下一次迭代

- goto语句
  - 基本不用这个语句
    - 程序的可读性会被降低（从上往下读，然后还有时不时往回看），同时用不好会使程序逻辑混乱



### 5.6 TRY语句块和异常处理

- throw表达式

  - 异常检测部分使用 `throw`表达式来表示它遇到了无法处理的问题。我们说 `throw`引发 `raise`了异常

  - ```c++
    //首先检查两条语句是否相同if (item1.isbn() != item2.isbn())    throw runtime_error("Data must refer to same ISBN");cout << item1 + item2 << endl;
    ```

- try语句块

  - 以 `try`关键词开始，以一个或多个 `catch`字句结束。 `try`语句块中的代码抛出的异常通常会被某个 `catch`捕获并处理。 `catch`子句也被称为异常处理代码

  - ```c++
    try{    //填写需要测试的语句} catch (出现了什么异常){    //出现该异常后需要执行的操作}
    ```

- 标准异常

  - 需要记住一下几个常见的异常处理文件：

    - ```c++
      #include <exception>#include <stdexcept>#include <new>#include <type_info>
      ```



# 第六章 函数

## 6.1函数基础

- 函数定义
  - 包括返回类型、函数名字和0个或者多个形参组成的列表和函数体
- 调用运算符
  - 调用运算符的形式是一对圆括号 `()`，作用于一个表达式，该表达式是函数或者指向函数的指针
- 函数调用过程：
  - 首先是主调函数的执行被中断
  - 接着被调函数开始执行
- 形参和实参
  - 形参和实参的**个数**和**类型**必须匹配上
- 返回类型
  - `void`表示函数不返回任何值。函数的返回类型不能是数组类型或者函数类型，但也可以是指向数组或者函数的指针

- 生命周期
  - 对象的生命周期是程序执行过程中该对象存在的一段时间
- 局部变量
  - 形参和函数体内部定义的变量统称为局部变量。它对函数而言是局部的，对函数外部而言是隐藏的
- 自动对象
  - 只存在于块执行期间的对象。当块的执行结束后，它的值就变成未定义的了
- 局部静态对象
  -  `static`类型的局部变量，生命周期贯穿函数调用前后

- 函数声明
  - 函数的声明和定义唯一的区别是声明无需函数体，用一个分号替代。函数声明主要用于描述函数的接口，也称函数原型



## 6.2参数传递

- 形参初始化的机理和变量初始化一样。
- **引用传递**：又称传引用调用，指**形参是引用类型**，引用形参是它对应的实参的别名
- **值传递**：又称传值调用，指实参的值是通过**拷贝**传递给形参

- 传值参数
  - 当初始化一个非引用类型的变量时，初始值被拷贝给变量
  - 函数对形参做的所有操作都不会影响实参
  - **指针形参**：常用在C中，`C++`建议使用引用类型的形参代替指针

- 传引用参数
  - 通过使用引用形参，允许函数改变一个或多个实参的值
  - 引用形参直接关联到绑定的对象，而非对象的副本
  - 使用引用形参可以用于**返回额外的信息**
  - 经常用引用形参来避免不必要的复制
  - `void swap(int &v1, int &v2)`
  - 如果无需改变引用形参的值，最好将其声明为常量引用

- `const`形参和实参
  - 形参的顶层`const`被忽略。`void func(const int i);`调用时既可以传入`const int`也可以传入`int`
  - 我们可以使用非常量初始化一个底层`const`对象，但是反过来不行
  - 尽量使用常量引用

- 数组形参
  - 当我们为函数传递一个数组时，实际上传递的是指向数组首元素的指针
  - 要注意数组的实际长度，不能越界

- 可变形参
  - `initializer_list`提供的操作（`C++11`）：

| 操作                                 | 解释                                                         |
| ------------------------------------ | ------------------------------------------------------------ |
| `initializer_list<T> lst;`           | 默认初始化；`T`类型元素的空列表                              |
| `initializer_list<T> lst{a,b,c...};` | `lst`的元素数量和初始值一样多；`lst`的元素是对应初始值的副本；列表中的元素是`const`。 |
| `lst2(lst)`                          | 拷贝或赋值一个`initializer_list`对象不会拷贝列表中的元素；拷贝后，原始列表和副本共享元素。 |
| `lst2 = lst`                         | 同上                                                         |
| `lst.size()`                         | 列表中的元素数量                                             |
| `lst.begin()`                        | 返回指向`lst`中首元素的指针                                  |
| `lst.end()`                          | 返回指向`lst`中微元素下一位置的指针                          |

- `initializer_list`使用demo：

```
void err_msg(ErrCode e, initializer_list<string> il){
    cout << e.msg << endl;
    for (auto bed = il.begin(); beg != il.end(); ++ beg)
        cout << *beg << " ";
    cout << endl;
}

err_msg(ErrCode(0), {"functionX", "okay});
```

- 所有实参类型相同，可以使用 `initializer_list`的标准库类型。
- 实参类型不同，可以使用`可变参数模板`。
- 省略形参符： `...`，便于`C++`访问某些C代码，这些C代码使用了 `varargs`的C标准功能。



## 6.3返回类型和return语句

- 无返回值

没有返回值的 `return`语句只能用在返回类型是 `void`的函数中，返回 `void`的函数可以没有 `return`语句

- 有返回值

  - `return`语句的返回值的类型必须和函数的返回类型相同，或者能够**隐式地**转换成函数的返回类型

  - 值的返回：返回的值用于初始化调用点的一个**临时量**，该临时量就是函数调用的结果

  - 最好不要返回局部对象的引用或指针

    - ```c++
      const string &manip(){
          return "Hello World!";//错误，返回类型应该是const string，不能返回局部临时量
      }
      ```

  - 引用返回左值：函数的返回类型决定函数调用是否是左值。调用一个返回引用的函数得到左值；其他返回类型得到右值。

  - 返回数组指针

    - `Type (*function (parameter_list))[dimension]`

    - 使用类型别名： `typedef int arrT[10];` 或者 `using arrT = int[10;]`，然后 `arrT* func() {...}`

    - 使用 `decltype`： `decltype(odd) *arrPtr(int i) {...}`




## 6.4函数重载

- 含义：如果同一作用域内几个函数名字相同但形参列表不同，我们称之为重载函数
- `main`函数不能重载
- 重载和``const`形参:

  - 一个有顶层`const`的形参和没有它的函数无法区分。 `Record lookup(Phone* const)`和 `Record lookup(Phone*)`无法区分
- 相反，是否有某个底层`const`形参可以区分。 `Record lookup(Account*)`和 `Record lookup(const Account*)`可以区分
- **重载和作用域**：若在内层作用域中声明名字，它将隐藏外层作用域中声明的同名实体，在不同的作用域中无法重载函数名



## 6.5 特殊用途语言特性

- 默认实参
  - `string screen(sz ht = 24, sz wid = 80, char backgrnd = ' ');`
  - 一旦某个形参被赋予了默认值，那么它之后的形参都必须要有默认值

- 内联（inline）函数
  - 普通函数的缺点：调用函数比求解等价表达式要慢得多
  - `inline`函数可以避免函数调用的开销，可以让编译器在编译时**内联地展开**该函数
  - `inline`函数应该在头文件中定义

- constexpr函数
  - 指能用于常量表达式的函数。
  - `constexpr int new_sz() {return 42;}`
  - 函数的返回类型及所有形参类型都要是字面值类型。
  - `constexpr`函数应该在头文件中定义



## 6.6函数匹配

- 重载函数匹配的**三个步骤**：1.候选函数；2.可行函数；3.寻找最佳匹配。
- **候选函数**：选定本次调用对应的重载函数集，集合中的函数称为候选函数（candidate function）。
- **可行函数**：考察本次调用提供的实参，选出可以被这组实参调用的函数，新选出的函数称为可行函数（viable function）。
- **寻找最佳匹配**：基本思想：实参类型和形参类型越接近，它们匹配地越好。

## 6.7函数指针

- **函数指针**：是指向函数的指针。

- `bool (*pf)(const string &, const string &);` 注：两端的括号不可少。

- 函数指针形参

  ：

  - 形参中使用函数定义或者函数指针定义效果一样。
  - 使用类型别名或者`decltype`。

- **返回指向函数的指针**：1.类型别名；2.尾置返回类型。





```c++
#include <iostream>

using namespace std;

int test01(int a, int b){
    return a > b ? a : b;
}

int test02(int a, int b, int(*p)(int, int)){
    return p(a, b);
}

int main(){
    int (*p)(int, int);
    p = test01;

    cout << test02(10, 9, p);
}

#include <iostream>

using namespace std;

int func1(const int a);
int func1(int a);//这两个函数声明是一样的

int main(){

}
```





# 第七章

##### 7.1 定义抽象数据类型

- 类的基本思想是数据抽象和封装

- 数据抽象是一种依赖于接口和实现分离的编程技术

- 定义成员函数

- 引入this

  - 成员函数通过一个名为this的额外的隐式参数来访问调用它的那个对象

- 引入const成员函数

  - 紧跟在参数列表后面的const表示this是一个指向常量的指针，像这样使用const的成员函数被称为常量成员函数
  - 即不能修改该对象的属性

- 构造函数

  - 类通过一个或几个特殊的成员函数来控制其对象的初始化过程

  - 默认构造函数（无需任何实参）

    - 合成的默认构造函数

  - 构造函数不能被写为const

  - 只有当类没有声明任何构造函数时，编译器才会自动地生成默认构造函数

  - 如果需要编译器生成默认构造函数

    - ```c++
      Sales_data() = default;
      ```

  - 构造函数初始值列表

  - 在类的外部定义构造函数

  - 拷贝，赋值和析构函数

  - 



##### 7.2 访问控制与封装

- 访问说明符：public,private,protected
- class默认的访问权限是private，struct默认的访问权限是public
- 友元：类允许其他类或者函数访问它的非公有成员
  - 友元声明只能出现在类定义的内部



##### 7.3 类的其他特性

- 定义在类内的成员函数都是自动的inline

- 可变数据成员

  - 写了一个函数是const的常函数，但是有些数据是需要在这个函数里面改变的

  - 那就把这个数据设为可变数据

  - ```c++
    mutable int a;//mutable表示该数据是一个可变数据
    ```

- 类的成员函数

  - 如果提供了构造函数，那么编译器就不会提供默认的构造函数了

  - 如果需要编译器提供默认的构造函数，就要声明出来

  - ```c++
    Screen() = default;//告诉编译器为我们提供默认构造函数
    ```

- 定义一个类型成员

  - ```c++
    typedef std::string::size_type pos;//使用类型别名等价地声明一个类型名字
    using pps = std::string;//同理
    ```

  - 类定义的类型名字和其他成员一样存在访问权限的限制

- 返回*this的成员函数

  - 如果要链式编程的话，就必须以引用的形式返回对象
  - 将this对象作为左值返回

- 从const成员函数返回*this

  - 如果返回的是const Sales_data&的话，那么就不能够链式编程了，因为返回对象是const

- 基于const的重载

  - 可以用const来重载函数

- 类类型

  - 即使两个类的成员列表完全一致，它们也是不同的类型

- 类的声明

  - 也叫做前向声明
  - 在它声明之后定义之前是一个不完全类型

- 类之间的友元关系

  - 把一个类声明为自己的友元类

  - ```c++
    class Screen{
        
    };
    
    class Window_mgr{
        friend class Screen;
    }
    ```

  - 友元关系是不具备传递性的，每个类负责控制自己的友元类和友元函数

- 令成员函数作为友元

  - ```c++
    class Screen{
        friend void Window_mgr::clear(int);
    }
    ```

- 函数重载和友元

  - ```c++
    extern int& storeOn(string, int);
    extern double& storeOn(int);
    
    class Screen{
      friend int& storeOn()  
    }
    ```



##### 7.4 类的作用域

- 作用域和定义在类外部的成员

  - 函数成员可以声明在类内，定义在类外

  - ```c++
    void Window_mgr::clear(int i){
        
    }
    ```

- 名字查找：

  - 首先，在名字所在的块中寻找其声明语句，只考虑在名字的使用之前出现的声明
  - 如果没有找到，继续查找外层作用域
  - 如果最终没有找到匹配的声明，则程序报错

- 对于定义在类内部的函数

  - 首先，编译成员的声明
  - 知道类全部可见后才编译函数体

- 用于类成员声明的名字查找

- 类型名要特殊处理

  - 已经在类外定义了的类型名就不能在类内重新定义

- 成员定义中的普通块作用域的名字查找

  - 首先，在成员函数内查找该名字的声明，和前面一样，只有在函数使用之前出现的声明才被考虑
  - 如果在成员函数内没有找到，则在类内继续查找，这时类的所有成员都可以被考虑
  - 如果类内也没找到该名字的声明，在成员函数定义之前的作用域继续查找
  - 尽管类的成员被隐藏了，但我们仍可以通过加上类的名字或显著地使用this指针来强制访问类成员

- 类作用域之后，在外围的作用域中查找



##### 7.5 构造函数再探

- 构造函数初始化列表

  - 如果成员是const，引用，或者属于某种未提供默认构造函数的类类型，必须通过构造函数初始值列表为这些成员提供初始值
  - 即用列表初始化成员，可以显式地初始化引用和const成员

- 成员初始化的顺序

  - 事实上，在编译器内部，并不是说按照代码的顺序初始化 初始化列表的，所以要尽量避免使用某些成员初始化其他成员

- 默认实参和构造函数

  - 构造函数也是接受默认实参的
  - 如果一个构造函数为所有参数提供了默认实参，则它实际上也定义了默认构造函数

- 委托构造函数

  - 就是在构造函数写实参的地方，调用构造函数

- 默认构造函数的作用

  - 如果定义了其他构造函数，那么最好也提供一个默认构造函数
  - 即如果有 有参构造函数了，那么就不会提供默认构造函数了

- 使用默认构造函数

  - 如果想要定义一个使用默认构造函数进行初始化对象，正确的方法是去掉对象名之后的空括号对

- 隐式的类类型转换

  - 只允许一步类类型转换
  - 能够通过一个实参调用的构造函数定义了一条从构造函数的参数类型向类类型隐式转换的规则
  - 如果构造函数只接受一个实参，则它实际上定义了转换为此类类型的隐式转换机制，有时我们把这种函数称为转换构造函数

- 类类型转换不是总有效的

  - 有时候编译器的隐式转换会给代码意想不到的影响

- 抑制构造函数定义的隐式转换

  - 通过关键字explicit来组织系统不自觉的隐式转换
  - 关键字explicit只对一个实参的构造函数有效，需要多个实参的构造函数不能用于指向隐式转换

- explicit构造函数只能用于直接初始化

  - ```c++
    Sales_data item1(null_book);//正确，可以直接初始化Sales_data item2 = null_book;//错误，这里涉及隐式转换，nonono
    ```

- 为转换显式地使用构造函数

  - 可以用类型等对数据进行强制转换

    - ```c++
      Sales_data(null_book);static_cast<Sales_data>(cin);
      ```

- 标准库中含有显示构造函数的类

- 聚合类

  - 所有成员都是public

  - 没有任何的构造函数

  - 没有类内初始值

  - 没有基类，没有虚函数

  - 可以用花括号来初始化

  - ```c++
    struct Data{    int ival;    string a;}Data vall = {1, "Anna"};//初始化的顺序一定要和类内声明的顺序一样
    ```

- 字面值常量类

  - null
  - https://blog.csdn.net/mbl114/article/details/111602832



##### 7.6 类的静态成员

- 声明静态成员
  - 类的静态成员存在于任何对象之外，对象中不包含任何与静态数据成员有关的数据
  - 静态成员函数也不与任何对象绑定在一起，它们不包含this指针，不能声明为const
- 使用类的静态成员
  - ：：访问
  - 类对象访问
  - 成员函数可以直接使用静态成员
- 定义静态成员
  - 类外定义的时候，不能重复static关键字
  - 和类的所有成员一样，当我们指向类外部的静态成员时，必须指明成员所属的类名，static关键词只能出现在类内
- 静态成员能用于某些场景，而普通成员不能
  - 可以使用静态成员作为默认实参，非静态数据成员不能作为默认实参（其本身就是对象的一部分）
- 静态成员的类内初始化
  - null



# 第十三章

#### 13.1 拷贝、赋值与销毁

- 一个类通过定义五种特殊的成员函数来控制对象的拷贝、移动、赋值和销毁
  - 拷贝构造函数
  - 拷贝赋值运算符
  - 移动构造函数
  - 移动赋值运算符
  - 析构函数
- 拷贝构造函数
  - 如果一个构造函数的第一个参数时自身类型的引用，且任何额外参数都有默认值，则此构造函数为拷贝构造函数
    - 如果不是引用，是传值的话，那就会无限的循环调用自身
  - 拷贝构造函数是系统会自动提供
  - 合成拷贝构造函数
  - 拷贝初始化和直接初始化
    - 拷贝初始化调用的情况
      - 将一个对象作为实参传递给一个非引用类型的形参
      - 从一个返回类型为非引用类型的函数返回一个对象
      - 用花括号列表初始化一个数组中的元素或一个聚合类中的成员
  - 参数和返回值
  - 拷贝初始化的限制
    - 防止隐式调用拷贝构造函数explicit
  - 编辑器可以绕过拷贝构造函数
    - 编辑器的优化
- 拷贝赋值运算符
  - 如果类未定义自己的拷贝赋值运算符，编辑器会为它合成一个
  - 重载赋值运算符
    - 赋值运算符通常返回一个指向其左侧运算对象的引用
  - 合成拷贝赋值运算符
- 析构函数
  - 释放对象使用的资源，并销毁对象的非static数据成员
  - 是一个类的成员函数，名字由波浪号类名构成，没有返回值，也不接受参数
  - 析构函数完成什么工作
    - 成员销毁时发生什么完全依赖于成员的类型，销毁类类型的成员需要执行成员自己的析构函数
    - 隐式销毁一个内置指针类型的成员不会delete它所指向的对象
  - 什么时候会调用析构函数
    - 变量在离开其作用域时被销毁
    - 当一个对象被销毁时，其成员被销毁
    - 容器被销毁时，其元素被销毁
    - 对于动态分配的对象，当对指向它的指针应用delete运算符时被销毁
    - 对于临时对象，当创建它的完整表达式结束时被销毁
    - ps：当指向一个对象的引用或指针离开作用域时，析构函数不会执行
  - 合成析构函数
- 三/五法则
  - 需要析构函数的类也需要拷贝和赋值操作
    - 我的理解：你需要自己去析构对象，就表明编译器默认的析构你是用不了的，有些操作是要自己去释放的
    - 那也就代表着拷贝对象和赋值对象也是一样需要人工操作的
    - 可以参考：深拷贝和浅拷贝
    - 如果一个类需要自定义析构函数，几乎可以肯定它也需要自定义拷贝赋值运算符和拷贝构造函数
  - 需要拷贝操作的类也需要赋值操作，反之亦然
    - 我的理解：拷贝和赋值不可以认为几乎时一样的操作吗
- 使用=default
  - 可以通过将拷贝控制成员定义为=default来显式要求编辑器生成合成的版本
- 阻止拷贝
  - 定义删除的函数
    - 可以通过将拷贝构造函数和拷贝赋值运算符定义为删除的函数来组织拷贝
    - 删除的函数是这样一种函数，虽然声明了它们，但是不能以任何方式使用它们
    - 在函数的参数列表后面加上=delete来指出
  - 析构函数不能是删除的成员
    - 对于析构函数已删除的类型，不能定义该类型的变量或释放指向该类型动态分配对象的指针
  - 合成的拷贝控制成员可能是删除的
    - 如果一个类有数据成员是不能默认构造，拷贝，复制或销毁，则对应的成员函数将被定义为删除的
  - private拷贝控制
    - 其实，如果不想拷贝函数被调用，就可以把它设为私有的就行了



#### 13.2 拷贝控制和资源管理

- 行为像值的类
  - 简述：拷贝、析构、拷贝复制运算符的时候要注意深拷贝和浅拷贝
  - 类值拷贝赋值运算符
    - 组合了析构函数和构造函数的操作
    - 赋值运算符的几点：
      - 如果将一个对象赋予它自身，赋值运算符必须能正确工作
      - 大多数赋值运算符组合了析构函数和拷贝构造函数的工作
- 定义行为像指针的类
  - 注意：拷贝的应该是指针的指向
  - 引用计数



#### 13.3 交换操作

- 类里面的swap函数
- 编写我们自己的swap函数
  - 与拷贝控制成员不同，swap并不是必要的，但是，对于分配了资源的类，定义swap可能是一种很重要的优化手段
- swap函数应该调用swap，而不是std::swap
  - 这里涉及using的问题
- 在赋值运算符中使用swap



#### 13.4 拷贝控制示例



#### 13.5 动态内存管理类



#### 13.6 对象移动
