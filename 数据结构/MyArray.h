#pragma once
#include <iostream>
#include <algorithm>   // 用于 std::min

template<typename T>
class MyArray {
protected:
    T* data;
    int size;
    int capacity;
    static const int POUTOFRANGEERROR;
    static const int POUTOFSIZEERROR;
    static const int FULLARRAYERROR;
public:
    // 构造函数
    MyArray(int capacity = 10);
    // 另一构造函数（参数：旧对象和目标容量）
    MyArray(const MyArray& old, int capacity);
    // 拷贝构造函数（深拷贝）
    MyArray(const MyArray& other) {
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        std::copy(other.data, other.data + size, data);
    }

    // 拷贝赋值运算符（深拷贝）
    MyArray& operator=(const MyArray& other) {
        if (this != &other) {
            size = other.size;
            capacity = other.capacity;
            T* newData = new T[other.capacity];
            std::copy(other.data, other.data + other.size, newData);
            delete[] data;
            data = newData;
        }
        return *this;
    }

    //析构函数
    ~MyArray();

    // 获取数组已存数据量
    int getSize();
    // 获取数组容量
    int getCapacity();
    // 判断空数组
    bool isEmpty();
    // 判断满数组
    bool isFull();
    // 判断索引是否越界
    bool pIsOutOfRange(int p);

	//修改数组容量为newCapacity，若newCapacity小于size，则size变为newCapacity
    void resize(int newCapacity);

    /* 
    在指定位置插入元素
    paras:  n:输入的元素
	        p:插入位置
    */
    void addInPlace(T n, int p);
    // 在末尾添加元素
    void addLast(T e) { 
		//std::cout << "using base class addLast" << "\n";
        addInPlace(e, size); 
    }
    // 在头部添加元素
    void addFirst(T b) { 
		//std::cout << "using base class addFirst" << "\n";
        addInPlace(b, 0); 
    }

    //获取p位置的元素
    T get(int p);

    //获取头尾元素
	T getFirst() { return get(0); }
	T getLast() { return get(size - 1); }

    //修改指定位置p的元素为n
    void set(T n, int p);

    //确定数组中是否存在元素e
    bool contain(T e);

    //寻找元素e，返回第一个e位置的索引，若未找到返回-1
    int find(T e);

	//删除指定位置p的元素,返回成功删除的元素，若删除失败返回默认值
	T remove(int p);

    //删除并返回头元素
	T removeFirst() { 
		//std::cout << "using base class removeFirst" << "\n";
        return remove(0); 
    }
    //删除并返回尾元素
	T removeLast() { 
		//std::cout << "using base class removeLast" << "\n";
        return remove(size - 1); 
    }

    //删除指定元素e一次
    bool removeElementOnce(T e);

    // 输出数组元素
    void readArray();
};

//实现

// 静态成员变量的定义（必须在 .cpp 中定义，否则链接报错）
template<typename T>
const int MyArray<T>::POUTOFRANGEERROR = -1;

template<typename T>
const int MyArray<T>::POUTOFSIZEERROR = -2;

template<typename T>
const int MyArray<T>::FULLARRAYERROR = -3;

// 构造函数
template<typename T>
MyArray<T>::MyArray(int capacity) {
    MyArray::capacity = capacity;
    data = new T[capacity];
    size = 0;
}

// 构造函数，复制原数组，可变大小
template<typename T>
MyArray<T>::MyArray(const MyArray& old, int capacity) {
    MyArray::capacity = capacity;
    data = new T[capacity];
    int n = std::min(old.size, capacity);
    size = n;
	std::copy(old.data, old.data + n, data);
}

// 析构函数
template<typename T>
MyArray<T>::~MyArray() {
    delete[] data;
}

template<typename T>
int MyArray<T>::getSize() {
    return size;
}

template<typename T>
int MyArray<T>::getCapacity() {
    return capacity;
}

template<typename T>
bool MyArray<T>::isEmpty() {
    return size == 0;
}

template<typename T>
bool MyArray<T>::isFull() {
    return capacity == size;
}

template<typename T>
bool MyArray<T>::pIsOutOfRange(int p) {
    return p < 0 || p >= capacity;
}

