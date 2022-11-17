# Variadic templates VI

- 代码六（递归+继承）

  - ```cpp
    //递归的继承
    template<typename Head, typename... Tail>
    class tuple<Head, Tail...>:private tuple<Tail...>{
        typedef tuple<Tail...> inherited;
        protected:
        	Head m_head;
        public:
        	tuple(){}
        	tuple(Head v, Tail... vtail):m_head(v),inherited(vtail...){}
        //前缀是表示Head的类型是什么
        //意义是取出第一个元素
        	typename Head::type head(){return m_head;}//这里是无法编译过的，是求出Head类型的时候出现了问题，用auto可以解决
        	auto head() -> decltype(m_head){return m_head}
        	Head head() {return m_head;}
        //意义是取出除去第一个元素后的tuple，用到的一个技巧就是，this指针子类指针指向父类对象
        	inherited& tail(){return *this;}
    };
    
    template<typename... Values> class tuple;
    template<> class tuple<> {};
    ```
