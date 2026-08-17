#pragma once
#include <iostream>

//映射，字典，支持add remove contains get set getSize isEmpty，其中getSize与isEmpty直接在父类中实现
template <typename K, typename V>
class MyMap {
protected:
	int size;
public:
	MyMap() :size(0) {}
	virtual void add(const K& k,const V& v) = 0;
	virtual V remove(const K& k) = 0;
	virtual bool contains(const K& k) = 0;
	virtual V get(const K& k) = 0;
	virtual void set(const K& k, const V& v) = 0;
	int getSize() { return size; }
	bool isEmpty() { return size == 0; }
};

template <typename K, typename V>
class MyNRLLMap:public MyMap<K,V> {
private:
    // 私有嵌套节点类 —— 外部不可见
    struct Node {
        K key;
        V value;
        Node* next;

        Node() : key(K()), value(V()), next(nullptr) {}
        Node(const K& k, const V& v, Node* n = nullptr)
            : key(k), value(v), next(n) {
        }
    };

    Node* dummyHead;   // 链表头指针

public:
    MyNRLLMap() :MyMap<K,V>(), dummyHead(new Node()) {}
    MyNRLLMap(const MyNRLLMap&) = delete;
    MyNRLLMap& operator=(const MyNRLLMap&) = delete;
    ~MyNRLLMap() {
        clear();
        delete dummyHead;
    }

    void clear() {
        Node* current = dummyHead->next;
        while (current) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        dummyHead->next = nullptr;
        this->size = 0;
    }

private:
    Node* getNode(const K& k) {
        Node* current = dummyHead->next;
        while (current) {
            if (current->key == k) return current;
            current = current->next;
        }
        return nullptr;
    }

public:
    bool contains(const K& k) {
        return getNode(k) != nullptr;
    }
    V get(const K& k) {
        Node* node = getNode(k);
        if (node == nullptr) {
            std::cout << "Node with key k not found. Function get returns default value.\n";
            return V();
        }
        return node->value;
    }
    void add(const K& k, const V& v) override {
        Node* node = getNode(k);
        if (node == nullptr) {
            dummyHead->next = new Node(k, v, dummyHead->next);
            this->size++;
        }
        else {
            std::cout << "Key already in the Map. Overwriting the original value." << "\n";
            node->value = v;
        }
        return;
    }
    void set(const K& k, const V& v) override {
        Node* node = getNode(k);
        if (node == nullptr) {
            std::cout << "Error with MyNRLLMap::set(K k, V v). Node with key k does not exist.\n"; 
        }
        else { 
            node->value = v; 
        }
        return;
    }
    V remove(const K& k) override {
        Node* prev = dummyHead;
        while (prev->next != nullptr) {
            if (prev->next->key == k) {
                break;
            }
            prev = prev->next;
        }
        if (prev->next != nullptr) {
            V ret = prev->next->value;
            Node* delNode = prev->next;
            prev->next = delNode->next;
            delNode->next = nullptr;
            delete delNode;
            this->size--;
            return ret;
        }
        std::cout << "Node with key k not found. Function remove returns default value.\n";
        return V();
    }
};

