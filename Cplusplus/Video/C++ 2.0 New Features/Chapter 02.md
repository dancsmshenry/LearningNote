# Variadic templates

variadic template（可变参数模板）

- 用于继承，递归等代码，感觉会使得代码变得难懂

- 样例

  - ```cpp
    #include <iostream>
    #include <bitset>
    
    using namespace std;
    
    void print(){//因为该函数类似一个递归函数，所以一定要写一个这个函数，因为print递归到最后args是没有东西的
    }
    
    template<typename T, typename... Types>//表示传进来的是一个T，再加上一个包（pack），即把后面的一连串变量变为一个pack，传入函数中
    void print(const T& firstArg, const Types&... args){
        cout << firstArg << endl;
        cout << "size:" << sizeof...(args) << endl;//用来求解args的个数（注意这种特殊的写法）
        print(args...);
    }
    
    int main(){
        print(7.5, "hello", bitset<16>(377), 42);
    }
    ```

- 也是分特化和泛化的，哪个更加符合就选哪个（埋坑）

  - ```cpp
    #include <iostream>
    #include <bitset>
    
    using namespace std;
    
    void print(){//因为该函数类似一个递归函数，所以一定要写一个这个函数，因为print递归到最后args是没有东西的
    }
    
    template<typename T, typename... Types>//表示传进来的是一个T，再加上一个包（pack），即把后面的一连串变量变为一个pack，传入函数中
    void print(const T& firstArg, const Types&... args){
        cout << firstArg << endl;
        cout << "size:" << sizeof...(args) << endl;//用来求解args的个数（注意这种特殊的写法）
        print(args...);
    }
    
    template<typename... Types>
    void print(const Types&... args){
        //这个和上面是可以共存的，分为特化和泛化，今后会继续讲的
        //传入相同的数据，好像还是调用上面那个函数
    }
    
    int main(){
        print(7.5, "hello", bitset<16>(377), 42);
    }
    ```

- 出现在不同的地方：

  - 用于template parameters，就是模板参数包
  - 用于function parameter types，就是函数参数类型包
  - 用于function parameters，就是函数参数包

- 用处：可以理解为一种关于函数参数的递归

  - ```cpp
    template<typename... Values> class tuple;
    template<> class tuple<> {};
    
    template<typename Head, typename... Tail>
    class tuple<Head, Tail...>:private tuple<Tail...>{
        typedef tuple<Tail...> inherited;
        public:
        	tuple(){}
        	tuple(Head v, Tail... vtail):m_head(v), inherited(vtail...){}
        typename Head::type head(){return m_head;}
        inherited& tail(){return *this;}
        protected:
        	Head m_head;
    };
    ```

  - 记录一下上面这种做法，可以认为是tuple一个接一个的继承（并且每个tuple都用一个m_head来存储最前面的一个数据，用inherited来存储上一级的tuple）

  - tips：如果出现这种用参数递归的情况，一定要准备一个空的类来最后继承，即终止点

  - tuple是一个可以放任意数量，类型的一个类型
