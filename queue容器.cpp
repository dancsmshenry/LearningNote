#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

void test01(){
    queue<int> q;
    q.push(1);//���β���Ԫ��
    q.pop();//�Ӷ�ͷ�Ƴ���һ��Ԫ��
    int a1 = q.back();//�������һ��Ԫ�أ���β����
    int a2 = q.front();//���ص�һ��Ԫ��
    int a3 = q.size();//���ض��еĴ�С
    bool a4 = q.empty();//�ж϶����Ƿ�Ϊ��
}

void test02(){
    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
    
    while (!q.empty()){
        cout << "��ͷԪ��Ϊ��" << q.front() << endl;
        cout << "��βԪ��Ϊ��" << q.back() << endl;
        q.pop(); 
        cout << endl;
    }
}

int main(){
    test02();
}
/**
 * û�е�����
 * �Ƚ����
 * ��ͷ front ��β back
 * ��� push
 * ������ͷ pop
 * ��С size
 **/ 