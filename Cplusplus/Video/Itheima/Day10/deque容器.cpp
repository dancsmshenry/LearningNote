/*
 * @Author: dancsmshenry
 * @Email: 1175152442@qq.com
 * @Date: 2021-05-30 14:14:45
 * @Last Modified by:   dancsmshenry
 * @Last Modified time: 2021-05-30 14:14:45
 * @Description: Description
 */


#include <iostream>
#include <deque>
#include <algorithm>//排序算法的头文件

using namespace std;

void PrintQueue(const deque<int> &d){
    //iterator普通迭代器，reverse_itertor逆序迭代器，const_itertor只读迭代器
    //这里用了const deque所以下面的迭代器就要用const_iterator
    for (deque<int>::const_iterator it = d.begin(); it != d.end(); ++it){
        cout << *it << ' ';
    }
}

void test01(){
    //deque的构造
    deque<int> deque_01;//默认构造方式
    deque<int> deque_02(10, 5);//10个5抛入deque中

    // for (int i = 0; i < deque_02.size(); ++i){
    //     cout << deque_02[i] << " ";
    // }

    deque_01.push_back(10);
    deque_01.push_back(20);
    deque_01.push_back(30);
    deque_01.push_back(40);

    // PrintQueue(deque_01);

    deque<int> deque_03(deque_01.begin(), deque_01.end());//将[begin,end)区间的元素拷贝给本身
    deque_03.push_back(50);
    //交换
    deque_03.swap(deque_02);
    // PrintQueue(deque_02);

    int n = deque_03.size();//返回队列的大小
    bool flag = deque_03.empty();//判断队列是否为空

    deque<int> deque_04(10, 5);
    deque_04.resize(11);//重新定义容器的长度，若容器变长，则以默认值填充新的位置，否则就删除多余的元素
    deque_04.resize(12, 100);//这里后面的参数是指用这个数来填充新的位置，少的话就不管了
    // PrintQueue(deque_04);

    if(deque_04.empty()){
        cout << "队列为空" << endl;
    }else{
        cout << "队列不为空" << endl;
    }
}

void test02(){
    deque<int> deque_01;

    //在容器尾部插入元素
    deque_01.push_back(1);

    //在容器首部插入元素
    deque_01.push_front(0);

    //删除容器的最后一个元素
    deque_01.pop_back();

    //删除容器的最前面的一个元素
    deque_01.pop_front();

    //返回第一个数据
    int a1 = deque_01.front();

    //返回最后一个数据
    int a2 = deque_01.back();

    //返回索引的数据，如果越界了就抛出异常
    int a3 = deque_01.at(0);

    //返回索引的数据，越界了就报错
    int a4 = deque_01[0];

    //删除队列中所有的数据
    deque_01.clear();
}

void test03(){
    deque<int> d(10, 10);
    //删除当前位置的数据
    //d.erase(d.begin());
    
    //删除d.begin(), d.begin() + 2之间的数据
    d.erase(d.begin(), d.begin() + 2);

    for (int i = 0; i < d.size(); ++ i){
        cout << d[i] << " ";
    }
}

void test04(){
    deque<int> d1(10, 2);
    //在pos即d1.begin()的位置添加数字3
    d1.insert(d1.begin(), 3);

    deque<int> d2(10, 2);
    //在pos即d1.begin()的位置添加2个数字3
    d2.insert(d2.begin(), 2, 3);

    deque<int> d3(1, 10);
    //从pos即d3.begin()开始把队列d2的全部都添加进来
    d3.insert(d3.begin(),d2.begin(),d2.end());

    for (int i = 0; i < d2.size(); ++ i){
        cout << d2[i] << " ";
    }
}

bool compare(int t1, int t2) {
    return t1 > t2;
}

//排序
void test05(){
    deque<int> d1;
    
    d1.push_back(50);
    d1.push_back(40);
    d1.push_back(24150);
    d1.push_back(110);
    d1.push_back(10);

    //排序,默认是从小到大的
    sort(d1.begin(), d1.end());

    //排序，从大到小
    sort(d1.begin(), d1.end(), compare);
    PrintQueue(d1);
}

int main(){
    // test01();
    // test02();
    // test03();
    // test04();
    test05();
}
/**
 * 双端数组 没有容量（动态分配内存，分段连续空间组成）
 * 允许用常数项的时间对头部元素进行插入和删除
 * 因为deque的itertor和vector不是一个量级的，所以最好用vector
 **/ 