#pragma once
#include <iostream>
#include <algorithm>   // 用于 std::min

class MyArray {
private:
    int* data;
    int size;
    int capacity;
    static const int POUTOFRANGEERROR;
    static const int POUTOFSIZEERROR;
    static const int FULLARRAYERROR;

public:
    // 构造函数
    MyArray(int capacity = 10);
    // 复制构造函数（参数：旧对象和目标容量）
    MyArray(const MyArray& old, int capacity);

    // 获取数组已存数据量
    int getSize();
    // 获取数组容量（注意：sizeof(data) 返回指针大小，不是实际容量）
    int getCapacity();
    // 判断空数组
    bool isEmpty();
    // 判断满数组
    bool isFull();
    // 判断索引是否越界
    bool pIsOutOfRange(int p);

    /* 
    在指定位置插入元素
    paras:  n:输入的元素
	        p:插入位置
    */
    void addInPlace(int n, int p);
    // 在末尾添加元素
    void addToEnd(int e);
    // 在头部添加元素
    void addToBegin(int b);

    //获取p位置的元素
    int get(int p);

    //修改指定位置p的元素为n
    int set(int n, int p);

    // 输出数组元素
    void readArray();
};