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
#include <algorithm>//�����㷨��ͷ�ļ�

using namespace std;

void PrintQueue(const deque<int> &d){
    //iterator��ͨ��������reverse_itertor�����������const_itertorֻ��������
    //��������const deque��������ĵ�������Ҫ��const_iterator
    for (deque<int>::const_iterator it = d.begin(); it != d.end(); ++it){
        cout << *it << ' ';
    }
}

void test01(){
    //deque�Ĺ���
    deque<int> deque_01;//Ĭ�Ϲ��췽ʽ
    deque<int> deque_02(10, 5);//10��5����deque��

    // for (int i = 0; i < deque_02.size(); ++i){
    //     cout << deque_02[i] << " ";
    // }

    deque_01.push_back(10);
    deque_01.push_back(20);
    deque_01.push_back(30);
    deque_01.push_back(40);

    // PrintQueue(deque_01);

    deque<int> deque_03(deque_01.begin(), deque_01.end());//��[begin,end)�����Ԫ�ؿ���������
    deque_03.push_back(50);
    //����
    deque_03.swap(deque_02);
    // PrintQueue(deque_02);

    int n = deque_03.size();//���ض��еĴ�С
    bool flag = deque_03.empty();//�ж϶����Ƿ�Ϊ��

    deque<int> deque_04(10, 5);
    deque_04.resize(11);//���¶��������ĳ��ȣ��������䳤������Ĭ��ֵ����µ�λ�ã������ɾ�������Ԫ��
    deque_04.resize(12, 100);//�������Ĳ�����ָ�������������µ�λ�ã��ٵĻ��Ͳ�����
    // PrintQueue(deque_04);

    if(deque_04.empty()){
        cout << "����Ϊ��" << endl;
    }else{
        cout << "���в�Ϊ��" << endl;
    }
}

void test02(){
    deque<int> deque_01;

    //������β������Ԫ��
    deque_01.push_back(1);

    //�������ײ�����Ԫ��
    deque_01.push_front(0);

    //ɾ�����������һ��Ԫ��
    deque_01.pop_back();

    //ɾ����������ǰ���һ��Ԫ��
    deque_01.pop_front();

    //���ص�һ������
    int a1 = deque_01.front();

    //�������һ������
    int a2 = deque_01.back();

    //�������������ݣ����Խ���˾��׳��쳣
    int a3 = deque_01.at(0);

    //�������������ݣ�Խ���˾ͱ���
    int a4 = deque_01[0];

    //ɾ�����������е�����
    deque_01.clear();
}

void test03(){
    deque<int> d(10, 10);
    //ɾ����ǰλ�õ�����
    //d.erase(d.begin());
    
    //ɾ��d.begin(), d.begin() + 2֮�������
    d.erase(d.begin(), d.begin() + 2);

    for (int i = 0; i < d.size(); ++ i){
        cout << d[i] << " ";
    }
}

void test04(){
    deque<int> d1(10, 2);
    //��pos��d1.begin()��λ���������3
    d1.insert(d1.begin(), 3);

    deque<int> d2(10, 2);
    //��pos��d1.begin()��λ�����2������3
    d2.insert(d2.begin(), 2, 3);

    deque<int> d3(1, 10);
    //��pos��d3.begin()��ʼ�Ѷ���d2��ȫ������ӽ���
    d3.insert(d3.begin(),d2.begin(),d2.end());

    for (int i = 0; i < d2.size(); ++ i){
        cout << d2[i] << " ";
    }
}

bool compare(int t1, int t2) {
    return t1 > t2;
}

//����
void test05(){
    deque<int> d1;
    
    d1.push_back(50);
    d1.push_back(40);
    d1.push_back(24150);
    d1.push_back(110);
    d1.push_back(10);

    //����,Ĭ���Ǵ�С�����
    sort(d1.begin(), d1.end());

    //���򣬴Ӵ�С
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
 * ˫������ û����������̬�����ڴ棬�ֶ������ռ���ɣ�
 * �����ó������ʱ���ͷ��Ԫ�ؽ��в����ɾ��
 * ��Ϊdeque��itertor��vector����һ�������ģ����������vector
 **/ 