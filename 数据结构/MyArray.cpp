#include "MyArray.h"

// 静态成员变量的定义（必须在 .cpp 中定义，否则链接报错）
const int MyArray::POUTOFRANGEERROR = -1;
const int MyArray::POUTOFSIZEERROR = -2;
const int MyArray::FULLARRAYERROR = -3;

// 构造函数
MyArray::MyArray(int capacity) {
    MyArray::capacity = capacity;
    data = new int[capacity];
    size = 0;
}

// 构造函数，复制原数组，可变大小
MyArray::MyArray(const MyArray& old, int capacity) {
    MyArray::capacity = capacity;
    data = new int[capacity];
    int n = std::min(old.size, capacity);
    for (int i = 0; i < n; ++i) {
        data[i] = old.data[i];
    }
    size = n;
}

int MyArray::getSize() {
    return size;
}

int MyArray::getCapacity() {
    return capacity;
}

bool MyArray::isEmpty() {
    return size == 0;
}

bool MyArray::isFull() {
    return sizeof(data) == size;
}

bool MyArray::pIsOutOfRange(int p) {
    return p < 0 || p >= sizeof(data);
}

void MyArray::addInPlace(int n, int p) {
    try {
        if (pIsOutOfRange(p)) {
            throw POUTOFRANGEERROR;
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
    }
    catch (...) {
        std::cout << "errors happened in addInPlace\n";
        std::cout << "errors not defined in class MyArrayP happened.\n";
    }
}

void MyArray::addToEnd(int e) {
    addInPlace(e, size);
}

void MyArray::addToBegin(int b) {
    addInPlace(b, 0);
}

int MyArray::get(int p) {
    try{
        if (pIsOutOfRange(p)) {
            throw POUTOFRANGEERROR;
        }
        else if (p>=size){
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
    }
    catch (...) {
        std::cout << "errors happened in get\n";
        std::cout << "errors not defined in class MyArrayP happened.\n";
	}
}

int MyArray::set(int n, int p) {
    try{
        if (pIsOutOfRange(p)) {
            throw POUTOFRANGEERROR;
        }
        else if (p >= size) {
            throw POUTOFSIZEERROR;
        }
        else {
            data[p] = n;
        }
    }
    catch(int e){
        if(e==POUTOFRANGEERROR){
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
    }
}

void MyArray::readArray() {
    std::cout << "capacity = " << sizeof(data) << ", size = " << size << "\n";
    for (int i = 0; i < size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << '\n';
}