#include <iostream>
#include <string>

using namespace std;

class Building{
    friend void goodGay(Building *building);

    public:
        Building(){
            this->m_SittingRoom = "客厅";
            this->m_BedRoom = "卧室";
        }

        string m_SittingRoom;//客厅

    private://私有属性只能在类内
        string m_BedRoom;//卧室
};

//友元函数 目的访问类中的私有成员属性
void goodGay(Building *building){
    cout << "好基友正在访问"<<building->m_SittingRoom << endl;
    cout << "好基友正在访问"<<building->m_BedRoom << endl;
}

void test01(){
    Building *building = new Building;
    goodGay(building);
}

int main(){
    test01();
}