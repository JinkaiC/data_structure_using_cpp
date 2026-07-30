#pragma once
#include <iostream>
#include "MyDynamicArray.h"
/*Stack: Last In First Out*/
/***************
栈的操作
MyStack<T>
void push(e);
T pop();
T peek();
int getSize();
bool isEmpty();
***************/

template <typename T>
class MyStack {
protected:
	MyDynamicArray<T> data; // 存储栈元素的数组，已经分配10个空间
	int capacity; // 栈的容量

public:
	virtual ~MyStack() {}
	virtual void push(T e) = 0; // 入栈操作
	virtual T pop() = 0; // 出栈操作
	virtual T peek() = 0; // 获取栈顶元素
	virtual int getSize() = 0; // 获取栈的大小
	virtual bool isEmpty() = 0; // 判断栈是否为空
};

template <typename T>
class MyArrayStack : public MyStack<T> {//基于动态数组实现的栈
private:

public:
	MyArrayStack(int capacity = 10) {
		this->capacity = capacity; // 默认容量为10
		this->data = MyDynamicArray<T>(this->capacity); // 初始化动态数组
	}
	void push(T e) override {
		this->data.addLast(e); // 将元素添加到数组末尾
		this->capacity = this->data.getCapacity(); // 更新容量
	}
	T pop() override {
		T e = this->data.removeLast(); // 移除数组末尾元素
		this->capacity = this->data.getCapacity(); // 更新容量
		return e;
	}
	T peek() override {
		return this->data.getLast(); // 获取数组末尾元素
	}
	int getSize() override {
		return this->data.getSize(); // 获取数组大小
	}
	bool isEmpty() override {
		return this->data.isEmpty(); // 判断数组是否为空
	}
	void readMyArrayStack() {
		std::cout << "\n";
		std::cout << "MyArrayStack: size = " << this->getSize() << ", capacity = " << this->capacity << std::endl;
		std::cout << "Stack: [";
		for(int i = 0; i < this->getSize(); i++) {
			std::cout << this->data.get(i);
			if (i != this->getSize() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << "] top" << std::endl;
	}
};