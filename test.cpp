#include <iostream>
#include <deque>
#include <list>
#include <vector>

using namespace std;

template<typename T,
         template <typename U> class Container
         >
class XCls{
public:
	Container<T> c;
};

template<typename T>
using Lst = list<T, allocator<T>>;

void print(){}

template <typename T,typename... Types>
void print(const T& firstArg, const Types&... args){
    cout << firstArg << endl;
    print(args...);
}

int main()
{
    print("546", 454, 8564);
}