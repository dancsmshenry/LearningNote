#include <iostream>
#include <string>

using namespace std;

class Building{
    friend void goodGay(Building *building);

    public:
        Building(){
            this->m_SittingRoom = "sittingroom";
            this->m_BedRoom = "bedroom";
        }

        string m_SittingRoom;

    private://私有属性只能在类内
        string m_BedRoom;
};

//友元函数 目的访问类中的私有成员属性
void goodGay(Building *building){
    cout << "this is building->m_SittingRoom "<<building->m_SittingRoom << endl;
    cout << "this is building->m_BedRoom "<<building->m_BedRoom << endl;
}

void test01(){
    Building *building = new Building;
    goodGay(building);
}

int main(){
    test01();
}