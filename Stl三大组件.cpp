#include <iostream>
#include <vector>
#include <string>
#include <algorithm>//ʹ��ϵͳ�㷨��ͷ�ļ�

using namespace std;

void MyPrint(int v){//�����Ҳ��˳�򣬼�������ִ���������֮ǰ���Ѿ������������������
    cout << v << endl;
}

//���������������ܣ���ָ�����
//��ָͨ��Ҳ��һ�ֵ�����
void test01(){
    int array[5] = {0,1,2,3,4};

    int *p = array;//ָ��ָ�������׵�ַ &array[0]

    for (int i = 0; i < 5; ++i){
        //cout << array[i] << endl;
        cout << *(p + i) << endl;
    }
}

//vector
void test02(){
    //����һ��vector����������������int�������ݣ���������v
    vector<int> v;

    //�������м�������
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    //���������е����ݣ����õ�����
    vector<int>::iterator itBegin = v.begin();//itBeginָ�����v�����еĳ�ʼλ��

    vector<int>::iterator itEnd = v.end();//itEndָ��v���������һ��λ�õ���һ����ַ

    while (itBegin != itEnd){
        cout << *itBegin << endl;
        itBegin ++ ;
    }//�о��������������Ϊָ�룿��

    //�ڶ��ֱ�����ʽ
    // for (int i = 0; i < 10; i ++ )
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++ it){
        cout << *it << endl;
    }

    //�����ֱ�����ʽ�������㷨
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

    v.push_back(Person(10, "��ͷ����"));
    v.push_back(Person(20, "Сͷ�ְ�"));
    v.push_back(Person(30, "����������"));

    //����
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it ++){
        cout << "�����ǣ�" << (*it).m_Name << "�������ǣ�" << it->m_Age << endl;
        //������->�����ʣ�Ҳ������.������
    }
    
}

//����Զ����������͵�ָ��
void test04(){
    vector<Person*> v;//�����ŵ���ָ���ˣ����������Ҫ����һ��

    Person p1(10, "��ͷ����");
    Person p2(20, "Сͷ�ְ�");
    Person p3(30, "����������");

    v.push_back(&p1);//��ѵ�����������ﴴ����ʱ����555
    v.push_back(&p2);
    v.push_back(&p3);

    //����
    for (vector<Person*>::iterator it = v.begin(); it != v.end(); it ++){
        cout << "�����ǣ�" << (*it)->m_Name << "�������ǣ�" << (*it)->m_Age << endl;
        //������->�����ʣ�Ҳ������.������
    }
    
}

//����Ƕ������
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
    //��С���������������
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
 * ���� vector
 * �㷨 for_each������ÿ��Ԫ�أ� ͷ�ļ� algorithm
 * ������iterator ÿ�����������Լ�ר���ĵ�����
 * v.begin()��ָ��ͷ��Ԫ�صĵ�ַ��,v.end()��ָ�����һ��Ԫ�صĺ�һ��λ�ã�
 **/ 