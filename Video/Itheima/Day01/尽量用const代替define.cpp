#include <iostream>

using namespace std;

int main(){
    
}

/**
 * 因为define所指定的内容会在预处理阶段，即被编译之前给替换为所要指向的内容
 * 如果define所定义的是在一个我不知道的头文件当中，出现错误的时候难以察觉
 * 
 * const与define的区别：
 * const有类型，可以进行编译器类型安全检查
 * #define没有类型，不可进行类型检查
 * 
 * const有作用域
 * 而#define不重视作用域，默认定义处到文件结尾，如果定义在指定作用域下，那么就不能用#define
 * 可以用#undef 变量 来卸载宏变量
 **/ 