template<typename T>
void MyArray<T>::resize(int newCapacity) {
    if (newCapacity < 0) {
        std::cout << "error happened in resize!\n";
        std::cout << "capacity = " << getCapacity() << "\n";
        std::cout << "the new capacity is negative!\n";
        return;
    }
    T* newData = new T[newCapacity];
    int n = std::min(size, newCapacity);
    for (int i = 0; i < n; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
    //std::cout << capacity << "\n";
    size = n; // Update size if the new capacity is smaller than the current size
}

template<typename T>
void MyArray<T>::addInPlace(T n, int p) {
    try {
		//std::cout << "using base class addInPlace" << "\n";
        if (pIsOutOfRange(p)) {
            throw POUTOFRANGEERROR;
        }
        else if(p > size) {
            throw POUTOFSIZEERROR;
		}
        else if (isFull()) {
            throw FULLARRAYERROR;
        }
        else {
            for (int i = size - 1; i >= p; --i) {
                data[i + 1] = data[i];
            }
            data[p] = n;
            ++size;
        }
    }
    catch (int e) {
        if (e == FULLARRAYERROR) {
            std::cout << "error happened in addInPlace!\n";
            std::cout << "capacity = " << getCapacity() << "\n";
            std::cout << "space is full, you may try to create a biggger array.\n";
        }
        if (e == POUTOFRANGEERROR) {
            std::cout << "error happened in addInPlace!\n";
            std::cout << "capacity = " << getCapacity() << "\n";
            std::cout << "the index p is out of range!\n";
        }
        if(e == POUTOFSIZEERROR) {
            std::cout << "error happened in addInPlace!\n";
            std::cout << "size = " << getSize() << "\n";
            std::cout << "the index p is out of the size of the array!\n";
		}
    }
    catch (...) {
        std::cout << "errors happened in addInPlace\n";
        std::cout << "errors not defined in class MyArrayP happened.\n";
		throw std::logic_error("Unexpected error in addInPlace function"); // Rethrow as a standard exception
    }
}

template<typename T>
T MyArray<T>::get(int p) {
    try {
        if (pIsOutOfRange(p)) {
            throw POUTOFRANGEERROR;
        }
        else if (p >= size) {
            throw POUTOFSIZEERROR;
        }
        else {
            return data[p];
        }
    }
    catch (int e) {
        if (e == POUTOFRANGEERROR) {
            std::cout << "error happened in get!\n";
            std::cout << "capacity = " << getCapacity() << "\n";
            std::cout << "the index p is out of range!\n";
        }
        else if (e == POUTOFSIZEERROR) {
            std::cout << "error happened in get!\n";
            std::cout << "size = " << getSize() << "\n";
            std::cout << "the index p is out of the size of the array!\n";
        }
		std::cout << "get function failed, returning default value.\n";
		return T(); // Return default value of T in case of error
    }
    catch (...) {
        std::cout << "errors happened in get\n";
        std::cout << "errors not defined in class MyArrayP happened.\n";
		throw std::logic_error("Unexpected error in get function"); // Rethrow as a standard exception
    }
}

template<typename T>
void MyArray<T>::set(T n, int p) {
    try {
        if (pIsOutOfRange(p)) {
            throw POUTOFRANGEERROR;
        }
        else if (p >= size) {
            throw POUTOFSIZEERROR;
        }
        else {
            data[p] = n;
            return;
        }
    }
    catch (int e) {
        if (e == POUTOFRANGEERROR) {
            std::cout << "error happened in set!\n";
            std::cout << "capacity = " << getCapacity() << "\n";
            std::cout << "the index p is out of range!\n";
        }
        else if (e == POUTOFSIZEERROR) {
            std::cout << "error happened in set!\n";
            std::cout << "size = " << getSize() << "\n";
            std::cout << "the index p is out of the size of the array!\n";
        }
    }
    catch (...) {
        std::cout << "errors happened in set\n";
        std::cout << "errors not defined in class MyArrayP happened.\n";
		throw std::logic_error("Unexpected error in set function"); // Rethrow as a standard exception
    }
}

template<typename T>
bool MyArray<T>::contain(T e) {
    for (int i = 0; i < size; i++) {
        if (data[i] == e) {
            return true;
        }
    }
    return false;
}

template<typename T>
int MyArray<T>::find(T e) {
    for (int i = 0; i < size; i++) {
        if (data[i] == e) {
            return i;
        }
    }
    return -1;
}

template<typename T>
T MyArray<T>::remove(int p) {
    try {
        if(pIsOutOfRange(p)) {
            throw POUTOFRANGEERROR;
        }
        else if (p >= size) {
            throw POUTOFSIZEERROR;
        }
        else {
			T oldValue = data[p];
            for (int i = p; i < size - 1; ++i) {
                data[i] = data[i + 1];
            }
            --size;
            return oldValue;
		}
    }
    catch (int e) {
        if (e == POUTOFRANGEERROR) {
            std::cout << "error happened in remove!\n";
            std::cout << "capacity = " << getCapacity() << "\n";
            std::cout << "the index p is out of range!\n";
        }
        else if (e == POUTOFSIZEERROR) {
            std::cout << "error happened in remove!\n";
            std::cout << "size = " << getSize() << "\n";
            std::cout << "the index p is out of the size of the array!\n";
        }
        std::cout << "remove function failed, returning default value.\n";
        return T();
    }
    catch (...) {
        std::cout << "errors happened in remove\n";
        std::cout << "errors not defined in class MyArrayP happened.\n";
		throw std::logic_error("Unexpected error in remove function"); // Rethrow as a standard exception
	}
}

template<typename T>
bool MyArray<T>::removeElementOnce(T e) {
	int i = find(e);
    if(i==-1) {
        return false;
    }
    else {
        remove(i);
        return true;
	}
}

template<typename T>
void MyArray<T>::readArray() {
    std::cout << "\n";
    std::cout << "capacity = " << capacity << ", size = " << size << "\n";
	std::cout << "Array elements: [";
    for (int i = 0; i < size; ++i) {
        std::cout << data[i];
        if (i < size - 1) {
            std::cout << ", ";
		}
    }
    std::cout << "]\n";
}