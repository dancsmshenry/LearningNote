#include <iostream>

using namespace std;

//只让visit做Building的好朋友，visit2不可以访问私有属性
class Building;//这里必须声明Building，否则编辑器会不知道goodGay中的Building是干什么的
//https://blog.csdn.net/qq_43259304/article/details/89605118
class goodGay{
    public:
        goodGay();

        void visit();
        void visit2();
    
    private:
        Building *building;
};

class Building{
    //让好基友类作为Building的好朋友
    //friend class goodGay;

    //让成员函数visit作为友元函数
    friend void goodGay::visit();

    public:
        Building();

        string m_SittingRoom;//客厅

    private:
        string m_BedRoom;//卧室
};

goodGay::goodGay(){
    building = new Building;
}

void goodGay::visit(){
    cout << "好基友正在访问，" << this->building->m_SittingRoom << endl;
    cout << "好基友正在访问，" << this->building->m_BedRoom << endl;
}

void goodGay::visit2(){
    cout << "好基友正在访问，" << this->building->m_SittingRoom << endl;
    //cout << "好基友正在访问，" << this->building->m_BedRoom << endl;
}

Building::Building(){
    this->m_SittingRoom = "客厅";
    this->m_BedRoom = "卧室";
}

void test01(){
    goodGay gg;
    gg.visit();
}

int main(){
    test01();
}