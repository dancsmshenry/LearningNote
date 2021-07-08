#include <iostream>

using namespace std;

struct Person{
    int m_Age;
};

void allocatMemory(Person** p){
    //传进来的是一个引用，接收的时候作为一个指针

    //**p是具体的Person对象 *p是对象的指针 p是指针的指针
    *p = (Person *) malloc(sizeof(Person));

    (*p) -> m_Age = 100;
}

void test01(){
    Person *p = NULL;
    //而这里的p其实也是一个指针，指向空null
    allocatMemory(&p);
    cout << p->m_Age << endl;
}

//利用指针引用开辟空间
void allocatMemoryByRef(Person* &p){
    //传进来的是一个指针
    //接收的是指针的引用
    p = (Person *)malloc(sizeof(Person));
    p->m_Age = 1000;
    cout << p->m_Age << endl;
}

void test02(){
    Person *p = NULL;
    allocatMemoryByRef(p);
}

int main(){
    // test01();
    test02();
}
//即用一级指针的引用，可以代替二级指针