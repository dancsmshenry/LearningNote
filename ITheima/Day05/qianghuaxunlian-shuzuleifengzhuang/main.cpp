#include <iostream>
#include "MyArray.h"

void test01(){
    //堆区创建数组
    MyArray *array = new MyArray(30);

    MyArray *array1(array);//这里是浅拷贝，不是深拷贝？？为什么这里没有析构它啊？
    //还有注意这里的array其实是一个指针，而传进来的要是一个实体
    //这是什么语法啊？？我只重写了拷贝构造，但是没重写指针的拷贝构造啊？

//    delete array;

    //尾插法测试
    for (int i = 0; i < 10; i ++ ){
        array1->push_Back(i);
    }

    //获取数据测试
    for (int i = 0; i < 10; i ++ ){
        cout << array1->getData(i) << " ";
    }
    cout << endl;

    array1->setData(0, 100);
    cout << array1->getData(0) << endl;

    delete array;

//    delete array1;//这里还是要手动释放的，因为拷贝构造出来的数组还是new出来的，是在堆上的
}

void test02(){
//    MyArray s1(1000);
//    MyArray s2(s1);
    MyArray *a1 = new MyArray(30);
//    MyArray a2(*a1);//这样是符合逻辑的，因为a1是一个指针，而*a1是一个对象，这很符合逻辑

//    MyArray *a3(a1);//但是这样为什么有可以呢

    //https://blog.csdn.net/qq_21148843/article/details/79794695


//    delete a1;
}

int main() {
//    std::cout << "Hello, World!" << std::endl;
//    test01();

    test02();
    return 0;
}