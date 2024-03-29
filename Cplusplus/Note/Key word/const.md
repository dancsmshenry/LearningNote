# const

- 表示变量是不能改变
- 常量必须要初始化的
- 对于const常量，编译器将在编译过程中把用到该变量的地方都替换成对应的值
  - 可以类比define，不过define是在预编译的时候换的，而这是在编译的时候换的
- 默认情况下，const对象被设定为仅在文件内有效，当多个文件中出现了同名的const变量时，其实等同于在不同文件中分别定义了独立的变量
- 阻止一个变量被改变，可以使用const关键字
- 在定义该const变量时，必须初始化，因此也导致如果类的成员变量有const类型的变量，那么该变量必须在类的初始化列表中进行初始化
- const类型变量可以通过类型转换符const_cast将const类型转换为非const类型
- 对于参数的传递，只有引用传递和指针传递可以用是否加const来重载（因为值传递都是一个临时变量传入，加不加const都不影响）
- 一个拥有顶层const的形参无法和另一个没有顶层const的形参区分开来





# 在C里面



## const全局变量

- 是放在常量区（只读数据段）的，因此是不可以使用指针修改的

- C语言中const全局变量默认是外部链接的，即可以跨文件使用，在一个文件里`const int a = 10`，在另一个文件中可以直接`extern const int a`声明一下即可使用



## const局部变量

- const局部变量是可以通过指针改变的，本质上还是一个变量，只是不可以做为左值存在，也就是无法直接对变量修改

- 局部的const变量是放在栈区里面的

- ```cpp
  #include <stdio.h>
  
  int main() {
      const int i = 1;
      int *p = &i;
      *p = 1022;
      printf("%d\n",i); // 1022
  }
  ```

- 无论全局还是局部变量的const，都是可以用来当作常量初始化数组的

- ```cpp
  #include <stdio.h>
  
  int main() {
      const int i1 = 11;
      int m[i1];
  }
  ```



## 顶层const

- 表示指针本身就是一个常量
  - 是指不能修改指针指的方向
  - 并不意味着不能通过指针修改其所指对象的值，能否这样做完全依赖于所指对象的类型，因为指针可能指向变量，也可能指向常量（再加上一层底层const即可）
- `int *const pr = &p;`
  - **从右往左读**，发现是一个const对象，紧接着发现是一个int *指针，就明白是一个常量指针
- 在c里面，常量指针不一定要初始化



## 底层const


- 表示指针所指的对象是一个常量

  - 是指不能通过指针修改对象的值
  - 所以该类型的指针既可以指向变量，也可以指向常量
- `const int* p2 = &ci;`

  - **从右往左读**，发现是一个指针，紧接着发现const，就明白是一个指针指向了一个常量
- 在c里面，const修饰的变量可以不用底层const指针修饰
- 在c里面，不一定要初始化

- 当执行对象的拷贝操作时，拷入和拷出的对象必须具有相同的底层的const资格
  - 比如说一个int*的，不能指向一个const类型的对象
- 用于声明引用的const都是底层const





# 在C++里面



## 成员函数

- 在一个函数声明中，const可以修饰形参，表明它是一个不能被修改的输入参数

- 对于类的成员函数，若指定其为const类型，则表明其是一个常函数，不能修改类的成员变量，**const对象只能访问类的const成员函数**

  - 因此在成员函数后面可以按是否加上const来判断重载
  - 这里的const本质上修饰的是this指针

- const成员函数可以访问非const对象的非const数据成员、const数据成员，也可以访问const对象内的所有数据成员

- 非const成员函数可以访问非const对象的非const数据成员、const数据成员，但不可以访问const对象的任意数据成员

- |                 | const对象 | 非const对象 |
  | --------------- | --------- | ----------- |
  | const成员函数   | ok        | no          |
  | 非const成员函数 | no        | ok          |



## 指针和引用

- 可以把引用绑定到const对象上，就像绑定到其他对象上，即对常量的引用
- 对常量的引用不能被用作修改它绑定的对象
  - 实现原理：const的引用的本质其实是把给到的值生成一个const的临时变量，然后把引用 引用到这个临时变量
  - 这就是为什么不能通过const引用来改变被引用对象


