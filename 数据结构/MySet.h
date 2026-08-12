#pragma once
#include<iostream>
#include"MyBST.h"
#include"MyLinkedList.h"

template <typename T>
class MySet {
public:
	virtual void add(T e) = 0;
	virtual void remove(T e) = 0;
	virtual bool contains(T e) = 0;
	virtual int getSize() = 0;
	virtual bool isEmpty() = 0;
};

template <typename T>
class MyBSTSet : public MySet<T> {
private:
	MyBST<T> bst;
public:
	MyBSTSet(){}
	void add(T e) override {
		if (!bst.contains(e)) {//因为我们实现的BST元素可重复，所以添加元素需要检查
			bst.insert(e);
		}
	}
	void remove(T e) override {
		bst.removeOneElement(e);
	}
	bool contains(T e) override {
		return bst.contains(e);
	}
	int getSize() override{
		return bst.getSize();
	}
	bool isEmpty() override {
		return bst.isEmpty();
	}
};

template <typename T>
class MyNRLLSet : public MySet<T> {
private:
	MyNoRingLinkedList<T> list;
public:
	MyNRLLSet() {}
	int getSize() override {
		return list.getSize();
	}
	bool isEmpty() override {
		return list.isEmpty();
	}
	bool contains(T e) override {
		return list.contains(e);
	}
	void add(T e) override {
		if (!list.contains(e)) {
			list.addFirst(e);
		}
	}
	void remove(T e) override {
		//**性能低，因为list没有遍历方法
		for (int i = 0; i < list.getSize(); i++) {
			if (list.get(i) == e) {
				list.remove(i);
				return;
			}
		}
	}
};
