//
// Created by HP on 2021/07/23.
//

#pragma once
#ifndef __MYARRAY_H
#define __MYARRAY_H
#include <iostream>

using namespace std;

class MyArray{
public:
    MyArray();//默认构造 默认100容量
    MyArray(int capacity);
    MyArray(const MyArray& array);

    ~MyArray();

    //尾插法
    void push_Back(int val);

    //根据索引获取值
    int getData(int index);

    //根据索引设置值
    void setData(int index, int val);

    int getSize();

private:
    int *pAddress;//指向真正存储数据的指针
    int m_Size;//数组的大小
    int m_Capacity;//数组的容量
};

#endif //__MYARRAY_H
