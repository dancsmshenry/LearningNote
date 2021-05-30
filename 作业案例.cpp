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

        string m_Name;//人名
        int m_Score;//分数，平均分
};

void creatPerson(vector<Person> &v){
    string nameSeed = "ABCDE";
    for (int i = 0; i < 5; i++){
        string name = "选手";
        name += nameSeed[i];

        int score = 0;
        Person p(name, score);

        v.push_back(p);
    }
}

void setScore(vector<Person> &v){
    for (vector<Person>::iterator it = v.begin(); it != v.end(); ++it){
        //对五个人进行打分
        deque<int> d;
        for (int i = 0; i < 10; i ++){
            int score = rand() % 40 + 60;
            d.push_back(score);
        }

        // //先看一下打分
        // for (deque<int>::iterator it = d.begin(); it != d.end(); it++){
        //     cout << *it << " ";
        // }

        // cout << endl;

        //对成绩进行排序
        sort(d.begin(), d.end());

        //去掉最高值和最低值
        d.pop_back();
        d.pop_back();

        int sum = 0;//总分
        for (deque<int>::iterator it = d.begin(); it != d.end(); it ++ ){
            sum += *it;
        }

        int avg = sum /d.size();//平均分

        it->m_Score = avg;
    }
}

void showScore(vector<Person> &v){
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it ++ ){
        cout << "姓名为：" << it->m_Name << "  最终平均分为：" << it->m_Score << endl;
    }
}

int main(){
    srand((unsigned)time(NULL));//设置随机数种子

    vector<Person> v;//创建容器，存放选手  

    creatPerson(v);//创建5名选手

    //测试
    // for (vector<Person>::iterator it = v.begin(); it != v.end(); it ++){
    //     cout << "姓名：" << (*it).m_Name << endl;
    // }
    
    setScore(v);//打分

    //展示平均分
    showScore(v);
}