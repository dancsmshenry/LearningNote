#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

void print(){//如果是递归的话，最后一定要写一个这个函数，因为print递归到最后args是没有东西的

}

template<typename T, typename... Types>
void print(const T& firstArg, const Types&... args){
    cout << firstArg << endl;
    cout << "size:" << sizeof...(args) << endl;//用来求解args的个数
    print(args...);
}

void prin(initializer_list<int> vals){
    for (auto p = vals.begin(); p != vals.end(); p ++ ){
        cout << *p << endl;
    }
}

class Foo{
    public:
        Foo(int i):_i(i){}
        Foo() = default;
        void func2() = delete;
    
    private:
        int _i;
};

template<typename T>
using vec = vector<T, allocator<T>>;

template<typename T, template<class> class Container>
class X{
    private:
        Container<T> c;
};

int main(){
    // cout << __cplusplus << endl;

    // print(7.5, "hello", bitset<16>(377), 42);

    // prin({1,2,3,4,5,6,7,1});

    // cout << min(10, 11, 12 );

    X<int, vec> c1;//因为vector是有两个参数的（_tp,_ALLOC）,如果是以模板传入的话，模板是无法自动推导后面的参数的

    Foo f;
}