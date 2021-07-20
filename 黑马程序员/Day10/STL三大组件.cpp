#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

/** 
 * stl standard template library
 * 容器（container），算法（algorithm），迭代器（iterator）
 * 容器和算法之间通过迭代器进行无缝连接
 * 
 * stl六大组件：
 * 容器（顾名思义，是用来存放数据的），算法（容器的方法接口），
 * 迭代器（扮演了容器与算法之间的胶合剂，相当于指针），
 * 仿函数（行为类似函数，是重载了（）运算符），
 * 适配器（配接器，一种用来修饰容器或者仿函数或迭代器接口的东西），
 * 空间配置器（负责空间的配置与管理）
 * 
 * 各个之间的关系：
 * 容器通过空间配置器取得数据存储空间，算法通过迭代器存储容器中的内容，仿函数可以
 * 协助算法完成不同的策略的变化，适配器可以修饰仿函数
 * 
 * 优点：
 * 高可重用性，高性能，高移植性，跨平台
 * 
 * 容器：
 * 序列式容器：强调值的排序，如vector，deque，list
 * 关联式容器：非线性的树结构，更准确的说是二叉树结构
 * 一个显著的特点就是：在值中选择一个值作为关键字key，这个关键字对值起到索引的作用，方便查找
 * set/multiset，map/multimap容器
 * 
 * 算法：
 * 质变算法：指运算过程中更改区间内的元素的内容，如：拷贝，替换，删除等
 * 非质变算法：不会改变元素的内容，如：查找，记数，遍历。找极值
 * 
 * 迭代器：
 * 可以近似的看为是一种指针一样的东西
 **/ 

//迭代器 遍历功能 用指针理解
//普通指针也算是一种迭代器
void test01(){
    int array[5] = {1, 3, 5, 7, 9};

    int *p = array;//指针指向数组的首地址，&array[0]

    for (int i = 0; i < 5; i ++ ){
        // cout << array[i] << " ";
        cout << *(p ++ ) << " ";
    }
}

void MyPrint(int v){
    cout << v << " ";
}

void test02(){
    //声明容器

    vector<int> v;//声明一个vector容器，这个容器存放int类型的数据，对象的名称为v

    //向容器中加入数据
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    //第一种遍历方式
    //利用迭代器遍历容器中的数据
    vector<int>::iterator itbegin = v.begin();//itbegin指向的是v容器中的起始位置

    vector<int>::iterator itend = v.end();//itend指向的是v容器中的最后一个位置的下一个地址

    while (itbegin != itend){
        cout << *itbegin << " ";
        itbegin ++ ;
    }
    cout << endl;

    //第二种遍历方式
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;

    //第三种遍历方式
    //需要使用头文件algotithm
    for_each(v.begin(), v.end(), MyPrint);
}

//操作自定义数据类型
class Person{
    public:
        Person(string name, int age){
            this->m_Name = name;
            this->m_Age = age;
        }

        string m_Name;
        int m_Age;
};

void test03(){
    vector<Person> v;
    Person p1("datouerzi", 10);
    Person p2("xiaotoubaba", 32);
    Person p3("gebiwangshushu", 30);
    Person p4("weiqunmama", 28);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    //遍历数组vector
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it ++ ){
        cout << "姓名：" << it->m_Name << " " << "年龄：" << it->m_Age << endl; 
    }
}

//存放自定义数据类型的指针
void test04(){
    vector<Person *> v; 
    Person p1("datouerzi", 10);
    Person p2("xiaotoubaba", 32);
    Person p3("gebiwangshushu", 30);
    Person p4("weiqunmama", 28);
    v.push_back(&p1);   
    v.push_back(&p2);
    v.push_back(&p3);
    v.push_back(&p4);

    //遍历数组vector
    for (vector<Person *>::iterator it = v.begin(); it != v.end(); it ++ ){
        cout << "姓名：" << (*it)->m_Name << " " << "年龄：" << (*it)->m_Age << endl; 
    }
}

//容器嵌容器
void test05(){
    
}

int main(){
    // test01();

    // test02();

    // test03();

    test04();
}