# 第5章 语句

## 5.1 简单语句

空语句：只有一个分号

```c++
;
```

复合语句块：用花括号 `{}`包裹起来的语句和声明的序列。一个块就是一个作用域

```c++
while (val <= 10){
    sum += val;
    ++ val;
}
```

空块

```c++
while (cin >> s && s!= sought){}
```

注意：不一定所有的语句都会以分号结尾

```c++
for (int i = 0; i < 100; ++ i) {
    i1 = i * i, i2 = i * i * i;
}
```

<br/>

<br/>

## 5.2 语句作用域

<br/>

<br/>

## 5.3 条件语句

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

<br/>

<br/>

## 5.4 迭代语句

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

<br/>

<br/>

## 5.5 跳转语句

break语句
- 终止离它最近的while、do while、for或者switch语句，并从这些语句之后的第一条语句执行

continue语句

- 终止最近的循环中的当前迭代并立即开始下一次迭代

goto语句（）本不用这个语句

- 程序的可读性会被降低（从上往下读，然后还有时不时往回看），同时用不好会使程序逻辑混乱

<br/>

<br/>

## 5.6 TRY语句块和异常处理

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

  - ```cpp
    #include <exception>
    #include <stdexcept>
    #include <new>
    #include <type_info>
    ```
