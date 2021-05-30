/*
 * @Author: dancsmshenry
 * @Email: 1175152442@qq.com
 * @Date: 2021-05-30 14:37:31
 * @Last Modified by: dancsmshenry
 * @Last Modified time: 2021-05-30 15:03:17
 * @Description: Description
 */

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <ctime>

using namespace std;

class Person{
    public:
        Person(string name, int score){
            this->m_Name = name;
            this->m_Score = score;
        }

        string m_Name;//����
        int m_Score;//������ƽ����
};

void creatPerson(vector<Person> &v){
    string nameSeed = "ABCDE";
    for (int i = 0; i < 5; i++){
        string name = "ѡ��";
        name += nameSeed[i];

        int score = 0;
        Person p(name, score);

        v.push_back(p);
    }
}

void setScore(vector<Person> &v){
    for (vector<Person>::iterator it = v.begin(); it != v.end(); ++it){
        //������˽��д��
        deque<int> d;
        for (int i = 0; i < 10; i ++){
            int score = rand() % 40 + 60;
            d.push_back(score);
        }

        // //�ȿ�һ�´��
        // for (deque<int>::iterator it = d.begin(); it != d.end(); it++){
        //     cout << *it << " ";
        // }

        // cout << endl;

        //�Գɼ���������
        sort(d.begin(), d.end());

        //ȥ�����ֵ�����ֵ
        d.pop_back();
        d.pop_back();

        int sum = 0;//�ܷ�
        for (deque<int>::iterator it = d.begin(); it != d.end(); it ++ ){
            sum += *it;
        }

        int avg = sum /d.size();//ƽ����

        it->m_Score = avg;
    }
}

void showScore(vector<Person> &v){
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it ++ ){
        cout << "����Ϊ��" << it->m_Name << "  ����ƽ����Ϊ��" << it->m_Score << endl;
    }
}

int main(){
    srand((unsigned)time(NULL));//�������������

    vector<Person> v;//�������������ѡ��  

    creatPerson(v);//����5��ѡ��

    //����
    // for (vector<Person>::iterator it = v.begin(); it != v.end(); it ++){
    //     cout << "������" << (*it).m_Name << endl;
    // }
    
    setScore(v);//���

    //չʾƽ����
    showScore(v);
}