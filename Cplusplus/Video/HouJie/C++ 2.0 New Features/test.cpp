#include <iostream>
#include <bitset>

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

int main(){
    // cout << __cplusplus << endl;

    // print(7.5, "hello", bitset<16>(377), 42);

    // prin({1,2,3,4,5,6,7,1});

    cout << min(10, 11, 12 );
}