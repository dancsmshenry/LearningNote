#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

//list是双向链表
void test01(){
    list<int> myList;
    for (int i = 0; i < 10; i++){
        myList.push_back(i);
    }

    list<int>::_Nodeptr node = myList._Myhead->_NEXT;
    
}

int main(){

}