初始化和对const的引用

- 引用的类型必须与其所引用对象的类型一致，但有两个例外：
  - 第一种，初始化常量引用时允许用任意表达式作为初始值，只要该表达式的结果能转换成引用的类型即可
- 常量引用能够使用任意表达式作为初始值，是因为编译器先复制一个相同的初始值（临时值， 是常量），接着让常量引用绑定该常量
- 所以，是不能用常量引用来修改被指向的值的

对const的引用可能引用一个并非const的对象

- 常量引用仅对引用可参与的操作做出了限定，对于引用的对象本身是不是常量未作限定
- 所以，常量引用既可以绑定常量，也可以绑定非常量，但共同点就是不能通过这个引用修改被引用的对象

**在cpp中，编译器先复制一个相同的初始值（临时值， 是常量），接着让常量引用绑定该常量**

- const引用可以引用非const和const的对象
- 不能通过const引用来修改被引用的对象
- 常量引用可以使用任何表达式作为初值
- PS：引用的底层是指针，所以指针也是这个道理



## const全局变量

- 是放在常量区的，因此是不可以使用指针修改的
- CPP则默认是内部链接，即作用域限定在本文件内，如果非要跨文件使用则在定义的时候就要用`extern`声明一下来提升作用域。即定义的时候就要加上`extern const int a = 10`，使用的时候还要声明`extern const int a`
- 如果需要extern的话，就要分配内存



## const局部变量

- cpp为了兼容c语言，所以给了const变量提供地址，而c语言本身提供的const还是可以被修改，而c++为了严谨就不能修改

- 当碰到用const修饰的变量时，cpp是直接将变量的值和变量的符号对应起来一起存到符号表，所以编译器不会为其分配内存空间

- 每次使用的时候都要去符号表里面去查找

- 但如果遇到要求const变量的地址的时候，这时候才会为其分配地址（所以如果要操控指针去修改const的变量，其实会复制一个单独的变量出来）

- ```cpp
  void test(){
        const int m_B = 20;
        int *p = (int *) &m_B;
        //int tmp = m_B; int *p = (int *)&tmp;//	相当于这样
        *p = 100;
  }
  ```

- ```cpp
  int main()
  {
      const int i = 0;
      int *j = (int *)&i;
      *j = 1;
      printf("%d,%d", i, *j);
  }
  //	如果是cpp的话，输出的是0,1
  //	如果是c的话，输出得是1,1
  ```

- 总结：在编译的时候如果前面有extern和取地址符&时，才会为const变量分配存储空间

- 看到的一种理解

  - 一般的const局部变量（直接用常量初始化的）是不分配内存的，即直接放到符号表中，因此是没办法修改的

  - 但是如果用变量初始化const局部变量的话，即`const int a = b`，这时候不管b是基本数据类型还是自定义数据类型，都会分配内存，即可以通过指针间接修改（cpp的const变量，如果要用指针修改的话，那么就必须要用指针强转，而由此，实际上得到的是一个从符号表复制的来的数据）



## 顶层const

- 表示指针本身就是一个常量
  - 是指不能修改指针指的方向
  - 并不意味着不能通过指针修改其所指对象的值，能否这样做完全依赖于所指对象的类型，因为指针可能指向变量，也可能指向常量（再加上一层底层const即可）
- `int *const pr = &p;`
  - **从右往左读**，发现是一个const对象，紧接着发现是一个int指针，所以是一个常量指针
- 在cpp中的常量指针必须初始化



## 底层const


- 表示指针所指的对象是一个常量

  - 是指不能通过指针修改对象的值
  - 所以该类型的指针既可以指向变量，也可以指向常量
- `const int* p2 = &ci;`

  - **从右往左读**，发现是一个指针，紧接着发现const，所以是一个指针指向了一个常量
- 在cpp里面，常量对象的地址必须使用指向常量的指针
- 在cpp中不必初始化

- 当执行对象的拷贝操作时，拷入和拷出的对象必须具有相同的底层的const资格
  - 比如说一个int*的，不能指向一个const类型的对象
- 用于声明引用的const都是底层const（比如说const vector<int>&，就是表示vector<int>是一个常量）
