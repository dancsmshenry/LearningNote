# 三个主题

- variadic templates（since cpp11）

  - 数量不定的模板参数

  - ```cpp
    void print(){}
    
    template <typename T,typename... Types>
    void print(const T& firstArg, const Types&... args){
        cout << firstArg << endl;
        print(args...);
    }
    /**
    可以理解上述的函数时递归调用的，即每次都取出前面一个数进行输出，把后面的数继续递归会这个函数操作
    不过注意，args总会出现空的时候，这样就不会调用到这个模板函数，所以为了防止bug，就再写一个空的函数返回即可
    **/
    
    cout << sizeof(args) << endl;//查询args有多少个
    ```

- auto(since cpp11)

  - ```cpp
    list<string> c;
    list<string>::iterator ite;
    ite = find(c.begin(), c.end(), target);
    
    //现在可以写为
    list<string> c1;
    auto ite = find(c.begin(), c.end(), target);//自动推导类型，用于一些类型非常难写或难找的类型的一种便捷式的写法
    //同时，auto必须要有具体的值，通过值才能推导出具体的对象
    ```

- ranged-base for(since cpp11)

  - ```cpp
    for(decl:coll){
        statement;
    }
    /**
    左边是一个变量，右边是一个容器，遍历一遍容器，把容器里的元素逐个放到这个变量当中
    **/
    
    for (auto elem:vec){
        cout << elem << endl;
    }//这个返回的是值，即类似值传递，不能修改到它本身（pass by value）
    
    for (auto& elem:vec){
        elem *= 3;
    }//这个返回的是值的引用，修改它就是修改本身（pass by reference）
    ```
