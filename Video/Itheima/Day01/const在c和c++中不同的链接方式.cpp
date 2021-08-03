#include <iostream>

using namespace std;

int main(){
    /**
     * const在c语言中是外部链接的
     * 例子：
     * 在同一个项目的文件夹中，一个文件写的是const int a = 10;
     * 另一个文件写：
     * extern const int a;
     * printf("%d", a);
     * 代码是可以运行的，输出的是10
     * 
     * 但是const在c++中是内部链接的
     * 同样的代码在c++中是会报错的
     * 
     * 原因是：const在c语言中，const的作用域是整个项目（可以这么理解吧），const是外部链接的
     * 但是在c++中不是，其作用域是在当前的文件中的，const是内部链接的
     **/ 
}