template <typename K, typename V>
class MyBSTMap :public MyMap<K,V> {
private:
    class Node {
    public: 
        K key;
        V value;
        Node* left;
        Node* right;
        Node(K key, V value) :key(key),value(value),left(nullptr),right(nullptr){}
    };
    Node* root;
    void clearTree(Node* node) {
        if (!node) return;
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
public:
    MyBSTMap():MyMap<K, V>(),root(nullptr) {}
    MyBSTMap(const MyBSTMap&) = delete;
    MyBSTMap& operator=(const MyBSTMap&) = delete;
    ~MyBSTMap() {
        clearTree(root);
    }
    void clear() {
        clearTree(root);
        root = nullptr;
        this->size = 0;
    }
private:
    Node* Add(const K& key, const V& value, Node* node) {
        if (node == nullptr) {
            this->size++;
            return new Node(key, value);
        }
        //注意：key唯一，不允许重复的key出现，检索到相同key视为set
        if (key < node->key) {
            node->left = Add(key, value, node->left);
        }
        else if (key > node->key) {
            node->right = Add(key, value, node->right);
        }
        else {
            node->value = value;
        }
        return node;
    }
public:
    void add(const K& key, const V& value) override {
        root = Add(key, value, root);
    }

private:
    Node* getNode(Node* node, const K& key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (key < node->key) {
            return getNode(node->left, key);
        }
        else if (key > node->key) {
            return getNode(node->right, key);
        }
        else {//key == node->key
            return node;
        }
    }
public:
    bool contains(const K& key) override {
        return getNode(root, key) != nullptr;
    }
    V get(const K& key) override {
        Node* node = getNode(root, key);
        if (node != nullptr) {
            return node->value;
        }
        else {
            std::cout << "Function get failed because key was not found.Returning default value.\n";
            return V();
        }
    }
    void set(const K& key, const V& value) override {
        Node* node = getNode(root, key);
        if (node == nullptr) {
            std::cout << "Function set failed because key was not found.\n";
        }
        else {
            node->value = value;
        }
        return;
    }

    //remove
private:
    //返回值为处理后的子树根（node），并将待修改的key, value对存入K& minKey, V& minKeyVal中
    Node* removeMinElementPrivate(Node* node, K& minKey, V& valOfMinKey) {
        if (node == nullptr) {
            minKey = K();
            valOfMinKey = V();
            return nullptr;
        }
        Node* originalNode = node;
        Node* parent = node;
        while (node->left != nullptr) {
            parent = node;
            node = node->left;
        }
        if (parent == node) {//没有进入while，node为最左节点，处理其右子树
            minKey = node->key;
            valOfMinKey = node->value;
            Node* rightChild = node->right;
            node->right = nullptr;
            delete node;
            this->size--;
            return rightChild;
        }
        else {//进入while，node为最左节点，parent为其父节点，把node右子树与parent左子树连接
            minKey = node->key;
            valOfMinKey = node->value;
            parent->left = node->right;
            node->right = nullptr;
            delete node;
            this->size--;
            return originalNode;
        }
    }
    //参考以下注释的函数
    
    //MyBSTNode<T>* removeMinElementPrivate(MyBSTNode<T>* node, T& minVal) {//返回值为处理后的子树根节点
    //    if (node == nullptr) {//空节点
    //        minVal = T();
    //        return nullptr;
    //    }
    //    MyBSTNode<T>* originalNode = node;
    //    MyBSTNode<T>* parent = node;
    //    while (node->left != nullptr) {
    //        parent = node;
    //        node = node->left;
    //    }
    //    if (parent == node) {//没有进入while，node为最左节点，处理右子树
    //        minVal = node->data;
    //        MyBSTNode<T>* rightChild = node->right;
    //        node->right = nullptr; // 断开与右子树的连接
    //        delete node;
    //        size--;
    //        return rightChild;
    //    }
    //    else {//进入while，node为最左节点，parent为其父节点，把node右子树与parent左子树连接
    //        minVal = node->data;
    //        parent->left = node->right; // 将父节点的左子树指向最小节点的右子树
    //        node->right = nullptr; // 断开与右子树的连接
    //        delete node;
    //        size--;
    //        return originalNode; // 返回原来的根节点	
    //    }
    //}

    Node* removeOneElementPrivate(K key, V& valueOfDelNode, Node* node) {
        if (node == nullptr) {
            return node;
        }
        else if (node->key == key) {
            valueOfDelNode = node->value;
            K tempKey;
            V tempVal;
            if (node->right != nullptr) {
                node->right = removeMinElementPrivate(node->right, tempKey, tempVal);
                node->key = tempKey;
                node->value = tempVal;
                return node;
            }
            else {
                Node* tempNode = node->left;
                delete node;
                this->size--;
                return tempNode;
            }
        }
        else if (node->key < key) {
            node->right = removeOneElementPrivate(key, valueOfDelNode, node->right);
            return node;
        }
        else if (node->key > key) {
            node->left = removeOneElementPrivate(key, valueOfDelNode, node->left);
            return node;
        }
    }

    //参考以下注释的函数

    //MyBSTNode<T>* removeOneElementPrivate(T value, MyBSTNode<T>* node) {
    //    if (node == nullptr) {
    //        return node;
    //    }
    //    else if (node->data == value) {
    //        T tempVal;
    //        if (node->left != nullptr) {
    //            node->left = removeMaxElementPrivate(node->left, tempVal);
    //            node->data = tempVal;
    //            return node;
    //        }
    //        else if (node->right != nullptr) {
    //            node->right = removeMinElementPrivate(node->right, tempVal);
    //            node->data = tempVal;
    //            return node;
    //        }
    //        else {
    //            delete node;
    //            size--;
    //            return nullptr;
    //        }
    //    }
    //    else if (node->data < value) {
    //        node->right = removeOneElementPrivate(value, node->right);
    //        return node;
    //    }
    //    else if (node->data > value) {
    //        node->left = removeOneElementPrivate(value, node->left);
    //        return node;
    //    }
    //}

public:
    V remove(const K& key) override {
        V memVal;
        removeOneElementPrivate(key, memVal, root);
        return memVal;
    }
};