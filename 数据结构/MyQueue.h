#pragma once

//队列：先进先出，first in first out(FIFO)
/************
需要实现的功能：
void enqueue(T value);	//入队
T dequeue();			//出队
T getFront();			//获取队首元素
int getSize();			//获取队列中元素个数
bool isEmpty();			//判断队列是否为空
************/

#include <iostream>
#include "MyDynamicArray.h"

template <typename T>
class MyQueue {
private:

public:
	MyQueue() = default;
	virtual ~MyQueue(){}
	virtual void enqueue(T value) = 0;	//入队
	virtual T dequeue() = 0;			//出队
	virtual T getFront() = 0;			//获取队首元素
	virtual int getSize() = 0;			//获取队列中元素个数
	virtual bool isEmpty() = 0;			//判断队列是否为空
	virtual void readMyQueue() = 0;		//读取队列中的元素
};

template <typename T>
class MyArrayQueue : public MyQueue<T> {
private:
	MyDynamicArray<T> array;

public:
	MyArrayQueue(int capacity = 10) :array(capacity) {
	}
	MyArrayQueue(const MyArrayQueue& other) :array(other.array) {
		array = other.array;
	};
	MyArrayQueue& operator=(const MyArrayQueue& other) = default;
	~MyArrayQueue() = default; //array的删除在MyDynamicArray的析构函数中已经实现了

	void enqueue(T value) override {
		array.addLast(value);
	}
	T dequeue() override {
		return array.removeFirst();
	}
	T getFront() override {
		return array.getFirst();
	}
	int getSize() override {
		return array.getSize();
	}
	int getCapacity() {
		return array.getCapacity();
	}
	bool isEmpty() override {
		return array.isEmpty();
	}

	void readMyQueue() {
		std::cout << "\n";
		std::cout << "This is a queue using MyDynamicArray to realize" << "\n";
		std::cout << "MyArrayQueue: size = " << this->getSize() << ", capacity = " << this->getCapacity() << std::endl;
		std::cout << "Queue: front [";
		for(int i=0;i<this->getSize();i++){
			std::cout << array.get(i);
			if(i != this->getSize()-1){
				std::cout << ", ";
			}
		}
		std::cout << "] tail" << std::endl;
	}
};



