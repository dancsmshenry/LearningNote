#include <iostream>
#include "Person.hpp"

//类模板的分文件编写问题以及解决
using namespace std;

//建议 模板不要做分文件编写，写到一个类中即可，类内进行声明和实现，最后把后缀名改为.hpp即可

int main() {
    Person<string, int> p("zhubajie", 10);
    p.showPerson();

//    std::cout << "Hello, World!" << std::endl;
    return 0;
}