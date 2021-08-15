#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/**
 * 动态增加大小：
 * 不是在原来的空间之后续接新空间（因为无法保障原空间之后尚有可配置的空间）
 * 而是一块更大的内存空间，然后将原数据拷贝到新空间，并释放原空间
 * 因此，对vector的任何操作，一旦引起了空间的重新配置，指向原来vector空间的迭代器就都失效了
 **/ 

void test01(){
    vector<int> v;

    for (int i = 0; i < 11; i ++ ){
        v.push_back(i);
        cout << v.capacity() << " ";//返回vector的容量
    }
}

int main(){
    test01();
}