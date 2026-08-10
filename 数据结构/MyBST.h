#pragma once
#include <iostream>
#include "MyQueue.h"

template <typename T>
class MyBSTNode {
public:
	T data;
	MyBSTNode<T>* left;
	MyBSTNode<T>* right;
	MyBSTNode(T value) : data(value), left(nullptr), right(nullptr) {}
	// 析构函数，递归删除左右子树
	~MyBSTNode() {
		delete left;
		delete right;
	}
};



template <typename T>
class MyBST {
protected:
	MyBSTNode<T>* root;
	int size;

public:
	MyBST() : root(nullptr), size(0) {}
	~MyBST() {
		delete root;
	}
	int getSize() const { return size; }
	int isEmpty() const { return size == 0; }

private:
	// 通过node插入元素，为了避免用户直接调用，设置为私有函数，返回插入的节点指针
	MyBSTNode<T>* Insert(T value, MyBSTNode<T>* node = root) {
		//递归实现

		//if(node == nullptr) {
		//	size++;
		//	return new MyBSTNode<T>(value);
		//}
		//else {
		//	if(value<node->data) {
		//		node->left = Insert(value, node->left);
		//	}
		//	else {
		//		node->right = Insert(value, node->right);
		//	}
		//	return node;
		//}

		//循环实现
		MyBSTNode<T>* newNode = new MyBSTNode<T>(value);
		if(root == nullptr) {
			size++;
			return newNode;
		}
		while(node != nullptr) {
			if (value < node->data) {
				if (node->left == nullptr) {
					node->left = newNode;
					size++;
					break;
				}
				node = node->left;
			} else {
				if (node->right == nullptr) {
					node->right = newNode;
					size++;
					break;
				}
				node = node->right;
			}
		}
		return root;
	}
public:
	// 通过value插入元素，只能从root开始添加，用户调用
	void insert(T value) {
		root = Insert(value, root);
	}


private:
	bool Contains(T value, MyBSTNode<T>* node) {
		//递归实现
		if (node == nullptr) {
			return false;
		}
		if (value == node->data) {
			return true;
		} else if (value < node->data) {
			return Contains(value, node->left);
		} else {
			return Contains(value, node->right);
		}
		//循环实现
		//while (node != nullptr) {
		//	if (value == node->data) {
		//		return true;
		//	}
		//	else if (value < node->data) {
		//		node = node->left;
		//	}
		//	else {
		//		node = node->right;
		//	}
		//}
		//return false;
	}
public:
	bool contains(T value) {
		return Contains(value, root);
	}

public:
	void readMyBST(int mode){
		if(mode== 0) {
			readByPreOrder(root);
		}
		else if(mode == 1) {
			readByInOrder(root);
		}
		else if(mode == 2) {
			readByPostOrder(root);
		}
		else if(mode == 3) {
			readByLevelOrder(root);
		}
		else {
			std::cout << "Invalid mode!" << std::endl;
		}
	}
//前中后序遍历：递归写法，或使用栈
private:
	void readByPreOrder(MyBSTNode<T>* node, int depth=0) {
		if(node == nullptr) {
			return;
		}
		coutANode(node->data, depth);
		readByPreOrder(node->left, depth + 1);
		readByPreOrder(node->right, depth + 1);
	}
	void readByInOrder(MyBSTNode<T>* node, int depth = 0) {
		if(node == nullptr) {
			return;
		}
		readByInOrder(node->left, depth + 1);
		coutANode(node->data, depth);
		readByInOrder(node->right, depth + 1);
	}
	void readByPostOrder(MyBSTNode<T>* node, int depth = 0) {
		if (node == nullptr) {
			return;
		}
		readByPostOrder(node->left, depth + 1);
		readByPostOrder(node->right, depth + 1);
		coutANode(node->data, depth);
	}
//层级遍历：使用队列
	void readByLevelOrder(MyBSTNode<T>* node, int depth = 0) {
		MyArrayQueue<MyBSTNode<T>*> queue;
		queue.enqueue(node);
		while(!queue.isEmpty()) {
			MyBSTNode<T>* current = queue.dequeue();
			coutANode(current->data, depth);
			if(current->left != nullptr) {
				queue.enqueue(current->left);
			}
			if(current->right != nullptr) {
				queue.enqueue(current->right);
			}
		}
	}
	void coutANode(T value, int depth) {
		std::cout << value << " at depth " << depth << std::endl;
	}
};