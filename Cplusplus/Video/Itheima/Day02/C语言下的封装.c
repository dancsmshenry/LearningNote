#include <stdio.h>
#include <string.h>

struct Person{
    char mName[1024];
    int mAge;
};

void PersonEat(struct Person *p){
    printf("Person->mName : %s\n", p->mName);
}

void test01(){
    struct Person p1;
    strcpy(p1.mName, "Tom");
    PersonEat(&p1);
}

struct Dog{
    char mName[1024];

    int mAge;
};

void DogEat(struct Dog* d){
    printf("Dog->mName : %s\n", d->mName);
}

void test02(){
    struct Dog d1;
    strcpy(d1.mName, "Jerry");
    DogEat(&d1);
}

void test03(){
    struct Person p2;
    strcpy(p2.mName, "laowang");
    DogEat(&p2);
}
//c语言中属性和行为被分开处理了，类型检测不够

int main(){
    // test01();

    // test02();

    test03();
}