#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

void test01(){
    stack<int> s;
    //����Ԫ��
    s.push(10);
    s.push(20);
    s.push(30);

    while (s.size() != 0){
        cout << "ջ��Ϊ��" << s.top() << endl;//����ջ��Ԫ��
        s.pop();//�߳�ջ��Ԫ��
    }

    cout << s.size() << endl;
}

int main(){
    test01();
}
/**
 * �Ƚ����
 * ջ��top
 * ѹջpush
 * ����ջ��pop
 * ��Сsize
 * �Ƿ�Ϊ��empty
 **/ 