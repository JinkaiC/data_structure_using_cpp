#pragma once
#include "MyArray.h"
#include <iostream>
#include <algorithm>


template<typename T>
class MyDynamicArray : public MyArray<T>
{
	//支持动态扩容和缩容的数组类，继承自MyArray类
	//扩容条件：当数组满时，扩容为原来的一倍
	//缩容条件：当数组中元素个数小于容量的1/4时，缩容为原来的一半，但最小容量为10
	//注意：初始化时，过大的容量不会缩容，只有在删除元素时，才会触发缩容操作，我们认为初始化时的容量是用户的需求，不能随意缩容
public:
    //构造函数，默认容量为10，调用父类构造函数
    MyDynamicArray(int capacity = 10) : MyArray<T>(capacity) {}

    //复制构造函数(与父类对比，不需要传入capacity参数)
    MyDynamicArray(const MyDynamicArray<T>& other) : MyArray<T>(other.capacity) {
        this->size = other.size;
        for (int i = 0; i < this->size; ++i) {
            this->data[i] = other.data[i];
        }
    }

    //添加元素n到位置p，空间不足时，动态扩容
    void addInPlace(T n, int p) {
        try {
            if (p<0 || p>this->capacity) {
                throw MyArray<T>::POUTOFRANGEERROR;
            }
            else {
                if (this->isFull()) {
                    this->resize(2 * this->capacity);
                }
                for (int i = this->size - 1; i >= p; --i) {
                    this->data[i + 1] = this->data[i];
                }
                this->data[p] = n;
                ++this->size;
            }
        }
        catch (int e) {
            if (e == MyArray<T>::POUTOFRANGEERROR) {
                std::cout << "error happened in addInPlace!\n";
                std::cout << "capacity = " << this->capacity << "\n";
                std::cout << "the index p is out of range!\n";
            }
        }
        catch (...) {
            std::cout << "errors happened in addInPlace\n";
            std::cout << "errors not defined in class MyArrayP happened.\n";
            throw std::logic_error("Unexpected error in addInPlace function"); // Rethrow as a standard exception
        }
    }

    //在父类中，addLast()和addFirst()通过addInPlace()实现，在子类中重载addInPlace()后，也应对其重载
    void addLast(T n) {
        this->MyDynamicArray::addInPlace(n, this->size);
	}
    void addFirst(T n) {
        this->MyDynamicArray::addInPlace(n, 0);
    }

    //重载remove函数，删除位置p的元素，空间过大时，动态缩容
    T remove(int p) {
        try {
            if (this->pIsOutOfRange(p)) {
                throw MyArray<T>::POUTOFRANGEERROR;
            }
            else {
				T removedElement = this->data[p];
                for (int i = p; i < this->size - 1; ++i) {
                    this->data[i] = this->data[i + 1];
                }
                --this->size;
                while (this->size < this->capacity / 4 && this->capacity > 10) {
                    this->resize(std::max(this->capacity / 2, 10));
                }
				return removedElement;
            }
        }
        catch (int e) {
            if (e == MyArray<T>::POUTOFRANGEERROR) {
                std::cout << "error happened in remove!\n";
                std::cout << "capacity = " << this->capacity << "\n";
                std::cout << "the index p is out of range!\n";
            }
			std::cout << "Returning default-constructed T due to error in remove\n";
			return T(); // Return a default-constructed T in case of error
        }
        catch (...) {
            std::cout << "errors happened in remove\n";
            std::cout << "errors not defined in class MyArrayP happened.\n";
            throw std::logic_error("Unexpected error in removeInPlace function"); // Rethrow as a standard exception
        }
    }

    //在父类中，removeLast()和removeFirst()通过remove()实现，在子类中重载remove()后，也应对其重载
    T removeLast() {
        return this->MyDynamicArray::remove(this->size - 1);
	}
    T removeFirst() {
        return this->MyDynamicArray::remove(0);
	}
};