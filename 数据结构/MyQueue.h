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

template <typename T>
class MyLoopQueue : public MyQueue<T> {
private:
	int front;
	int tail;
	int size;
	int capacity;
	T* array; //使用T*指针实现循环队列
	void resize(int newCapacity) {//resize函数只用于自身扩容缩容，不在外部调用，只需注意其在类内的逻辑
		T* newArray = new T[newCapacity + 1];
		for(int i=0;i<size;i++){
			newArray[i] = array[(front + i) % (capacity+1)];
		}
		delete[] array;
		array = new T[newCapacity + 1];
		std::copy(newArray, newArray + size, array);
		front = 0;
		tail = size;
		capacity = newCapacity;
	}
public:
	MyLoopQueue(int capacity = 10) : front(0), tail(0), size(0), capacity(capacity) { array = new T[capacity + 1]; }//因为循环队列需要一个额外的空间来区分队列满和队列空的情况，所以在初始化时，容量需要加1。
	MyLoopQueue(const MyLoopQueue& other) : front(other.front), tail(other.tail), size(other.size), capacity(other.capacity) { 
		delete[] array;
		array = new T[other.capacity + 1];
		std::copy(other.array, other.array + size, array); 
	}
	~MyLoopQueue() { delete[] array; }
	MyLoopQueue& operator=(const MyLoopQueue& other) {
		if(this != &other) {
			front = other.front;
			tail = other.tail;
			size = other.size;
			capacity = other.capacity;
			delete[] array;
			array = new T[other.capacity + 1];
			std::copy(other.array, other.array + size, array);
		}
		return *this;
	}
	//enqueue dequeue getFront getSize isEmpty readMyQueue
	int getCapacity() {
		return capacity;
	}
	void enqueue(T value) override {
		if (isFull()) {
			resize(2 * capacity);//扩容后头在0，尾在size
		}
		array[tail] = value;
		tail = (tail + 1) % (capacity + 1);
		size++;
	}
	T dequeue() override {
		if (!isEmpty()) {
			T ret = array[front];
			front = (front + 1) % (capacity + 1);
			size--;
			//动态缩容
			if (size <= (capacity + 1) / 4 && (capacity + 1) / 2 >= 10) {
				resize((capacity + 1) / 2);
			}
			return ret;
		}
		else {//报错
			std::cout << "MyLoopQueue is empty, cannot dequeue" << std::endl;
			std::cout << "return default value" << std::endl;
			return T();
		}
	}
	T getFront() override {
		if (!isEmpty()) {
			return array[front];
		}
		else {//报错
			std::cout << "MyLoopQueue is empty, cannot getFront" << std::endl;
			std::cout << "return default value" << std::endl;
			return T();
		}
	}
	int getSize() override {
		return size;
	}
	bool isFull() {
		return front == (tail + 1) % (capacity+1);
	}
	bool isEmpty() override {
		return front == tail;
	}
	void readMyQueue() override {
		std::cout<< "\n";
		std::cout << "This is a loop queue" << "\n";
		std::cout << "MyLoopQueue: size = " << this->getSize() << ", MyLoopQueue capacity = " << this->getCapacity() << std::endl;
		std::cout << "MyLoopQueue: front(" << front << ")[";
		for(int i = front; i != tail; i=(i+1)% (capacity + 1)) {
			std::cout << array[i];
			if (i != (tail+ (capacity + 1) - 1)% (capacity + 1)) {
				std::cout << ", ";
			}
		}
		std::cout << "] tail(" << tail << ")" << std::endl;
	}

};

