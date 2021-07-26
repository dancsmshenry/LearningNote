//
// Created by HP on 2021/07/23.
//

#include "MyArray.h"

//默认构造
MyArray::MyArray() {
    cout << "MoRenGouZao DiaoYong" << endl;
    this->m_Capacity = 100;
    this->m_Size = 0;
    this->pAddress = new int[this->m_Capacity];
}

//有参构造
MyArray::MyArray(int capacity) {
    cout << "YouCanGouZao DiaoYong" << endl;
    this->m_Capacity = capacity;
    this->m_Size = 0;
    this->pAddress = new int[this->m_Capacity];
}

//拷贝构造
MyArray::MyArray(const MyArray &array) {
    cout << "KaoBeiGouZao DiaoYong" << endl;
    this->m_Capacity = array.m_Capacity;
    this->m_Size = array.m_Size;
    this->pAddress = new int[array.m_Capacity];

    for (int i = 0; i < array.m_Size; i ++ ){
        this->pAddress[i] = array.pAddress[i];
    }
}

//析构函数
MyArray::~MyArray() {
    if (this->pAddress != NULL){
        cout << "XiGouHanShu DiaoYong" << endl;
        delete[] this->pAddress;
        this->pAddress = NULL;
    }
}

void MyArray::push_Back(int val) {
    this->pAddress[this->m_Size] = val;
    this->m_Size ++ ;
}

int MyArray::getData(int index) {
    return this->pAddress[index];
}

void MyArray::setData(int index, int val) {
    this->pAddress[index] = val;
}

int MyArray::getSize() {
    return m_Size;
}

int& MyArray::operator[] (int index){
    return this->pAddress[index];
}