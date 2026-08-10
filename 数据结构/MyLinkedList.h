#pragma once
#include <iostream>
//与数组对比：真正动态，但是丧失了随机访问的能力，访问元素需要从头开始遍历，时间复杂度为O(n)；
template <typename T>
class MyNode {
public:
	T data;
	MyNode* next;
	MyNode() : data(T()), next(nullptr) {}
	MyNode(T value) : data(value), next(nullptr) {}
	MyNode(T value, MyNode* nextNode) : data(value), next(nextNode) {}
	void readMyNode() {
		try {
			std::cout << data << std::endl;
		}
		catch (...) {
			std::cout << "[unprintable]" << std::endl;
		}
	}
};


//如果我们不允许通过MyNode类型对链表进行操作，只允许用户传入value，我们通过value对链表新建node并连接，那么我们可以做到链表无环
template <typename T>
class MyNoRingLinkedList {
protected:
	MyNode<T>* dummyHead;
	int size;
public:
	MyNoRingLinkedList() {
		dummyHead = new MyNode<T>();
		size = 0;
	}
	MyNoRingLinkedList(T* array, int length) {
		dummyHead = new MyNode<T>();
		MyNode<T>* node = dummyHead;
		for (int i = 0; i < length; i++) {
			MyNode<T>* nextNode = new MyNode<T>(array[i]);
			node->next = nextNode;
			node = nextNode;
		}
		size = length;
		//temp->next = nullptr;// This line is not necessary because the constructor of MyNode already sets next to nullptr.
	}
	MyNoRingLinkedList(const MyNoRingLinkedList<T>& other) {
		dummyHead = new MyNode<T>();
		size = 0;
		MyNode<T>* current = dummyHead;
		MyNode<T>* otherCurrent = other.dummyHead->next;
		while (otherCurrent != nullptr) {
			current->next = new MyNode<T>(otherCurrent->data);
			current = current->next;
			otherCurrent = otherCurrent->next;
		}
		size = other.size;
	}
	MyNoRingLinkedList<T>& operator=(const MyNoRingLinkedList<T>& other) {
		// Self-assignment check
		if (this == &other) {
			return *this;
		}
		//清空原有节点
		MyNode<T>* node = dummyHead->next;
		while (node != nullptr)
		{
			MyNode<T>* nextNode = node->next;
			delete node;
			node = nextNode;
		}
		dummyHead->next = nullptr; // Reset the next pointer of dummyHead to nullptr
		//复制新节点
		MyNode<T>* temp = dummyHead;
		MyNode<T>* current = temp;
		MyNode<T>* otherCurrent = other.dummyHead->next;
		while (otherCurrent != nullptr) {
			current->next = new MyNode<T>(otherCurrent->data);
			current = current->next;
			otherCurrent = otherCurrent->next;
		}
		size = other.size;
		return *this;
	}
	~MyNoRingLinkedList() {
		MyNode<T>* node = dummyHead;
		while (node != nullptr)
		{
			MyNode<T>* nextNode = node->next;
			delete node;
			node = nextNode;
		}
	}

	//检测链表元素个数
	int getSize() {
		return size;
	}

	//检测链表是否为空
	bool isEmpty() {
		return size == 0;
	}

	//在链表头插入元素
	void addFirst(T value) {
		MyNode<T>* newNode = new MyNode<T>(value);
		newNode->next = dummyHead->next;
		dummyHead->next = newNode;
		size++;
	}

	//在指定位置插入元素，index从0开始计数，index=0表示在链表头插入元素，index=size表示在链表尾插入元素
	void addInPlace(int index, T value) {
		if (index < 0 || index > size) {
			std::cout << "Error: Index out of bounds." << std::endl;
			return;
		}
		MyNode<T>* newNode = new MyNode<T>(value);
		MyNode<T>* current = dummyHead;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
		size++;
		return;
	}

	//在链表尾插入元素，复用addInPlace函数
	void addLast(T value) {
		addInPlace(size, value);
	}

