# Variadic templates V

- 代码五

  - ```cpp
    template<typename... Args>//重载操作符，如果是对tuple进行操作，就用这个
    ostream& operator<<(ostream& os, const tuple<Args...> &t){
        os << "[";
        PRINT_TUPLE<0, sizeof...(Args), Args...>::print(os, t);
        return os << "]"; 
    }
    
    template<int IDX, int MAX, typename... Args>//IDX表示当前输出到了第几个，MAX表示tuple的长度
    struct PRINT_TUPLE{
        static void print(ostream& os, const tuple<Args...> &t){
            os << get<IDX>(t) << (IDX + 1 == MAX ? "" : ",");//输出第几个字符，get应该是tuple的专用函数
            PRINT_TUPLE<IDX + 1, MAX, Args...>::print(os, t);
        }
    }
    
    template<int MAX, typename... Args>
    struct PRINT_TUPLE<MAX, MAX, Args...>{//如果当前操作的是最后一个，即全部都输出完了，就return
        static void print(ostream& os, const tuple<Args...> &t){
            return;
        }
    }
    
    //使用过程
    cout << make_tuple(7.5,546,64116,16,"lsdjkf") << endl;
    //结果是：[7.5,546,64116,16,lsdjkf]
    ```

