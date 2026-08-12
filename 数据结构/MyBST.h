#pragma once
#include <iostream>
#include <queue>
#include "MyQueue.h"
#include "MyStack.h"

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
	MyBSTNode<T>* Insert(T value, MyBSTNode<T>* node) {
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
		if (root == nullptr) {
			size++;
			return newNode;
		}
		while (node != nullptr) {
			if (value < node->data) {
				if (node->left == nullptr) {
					node->left = newNode;
					size++;
					break;
				}
				node = node->left;
			}
			else {
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
		}
		else if (value < node->data) {
			return Contains(value, node->left);
		}
		else {
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
	void readMyBST(int mode) {
		if (mode == 0) {
			readByPreOrder(root);
		}
		else if (mode == 1) {
			readByInOrder(root);
		}
		else if (mode == 2) {
			readByPostOrder(root);
		}
		else if (mode == 3) {
			readByLevelOrder(root);
		}
		else if (mode == 4) {
			readByInOrderWithStack(root);
		}
		else {
			std::cout << "Invalid mode!" << std::endl;
		}
	}
	//前中后序遍历：递归写法，或使用栈
private:
	void readByPreOrder(MyBSTNode<T>* node, int depth = 0) {
		if (node == nullptr) {
			return;
		}
		coutANode(node->data, depth);
		readByPreOrder(node->left, depth + 1);
		readByPreOrder(node->right, depth + 1);
	}
	void readByInOrder(MyBSTNode<T>* node, int depth = 0) {
		if (node == nullptr) {
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
	//仅使用栈实现中序遍历，其余两种略
	void readByInOrderWithStack(MyBSTNode<T>* node) {
		if (node == nullptr) {
			return;
		}
		MyArrayStack<std::pair<MyBSTNode<T>*, int>> stack;
		MyBSTNode<T>* current = node;
		int depth = 0;
		while (current != nullptr || !stack.isEmpty()) {
			while (current != nullptr) {
				stack.push({ current, depth });
				current = current->left;
				depth++;
			}
			std::pair<MyBSTNode<T>*, int> top = stack.pop();
			node = top.first;
			depth = top.second;
			//auto [node, depth] = stack.pop();
			coutANode(node->data, depth);
			current = node->right;
			depth++;
		}
	}
	//层级遍历：使用队列
	void readByLevelOrder(MyBSTNode<T>* node, int depth = 0) {
		if(node == nullptr) {
			return;
		}
		std::queue<std::pair<MyBSTNode<T>*, int>> q; //pair<node,depth>
		//MyArrayQueue<std::pair<MyBSTNode<T>*, int>> queue;//pair<node,depth>
		q.push({ node,depth });
		while (!q.empty()) {
			std::pair<MyBSTNode<T>*, int> front = q.front();
			q.pop();
			MyBSTNode<T>* current = front.first;
			int currentDepth = front.second;
			coutANode(current->data, currentDepth);
			if (current->left != nullptr) {
				q.push({ current->left, currentDepth + 1 });
			}
			if (current->right != nullptr) {
				q.push({ current->right, currentDepth + 1 });
			}
		}
	}
	void coutANode(T value, int depth) {
		try {
			std::cout << value;
		}
		catch(...){
			std::cout << "[unprintable]";
		}
		std::cout << " at depth " << depth << std::endl;
	}

private:
	MyBSTNode<T>* removeMinElementPrivate(MyBSTNode<T>* node, T& minVal) {//返回值为处理后的子树根节点
		if (node == nullptr) {//空节点
			minVal = T();
			return nullptr;
		}
		MyBSTNode<T>* originalNode = node;
		MyBSTNode<T>* parent = node;
		while (node->left != nullptr) {
			parent = node;
			node = node->left;
		}
		if (parent == node) {//没有进入while，node为最左节点，处理右子树
			minVal = node->data;
			MyBSTNode<T>* rightChild = node->right;
			node->right = nullptr; // 断开与右子树的连接
			delete node;
			size--;
			return rightChild;
		}
		else {//进入while，node为最左节点，parent为其父节点，把node右子树与parent左子树连接
			minVal = node->data;
			parent->left = node->right; // 将父节点的左子树指向最小节点的右子树
			node->right = nullptr; // 断开与右子树的连接
			delete node;
			size--;
			return originalNode; // 返回原来的根节点	
		}
	}
	MyBSTNode<T>* removeMaxElementPrivate(MyBSTNode<T>* node, T& maxVal) {
		if (node == nullptr) {
			maxVal = T();
			return nullptr;
		}
		MyBSTNode<T>* originalNode = node;
		MyBSTNode<T>* parent = node;
		while (node->right != nullptr) {
			parent = node;
			node = node->right;
		}
		if(parent == node) {//没有进入while，node为最右节点，处理左子树
			maxVal = node->data;
			MyBSTNode<T>* leftChild = node->left;
			node->left = nullptr; // 断开与左子树的连接
			delete node;
			size--;
			return leftChild;
		}
		else {//进入while，node为最右节点，parent为其父节点，把node左子树与parent右子树连接
			maxVal = node->data;
			parent->right = node->left; // 将父节点的右子树指向最大节点的左子树
			node->left = nullptr; // 断开与左子树的连接
			delete node;
			size--;
			return originalNode; // 返回原来的根节点	
		}
	}
	MyBSTNode<T>* removeOneElementPrivate(T value, MyBSTNode<T>* node) {
		if (node == nullptr) {
			return node;
		}
		else if (node->data == value) {
			T tempVal;
			if (node->left != nullptr) {
				node -> left = removeMaxElementPrivate(node->left, tempVal);
				node->data = tempVal;
				return node;
			}
			else if (node->right != nullptr) {
				node -> right = removeMinElementPrivate(node->right, tempVal);
				node->data = tempVal;
				return node;
			}
			else {
				delete node;
				size--;
				return nullptr;
			}
		}
		else if (node->data < value) {
			node->right = removeOneElementPrivate(value, node->right);
			return node;
		}
		else if (node->data > value) {
			node->left = removeOneElementPrivate(value, node->left);
			return node;
		}
	}
public:
	void removeMinElement(T& minVal) {
		root = removeMinElementPrivate(root, minVal);
	}
	void removeMaxElement(T& maxVal) {
		root = removeMaxElementPrivate(root, maxVal);
	}
	bool removeOneElement(T value) {
		int preSize = size;
		root = removeOneElementPrivate(value, root);
		if (preSize == size) {
			std::cout << "Value " << value << " not found in BST." << std::endl;
			return false;
		}
		return true;
	}
};