	//获取指定位置的元素，index从0开始计数，index=0表示获取链表头的元素，index=size-1表示获取链表尾的元素
	T get(int index) {
		if (index < 0 || index >= size) {
			std::cout << "Error: Index out of bounds." << std::endl;
			return T(); // Return default value if index is out of bounds
		}
		MyNode<T>* currentNode = dummyHead->next;
		for (int i = 0; i < index; i++) {
			currentNode = currentNode->next;
		}
		return currentNode->data;
	}

	//获取链表头的元素，复用get函数
	T getFirst() {
		return get(0);
	}

	//获取链表尾的元素，复用get函数
	T getLast() {
		return get(size - 1);
	}

	//修改指定位置的元素，index从0开始计数，index=0表示修改链表头的元素，index=size-1表示修改链表尾的元素
	void set(int index, T value) {
		if (index < 0 || index >= size) {
			std::cout << "Error: Index out of bounds." << std::endl;
			return;
		}
		MyNode<T>* currentNode = dummyHead->next;
		for (int i = 0; i < index; i++) {
			currentNode = currentNode->next;
		}
		currentNode->data = value;
	}

	//查找链表中是否包含指定元素，返回true或false
	bool contains(T value) {
		MyNode<T>* currentNode = dummyHead->next;
		while (currentNode != nullptr) {
			if (currentNode->data == value) {
				return true;
			}
			currentNode = currentNode->next;
		}
		return false;
	}

	//根据索引删除链表中的元素，返回删除的元素
	T remove(int index) {
		if (index < 0 || index >= size) {
			std::cout << "Error: Index out of bounds." << std::endl;
			return T(); // Return default value if index is out of bounds
		}
		MyNode<T>* prevNode = dummyHead;
		for (int i = 0; i < index; i++) {
			prevNode = prevNode->next;
		}
		MyNode<T>* delNode = prevNode->next;
		prevNode->next = delNode->next;
		T retValue = delNode->data;
		delete delNode;
		size--;
		return retValue;
	}

	//删除链表头的元素，复用remove函数
	T removeFirst() {
		return remove(0);
	}

	//删除链表尾的元素，复用remove函数
	T removeLast() {
		return remove(size - 1);
	}

	//打印链表中的所有元素
	void readMyNoRingLinkedList() {
		MyNode<T>* currentNode = dummyHead->next;
		while (currentNode != nullptr) {
			try{
				std::cout << currentNode->data;
			}
			catch(...) {
				std::cout << "[unprintable]";
			}
			std::cout << " -> ";
			currentNode = currentNode->next;
		}
		std::cout << "nullptr" << std::endl;
		return;
	}

};

template<typename T>
class MyNRLLWithTail : public MyNoRingLinkedList<T> {
private:
	MyNode<T>* tail;
public:
	MyNRLLWithTail() : MyNoRingLinkedList<T>() {
		tail = this->dummyHead; // Initially, tail points to dummyHead
	}
	MyNRLLWithTail(T* array, int length) : MyNoRingLinkedList<T>(array, length) {
		MyNode<T>* current = this->dummyHead;
		while (current->next != nullptr) {
			current = current->next;
		}
		tail = current; // Set tail to the last node
	}
	MyNRLLWithTail(const MyNRLLWithTail<T>& other) : MyNoRingLinkedList<T>(other) {
		MyNode<T>* current = this->dummyHead;
		while (current->next != nullptr) {
			current = current->next;
		}
		tail = current; // Set tail to the last node
	}
	~MyNRLLWithTail() {
		// Destructor will be handled by the base class
	}

	T getLast() {
		return tail->data;
	}
	void addInPlace(int index, T value) {
		if (index < 0 || index > this->size) {
			std::cout << "Error: Index out of bounds." << std::endl;
			return;
		}
		MyNode<T>* newNode = new MyNode<T>(value);
		MyNode<T>* current = this->dummyHead;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
		if (index == this->size) { // If adding at the end, update tail
			tail = newNode;
		}
		this->size++;
	}
	void addLast(T value) {
		MyNode<T>* newNode = new MyNode<T>(value);
		tail->next = newNode;
		tail = newNode;
		this->size++;
	}
};