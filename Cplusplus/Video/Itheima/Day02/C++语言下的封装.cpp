#include <iostream>
#include <string.h>

using namespace std;

struct Person{
    char mName[1024];
    int mAge;

    void PersonEat(){
        cout << "Person->mName : "<< mName;
    }
};

//cpp中的封装 严格类型转换检测 让属性和行为绑定在一起
/**
 * 属性和行为作为一个整体来表示生活中的事物
 * 控制权限 public private protect
 **/ 
void test01(){
    struct Person p1;
    strcpy(p1.mName, "Tom");
    p1.PersonEat();
}

struct Dog{
    char mName[1024];
    int mAge;

    void PersonEat(){
        cout << "Dog->mName : "<< mName;
    }
};

void test02(){
    struct Dog d1;
    strcpy(d1.mName, "Jerry");
    d1.PersonEat();
}

void test03(){
    struct Person p2;
    strcpy(p2.mName, "laowang");
}

//struct 和 class是一个意思，唯一不同的是默认权限，struct是public，class是private
class Animal{
    void eat(){

    }

    public:
        int mHeight;

    protected:
        int mWeight;
};

void test04(){
    Animal a1;
    
    //这里是私有权限，即私有成员，在类内可以被访问，类外部就不可以被访问
    // a1.eat();

    //这里是公有权限
    cout << a1.mHeight << endl;
    
    //这里是保护权限，类内部可以访问，当前类的子类也可以访问，类外部就不可以访问
    // cout << a1.mWeight << endl;
}

int main(){
    // test01();

    // test02();

    test03();
}