#include <iostream>
#include <vector>
#include <string>
#include <algorithm>//使用系统算法的头文件

using namespace std;

void MyPrint(int v){//这好像也有顺序，即必须在执行这个函数之前就已经声明定义了这个函数
    cout << v << endl;
}

//迭代器，遍历功能，用指针理解
//普通指针也算一种迭代器
void test01(){
    int array[5] = {0,1,2,3,4};

    int *p = array;//指针指向数组首地址 &array[0]

    for (int i = 0; i < 5; ++i){
        //cout << array[i] << endl;
        cout << *(p + i) << endl;
    }
}

//vector
void test02(){
    //声明一个vector容器，这个容器存放int类型数据，对象名称v
    vector<int> v;

    //向容器中加入数据
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    //遍历容器中的数据，利用迭代器
    vector<int>::iterator itBegin = v.begin();//itBegin指向的是v容器中的初始位置

    vector<int>::iterator itEnd = v.end();//itEnd指向v容器中最后一个位置的下一个地址

    while (itBegin != itEnd){
        cout << *itBegin << endl;
        itBegin ++ ;
    }//感觉迭代器可以理解为指针？？

    //第二种遍历方式
    // for (int i = 0; i < 10; i ++ )
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++ it){
        cout << *it << endl;
    }

    //第三种遍历方式，利用算法
    for_each(v.begin(), v.end(), MyPrint);
}

class Person{
    public:
        Person(int age, string name){
            this->m_Age = age;
            this->m_Name = name;
        };

        int m_Age;
        string m_Name;
};

void test03(){
    vector<Person> v;

    v.push_back(Person(10, "大头儿子"));
    v.push_back(Person(20, "小头爸爸"));
    v.push_back(Person(30, "隔壁王叔叔"));

    //遍历
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it ++){
        cout << "姓名是：" << (*it).m_Name << "，年龄是：" << it->m_Age << endl;
        //可以用->来访问，也可以用.来访问
    }
    
}

//存放自定义数据类型的指针
void test04(){
    vector<Person*> v;//这里存放的是指针了，所以下面就要更改一下

    Person p1(10, "大头儿子");
    Person p2(20, "小头爸爸");
    Person p3(30, "隔壁王叔叔");

    v.push_back(&p1);//教训，不能再这里创建临时对象555
    v.push_back(&p2);
    v.push_back(&p3);

    //遍历
    for (vector<Person*>::iterator it = v.begin(); it != v.end(); it ++){
        cout << "姓名是：" << (*it)->m_Name << "，年龄是：" << (*it)->m_Age << endl;
        //可以用->来访问，也可以用.来访问
    }
    
}

//容器嵌套容器
void test05(){
    vector<vector<int>> v;

    vector<int> v1;
    vector<int> v2;
    vector<int> v3;

    for (int i = 0; i < 5; i++){
        v1.push_back(i);
        v2.push_back(i + 10);
        v3.push_back(i + 100);
    }
    //将小容器放入大容器中
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);

    for (vector<vector<int>>::iterator it = v.begin(); it != v.end(); it ++){
        for (vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2 ++ ){
            cout << *it2 << " ";
        }
        cout << endl;
    }
}

int main(){
    // test01();
    // test02();
    // test03();
    // test04();
    test05();
}
/**
 * 容器 vector
 * 算法 for_each（遍历每个元素） 头文件 algorithm
 * 迭代器iterator 每个容器都有自己专属的迭代器
 * v.begin()（指向头部元素的地址）,v.end()（指向最后一个元素的后一个位置）
 **/ 